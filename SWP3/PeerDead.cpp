#include "PeerState.h"

PeerDead::PeerDead(TcpClientPtr _pClient)
{
	m_pClient = _pClient;
}

void PeerDead::Connect(PeerContext* _pPeerContext, const String& _sHost, const String& _sService)
{
}

void PeerDead::Listen(PeerContext* _pPeerContext, const String& _sHost, const String& _sService)
{
}

void PeerDead::Open(PeerContext* _pPeerContext)
{
}

void PeerDead::Close(PeerContext* _pPeerContext)
{
	ChangeState(_pPeerContext, PeerStatePtr(new PeerClosed(m_pClient)));
}

void PeerDead::SendString(PeerContext* _pPeerContext, const String& _sMessage)
{
}

void PeerDead::SendData(PeerContext* _pPeerContext, const Vector<Byte>& _vBuffer)
{
}

void PeerDead::ReceiveString(PeerContext* _pPeerContext, String& _sMessage_)
{
}

void PeerDead::ReceiveData(PeerContext* _pPeerContext, Vector<Byte>& _vBuffer_)
{
}
