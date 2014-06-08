#include "Address.h"
#include "SocketTypes.h"
#include <cstring>
#include <string>

Address::Address(SocketAddressPtr _pSocketAddress)
{
	Byte* pBuffer = _pSocketAddress->Item.data();
	m_sAddressStorage = *((AddrStorage*)pBuffer);
}

Address::Address(AddressFamily _eAddressFamily, const String& _sAddress, int _iPort)
{
	AddrIn aiIn;
	AddrIn6 ai6In;
	memset(&m_sAddressStorage, 0, sizeof(m_sAddressStorage));
	m_eAddressFamily = _eAddressFamily;

	switch (_eAddressFamily) {
	case AddressFamily::InterNetwork:
		aiIn.sin_family = AF_INET;
		aiIn.sin_port = htons((U16)_iPort);
		
		if (InetPton((int)_eAddressFamily, _sAddress.c_str(), &(aiIn.sin_addr)) != 1) {
			throw AddressException("Could not parse given address");
		}
		
		memcpy(&m_sAddressStorage, &aiIn, sizeof(aiIn));
		break;
	case AddressFamily::InterNetworkV6:
		ai6In.sin6_family = AF_INET6;
		ai6In.sin6_port = htons((U16)_iPort);

		if (InetPton((int)_eAddressFamily, _sAddress.c_str(), &(ai6In.sin6_addr)) != 1) {
			throw AddressException("Could not parse given address");
		}
		
		memcpy(&m_sAddressStorage, &ai6In, sizeof(ai6In));
		break;
	default:
		throw AddressException("Value of AddressFamily is not supported");
	}
}

Address::Address(AddressFamily _eAddressFamily, SocketType _eSocketType, ProtocolType _eProtocolType, Addr* _pAddress, AddrLength _iLength)
{
	m_eAddressFamily = _eAddressFamily;
	m_eSocketType = _eSocketType;
	m_eProtocolType = _eProtocolType;
	memset(&m_sAddressStorage, 0, sizeof(m_sAddressStorage));
	memcpy(&m_sAddressStorage, _pAddress, _iLength);
}

SocketAddressPtr Address::GetSocketAddress() const
{
	SocketAddressPtr pSocketAddress = ISocketAddress::Create((AddressFamily)m_sAddressStorage.ss_family);
	Byte* pBuffer = (Byte*)&m_sAddressStorage;
	pSocketAddress->Item.insert(pSocketAddress->Item.begin(), pBuffer, pBuffer + sizeof(m_sAddressStorage));
	return pSocketAddress;
}

AddressInfoPtr Address::GetInfo() const
{
	AddressInfoPtr pInfo(new AddressInfo);
	pInfo->eAddressFamily = m_eAddressFamily;
	pInfo->eProtocolType = m_eProtocolType;
	pInfo->eSocketType = m_eSocketType;
	pInfo->pAddress = (Addr*)&m_sAddressStorage;

	switch (m_eAddressFamily) {
	case AddressFamily::InterNetwork:
		pInfo->iAddressLength = sizeof(AddrIn);
		break;
	case AddressFamily::InterNetworkV6:
		pInfo->iAddressLength = sizeof(AddrIn6);
		break;
	default:
		throw AddressException("Value of AddressFamily is not supported");
	}

	return pInfo;
}

String Address::ToString() const
{
	char sAddress[INET6_ADDRSTRLEN];

	switch (m_eAddressFamily) {
	case AddressFamily::InterNetwork:
		if (!InetNtop(AF_INET6, &((AddrIn*)&m_sAddressStorage)->sin_addr, sAddress, sizeof(sAddress))) {
			throw AddressException("Could not convert stored address to presentation");
		} break;
	case AddressFamily::InterNetworkV6:
		if (!InetNtop(AF_INET6, &((AddrIn6*)&m_sAddressStorage)->sin6_addr, sAddress, sizeof(sAddress))) {
			throw AddressException("Could not convert stored address to presentation");
		} break;
	default:
		throw AddressException("Value of AddressFamily is not supported");
	}

	return sAddress;
}

AddressPtr IAddress::Create(SocketAddressPtr _pSocketAddress)
{
	return AddressPtr(new Address(_pSocketAddress));
}

AddressPtr IAddress::Create(AddressFamily _eAddressFamily, const String& _sAddress, int _iPort)
{
	return AddressPtr(new Address(_eAddressFamily, _sAddress, _iPort));
}

Vector<AddressPtr> IAddress::GetHostAddresses(SocketType _eSocketType, const String& _sAddress, int _iPort)
{
	return IAddress::GetHostAddresses(_eSocketType, _sAddress, std::to_string(_iPort));
}

Vector<AddressPtr> IAddress::GetHostAddresses(SocketType _eSocketType, const String& _sAddress, const String& _sService)
{
	Vector<AddressPtr> vResult;
	AddrInfo aiInfo, *pInfo, *pIt;

	memset(&aiInfo, 0, sizeof(aiInfo));
	aiInfo.ai_family = AF_UNSPEC;
	aiInfo.ai_socktype = (int)_eSocketType;

	if (getaddrinfo(_sAddress.c_str(), _sService.c_str(), &aiInfo, &pInfo) != 0) {
		throw AddressException(gai_strerror(errno));
	}

	for (pIt = pInfo; pIt; pIt = pIt->ai_next) {
		vResult.push_back(AddressPtr(new Address((AddressFamily)pIt->ai_family, (SocketType)pIt->ai_socktype, (ProtocolType)pIt->ai_protocol, pIt->ai_addr, pIt->ai_addrlen)));
	}

	freeaddrinfo(pInfo);
	return vResult;
}

U16 IAddress::HostToNetwork(U16 _uHost)
{
	return htons(_uHost);
}

U32 IAddress::HostToNetwork(U32 _uHost)
{
	return htonl(_uHost);
}

U64 IAddress::HostToNetwork(U64 _uHost)
{
	throw AddressException("'HostToNetwork' is not yet implemented");
}

U16 IAddress::NetworkToHost(U16 _uNetwork)
{
	return ntohs(_uNetwork);
}

U32 IAddress::NetworkToHost(U32 _uNetwork)
{
	return ntohl(_uNetwork);
}

U64 IAddress::NetworkToHost(U64 _uNetwork)
{
	throw AddressException("'NetworkToHost' is not yet implemented");
}

AddressException::AddressException(const String& _sWhat)
{
	m_sWhat = _sWhat;
}

const char* AddressException::what() const
{
	return m_sWhat.c_str();
}
