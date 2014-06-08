#include "PeerContext.h"
#include "PeerState.h"


void PeerContext::Connect(const String& _sHost, const String& _sService)
{
	m_pPeerState->Connect(this, _sHost, _sService);
}

void PeerContext::Listen(const String& _sHost, const String& _sService)
{
	m_pPeerState->Listen(this, _sHost, _sService);
}

void PeerContext::Open()
{
	m_pPeerState->Open(this);
}

void PeerContext::Close()
{
	m_pPeerState->Close(this);
}

void PeerContext::SendString(const String& _sMessage)
{
	m_pPeerState->SendString(this, _sMessage);
}

void PeerContext::SendData(const Vector<Byte>& _vBuffer)
{
	m_pPeerState->SendData(this, _vBuffer);
}

void PeerContext::ReceiveString(String& _sMessage_)
{
	m_pPeerState->ReceiveString(this, _sMessage_);
}

void PeerContext::ReceiveData(Vector<Byte>& _vBuffer_)
{
	m_pPeerState->ReceiveData(this, _vBuffer_);
}

void PeerContext::ChangeState(PeerStatePtr _pPeerState)
{
	m_pPeerState = _pPeerState;
}
