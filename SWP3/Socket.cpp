#include "Socket.h"
#include "SocketTypes.h"
#include <cstring>
#include <cerrno>
#include <algorithm>

// TODO: Timeout und Available muss not implementiert werden

Socket::Socket(SocketHandle _hSocket, AddressFamily _eAddressFamily, SocketType _eSocketType, ProtocolType _eProtocolType)
{
	m_bIsConnected = (_hSocket != InvalidSocket);
	m_hSocket = _hSocket;
	m_eAddressFamily = _eAddressFamily;
	m_eSocketType = _eSocketType;
	m_eProtocolType = _eProtocolType;
}

Socket::Socket(AddressFamily _eAddressFamily, SocketType _eSocketType, ProtocolType _eProtocolType)
{
	m_eAddressFamily = _eAddressFamily;
	m_eSocketType = _eSocketType;
	m_eProtocolType = _eProtocolType;

	if ((m_hSocket = socket((int)_eAddressFamily, (int)_eSocketType, (int)_eProtocolType)) == InvalidSocket) {
		throw SocketException(strerror(errno));
	}
}

Socket::~Socket()
{
	if (m_hSocket != InvalidSocket) {
		CloseSocket(m_hSocket);
	}
}

AddressFamily Socket::GetAddressFamily() const
{
	return m_eAddressFamily;
}

SocketType Socket::GetSocketType() const
{
	return m_eSocketType;
}

ProtocolType Socket::GetProtocolType() const
{
	return m_eProtocolType;
}

S32 Socket::Available() const
{
	throw SocketException("'Available' is not yet implemented");
}

void Socket::Bind(const AddressPtr _pAddress)
{
	AddressInfoPtr pInfo = _pAddress->GetInfo();

	if (bind(m_hSocket, pInfo->pAddress, pInfo->iAddressLength) != 0) {
		m_bIsBound = false;
		throw SocketException(strerror(errno));
	} else {
		m_bIsBound = true;
	}
}

void Socket::Bind(const Vector<AddressPtr>& _vAddresses)
{
	for (const AddressPtr& pAddress : _vAddresses) {
		AddressInfoPtr pInfo = pAddress->GetInfo();

		if (bind(m_hSocket, pInfo->pAddress, pInfo->iAddressLength) != 0) {
			continue;
		} else {
			m_bIsBound = true;
			return;
		}
	}

	m_bIsBound = false;
	throw SocketException(strerror(errno));
}

bool Socket::IsBound() const
{
	return m_bIsBound;
}

void Socket::Connect(const AddressPtr _pAddress)
{
	AddressInfoPtr pInfo = _pAddress->GetInfo();

	if (connect(m_hSocket, pInfo->pAddress, pInfo->iAddressLength) != 0) {
		m_bIsConnected = false;
		throw SocketException(strerror(errno));
	} else {
		m_bIsConnected = true;
	}
}

void Socket::Connect(const Vector<AddressPtr>& _vAddresses)
{
	for (const AddressPtr& pAddress : _vAddresses) {
		AddressInfoPtr pInfo = pAddress->GetInfo();

		if (connect(m_hSocket, pInfo->pAddress, pInfo->iAddressLength) != 0) {
			continue;
		} else {
			m_bIsConnected = true;
			return;
		}
	}

	m_bIsConnected = false;
	throw SocketException(strerror(errno));
}

bool Socket::IsConnected() const
{
	return m_bIsConnected;
}

void Socket::Listen(S32 _iBacklog) const
{
	if (listen(m_hSocket, _iBacklog) != 0) {
		throw SocketException(strerror(errno));
	}
}

SocketPtr Socket::Accept() const
{
	AddrStorage asAddress;
	AddrLength iLength;

	SocketHandle hSocket = accept(m_hSocket, (Addr*)&asAddress, &iLength);

	if (hSocket == InvalidSocket) {
		throw SocketException(strerror(errno));
	}

	// TODO: Da AddressFamily noch nicht alle möglichen Werte implementiert hat, kann dieser Code zu einem Fehler führen
	return SocketPtr(new Socket(hSocket, (AddressFamily)asAddress.ss_family, m_eSocketType, m_eProtocolType));
}

void Socket::ShutDown(SocketShutdown _eHow)
{
	if (shutdown(m_hSocket, (int)_eHow) != 0) {
		throw SocketException(strerror(errno));
	}

	if (_eHow == SocketShutdown::Both) {
		m_bIsBound = m_bIsConnected = false;
	}
}

void Socket::Close()
{
	if (CloseSocket(m_hSocket) != 0) {
		throw SocketException(strerror(errno));
	}

	m_bIsBound = m_bIsConnected = false;
}

S32 Socket::Receive(Vector<Byte>& _vBuffer_, int _iFlags) const
{
	Vector<Byte> vBuffer(SendBufferSize);
	S32 iSize = (S32)_vBuffer_.size();
	S32 iTotal = 0;

	for (int iN = 0; iTotal < iSize; iTotal += iN) {
		int iLength = ((iTotal + ReceiveBufferSize > iSize) ? (iSize - iTotal) : ReceiveBufferSize);
		iN = recv(m_hSocket, (char*)vBuffer.data(), ReceiveBufferSize, _iFlags);

		if (iN == SocketError) {
			throw SocketException(strerror(errno));
		} else if (iN == 0) {
			throw SocketException("Remote end point closed connection");
		} else if (iLength != ReceiveBufferSize && iN > iLength) {
			std::copy(vBuffer.begin(), vBuffer.begin() + iLength, (char*)_vBuffer_.data() + iTotal);
			throw SocketException("Received bytes exceed given buffer");
		} else {
			std::copy(vBuffer.begin(), vBuffer.begin() + iN, (char*)_vBuffer_.data() + iTotal);
		}
	}

	return iTotal;
}

S32 Socket::Send(const Vector<Byte>& _vBuffer, int _iFlags) const
{
	S32 iResult = 0;
	S32 iSize = (S32)_vBuffer.size();

	for (S32 sent = 0; sent < iSize; sent += SendBufferSize) {
		int iLength = ((sent + SendBufferSize > iSize) ? (iSize - sent) : SendBufferSize);
		int iSent = send(m_hSocket, (const char*)_vBuffer.data() + sent, iLength, _iFlags);

		if (iSent == SocketError) {
			throw SocketException(strerror(errno));
		} else if (iSent == 0) {
			throw SocketException("Remote end point closed connection");
		} else if (iSent != iLength) {
			throw SocketException("Could not send all data");
		}

		iResult += iSent;
	}

	return iResult;
}

void Socket::SendFile(const String& _sPath) const
{
	Vector<Byte> vBuffer(SendBufferSize);
	InputFileStream ifFile(_sPath, std::ios_base::binary);
	int iSize = 0;

	ifFile.seekg(0, std::ios_base::end);
	iSize = (int)ifFile.tellg();
	ifFile.seekg(0, std::ios_base::beg);

	for (int iTotal = 0, iN = 0; iTotal < iSize; iTotal += iN) {
		int iLength = ((iTotal + SendBufferSize > iSize) ? (iSize - iTotal) : SendBufferSize);
		ifFile.read((char*)vBuffer.data(), iLength);
		iN = send(m_hSocket, (const char*)vBuffer.data() + iTotal, iLength, 0);

		if (iN == SocketError) {
			throw SocketException(strerror(errno));
		} else if (iN == 0) {
			throw SocketException("Remote end point closed connection");
		}
	}
}

void Socket::SendFile(const String& _sPath, const Vector<Byte>& _vPreBuffer, const Vector<Byte>& _vPostBuffer) const
{
	Vector<Byte> vBuffer;
	InputFileStream ifFile(_sPath, std::ios_base::binary);
	int iSize = (int)_vPreBuffer.size();

	// PreBuffer
	for (int iTotal = 0, iN = 0; iTotal < iSize; iTotal += iN) {
		int iLength = ((iTotal + SendBufferSize > iSize) ? (iSize - iTotal) : SendBufferSize);
		iN = send(m_hSocket, (const char*)_vPreBuffer.data() + iTotal, iLength, 0);

		if (iN == SocketError) {
			throw SocketException(strerror(errno));
		} else if (iN == 0) {
			throw SocketException("Remote end point closed connection");
		}
	}

	vBuffer.resize(SendBufferSize);
	ifFile.seekg(0, std::ios_base::end);
	iSize = (int)ifFile.tellg();
	ifFile.seekg(0, std::ios_base::beg);

	// File
	for (int iTotal = 0, iN = 0; iTotal < iSize; iTotal += iN) {
		int iLength = ((iTotal + SendBufferSize > iSize) ? (iSize - iTotal) : SendBufferSize);
		ifFile.read((char*)vBuffer.data(), iLength);
		iN = send(m_hSocket, (const char*)vBuffer.data() + iTotal, iLength, 0);

		if (iN == SocketError) {
			throw SocketException(strerror(errno));
		} else if (iN == 0) {
			throw SocketException("Remote end point closed connection");
		}
	}

	iSize = (int)_vPostBuffer.size();

	// PostBuffer
	for (int iTotal = 0, iN = 0; iTotal < iSize; iTotal += iN) {
		int iLength = ((iTotal + SendBufferSize > iSize) ? (iSize - iTotal) : SendBufferSize);
		iN = send(m_hSocket, (const char*)_vPreBuffer.data() + iTotal, iLength, 0);

		if (iN == SocketError) {
			throw SocketException(strerror(errno));
		} else if (iN == 0) {
			throw SocketException("Remote end point closed connection");
		}
	}
}

S32 Socket::ReceiveFrom(Vector<Byte>& _vBuffer_, AddressPtr& pAddress_, int _iFlags) const
{
	int iSize = (int)_vBuffer_.size();
	AddrStorage asAddressStorage;
	AddrLength iAddressLength = sizeof(asAddressStorage);
	int iReceived = recvfrom(m_hSocket, (char*)_vBuffer_.data(), iSize, _iFlags, (Addr*)&asAddressStorage, &iAddressLength);

	if (iReceived == SocketError) {
		throw SocketException(strerror(errno));
	} else if (iReceived == 0) {
		throw SocketException("There is no remote end point");
	}

	// Erzeuge SocketAddress und speicher den Sender in pAddress_
	SocketAddressPtr pSocketAddress = ISocketAddress::Create((AddressFamily)asAddressStorage.ss_family);
	Byte* pBuffer = (Byte*)&asAddressStorage;
	pSocketAddress->Item.insert(pSocketAddress->Item.begin(), pBuffer, pBuffer + iAddressLength);
	pAddress_ = IAddress::Create(pSocketAddress);
	return (S32)iReceived;
}

S32 Socket::SendTo(const Vector<Byte>& _vBuffer, const AddressPtr _pAddress, int _iFlags) const
{
	S32 iTotal = 0;
	int iSize = (int)_vBuffer.size();
	AddressInfoPtr pInfo = _pAddress->GetInfo();

	for (int iN = 0; iTotal < (int)_vBuffer.size(); iTotal += iN, iSize -= iN) {
		iN = sendto(m_hSocket, (const char*)_vBuffer.data() + iTotal, iSize, _iFlags, pInfo->pAddress, pInfo->iAddressLength);
		
		if (iN == SocketError) {
			throw SocketException(strerror(errno));
		} else if (iN == 0) {
			throw SocketException("Remote end point closed connection");
		}
	}

	return iTotal;
}

SocketPtr ISocket::Create(AddressFamily _eAddressFamily, SocketType _eSocketType, ProtocolType _eProtocolType)
{
	return SocketPtr(new Socket(_eAddressFamily, _eSocketType, _eProtocolType));
}
