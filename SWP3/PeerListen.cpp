#include "PeerState.h"

PeerListen::PeerListen(TcpListenerPtr _pListener)
{
	m_pListener = _pListener;
}

void PeerListen::Connect(PeerContext* _pPeerContext, const String& _sHost, const String& _sService)
{
}

void PeerListen::Listen(PeerContext* _pPeerContext, const String& _sHost, const String& _sService)
{
}

void PeerListen::Open(PeerContext* _pPeerContext)
{
	try {
		ChangeState(_pPeerContext, PeerStatePtr(new PeerAlive(m_pListener->AcceptClient())));
	} catch (SocketException&) {
		std::rethrow_exception(std::current_exception()); // TODO: spezifisches error handling
	}
}

void PeerListen::Close(PeerContext* _pPeerContext)
{
}

void PeerListen::SendString(PeerContext* _pPeerContext, const String& _sMessage)
{
}

void PeerListen::SendData(PeerContext* _pPeerContext, const Vector<Byte>& _vBuffer)
{
}

void PeerListen::ReceiveString(PeerContext* _pPeerContext, String& _sMessage_)
{
}

void PeerListen::ReceiveData(PeerContext* _pPeerContext, Vector<Byte>& _vBuffer_)
{
}

String PeerListen::GetState(PeerContext* _pPeerContext) const
{
	return "Listen";
}
