#include "PeerState.h"

PeerClosed::PeerClosed(TcpClientPtr _pClient)
{
	m_pClient = _pClient;
}

void PeerClosed::Connect(PeerContext* _pPeerContext, const String& _sHost, const String& _sService)
{
}

void PeerClosed::Listen(PeerContext* _pPeerContext, const String& _sHost, const String& _sService)
{
}

void PeerClosed::Open(PeerContext* _pPeerContext)
{
	ChangeState(_pPeerContext, PeerStatePtr(new PeerAlive(m_pClient)));
}

void PeerClosed::Close(PeerContext* _pPeerContext)
{
}

void PeerClosed::SendString(PeerContext* _pPeerContext, const String& _sMessage)
{
}

void PeerClosed::SendData(PeerContext* _pPeerContext, const Vector<Byte>& _vBuffer)
{
}

void PeerClosed::ReceiveString(PeerContext* _pPeerContext, String& _sMessage_)
{
}

void PeerClosed::ReceiveData(PeerContext* _pPeerContext, Vector<Byte>& _vBuffer_)
{
}
