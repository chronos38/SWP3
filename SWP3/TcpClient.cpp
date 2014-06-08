#include "TcpClient.h"
#include "SocketTypes.h"

TcpClient::TcpClient()
{
}

TcpClient::TcpClient(AddressPtr _pAddress)
{
	AddressInfoPtr pInfo = _pAddress->GetInfo();

	if (pInfo->eSocketType != SocketType::Stream) {
		throw TcpClientException("Given address is not a TCP Address");
	}

	m_pSocket = ISocket::Create(_pAddress->GetSocketAddress()->GetAddressFamily(), SocketType::Stream, pInfo->eProtocolType);
	m_pSocket->Connect(_pAddress);
}

SocketPtr TcpClient::GetSocket() const
{
	return m_pSocket;
}

void TcpClient::SetSocket(SocketPtr _pSocket)
{
	m_pSocket = _pSocket;
	m_nsNetworkStream = NetworkStreamPtr(new NetworkStream(_pSocket));
}

void TcpClient::Connect(AddressPtr _pAddress)
{
	m_pSocket->Connect(_pAddress);
}

bool TcpClient::IsConnected() const
{
	return m_pSocket->IsConnected();
}

NetworkStreamPtr TcpClient::GetStream() const
{
	return m_nsNetworkStream;
}

TcpClientPtr ITcpClient::Create()
{
	return TcpClientPtr(new TcpClient());
}

TcpClientPtr Create(AddressPtr _pAddress)
{
	return TcpClientPtr(new TcpClient(_pAddress));
}
