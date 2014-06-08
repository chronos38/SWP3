#include "TcpListener.h"
#include "SocketTypes.h"

TcpListener::TcpListener(AddressPtr _pAddress)
{
	AddressInfoPtr pInfo = _pAddress->GetInfo();

	if (pInfo->eSocketType != SocketType::Stream) {
		throw TcpListenerException("Given address is not a TCP Address");
	}

	m_pSocket = ISocket::Create(_pAddress->GetSocketAddress()->GetAddressFamily(), SocketType::Stream, pInfo->eProtocolType);
	m_pSocket->Bind(_pAddress);
}

TcpListener::TcpListener(SocketPtr _pSocket)
{
	m_pSocket = _pSocket;
}

SocketPtr TcpListener::AcceptSocket() const
{
	return m_pSocket->Accept();
}

TcpClientPtr TcpListener::AcceptClient() const
{
	TcpClientPtr pClient = ITcpClient::Create();
	pClient->SetSocket(AcceptSocket());
	return pClient;
}

void TcpListener::Start() const
{
	m_pSocket->Listen(10);
}

void TcpListener::Start(S32 _iBacklog) const
{
	if (_iBacklog < 0) {
		throw std::out_of_range("The _iBacklog parameter is less than 0");
	}

	m_pSocket->Listen(_iBacklog);
}

void TcpListener::Stop()
{
	m_pSocket->Close(); // TODO: Wenn der Socket einmal geschlossen ist, dann kann er nicht wieder verwendet werden. Es sollte anders implementiert werden
}

bool TcpListener::Pending() const
{
	throw TcpListenerException("'Pending' is not yet implemented");
}

bool TcpListener::IsActive() const
{
	return m_pSocket->IsBound();
}

TcpListenerPtr ITcpListener::Create(AddressPtr _pAddress)
{
	return TcpListenerPtr(new TcpListener(_pAddress));
}
