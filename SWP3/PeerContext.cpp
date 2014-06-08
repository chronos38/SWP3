#include "PeerContext.h"
#include "PeerState.h"

void PeerContext::Open()
{
	m_pPeerState->Open(this);
}

void PeerContext::Close()
{
	m_pPeerState->Close(this);
}

void PeerContext::SendState()
{
	m_pPeerState->SendState(this);
}

void PeerContext::SendString(const String& _sMessage)
{
	m_pPeerState->SendString(this, _sMessage);
}

void PeerContext::SendData(const Vector<Byte>& _vBuffer)
{
	m_pPeerState->SendData(this, _vBuffer);
}

PeerStates PeerContext::ReceiveState()
{
	return m_pPeerState->ReceiveState(this);
}

void PeerContext::ReceiveString(String& _sMessage)
{
	m_pPeerState->ReceiveString(this, _sMessage);
}

void PeerContext::ReceiveData(Vector<Byte>& _vBuffer)
{
	m_pPeerState->ReceiveData(this, _vBuffer);
}

void PeerContext::ChangeState(PeerStatePtr _pPeerState)
{
	m_pPeerState = _pPeerState;
}

NetworkStreamPtr PeerContext::GetStream() const
{
	return m_pNetworkStream;
}
