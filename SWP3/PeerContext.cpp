#include "PeerContext.h"
#include "PeerState.h"

PeerContext::PeerContext(TcpClientPtr _pClient)
{
	m_pClient = pClient;
}

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

String PeerContext::GetState()
{
	return m_pPeerState->GetState(this);
}

TcpClientPtr PeerContext::GetClient() const
{
	return m_pClient;
}

void PeerContext::ChangeState(PeerStatePtr _pPeerState)
{
	m_pPeerState = _pPeerState;
}

void PeerContextComposite::Remove(PeerContextPtr _pPeerContext)
{
	for (auto it = m_qPeerContext.begin(), end = m_qPeerContext.end(); it != end; it++) {
		if (*it == _pPeerContext) {
			m_qPeerContext.erase(it);
			break;
		}
	}
}

void PeerContextComposite::Add(PeerContextPtr _pPeerContext)
{
	m_qPeerContext.push_back(_pPeerContext);
}

PeerContextPtr PeerContextComposite::GetChild(S32 _iIndex)
{
	return m_qPeerContext[_iIndex];
}

void PeerContextComposite::RemoveAll()
{
	m_qPeerContext.clear();
}

S32 PeerContextComposite::Count()
{
	return (S32)m_qPeerContext.size();
}

void PeerContextComposite::Open()
{
	for (PeerContextPtr pContext : m_qPeerContext) {
		pContext->Open();
	}
}

void PeerContextComposite::Close()
{
	for (PeerContextPtr pContext : m_qPeerContext) {
		pContext->Close();
	}
}

void PeerContextComposite::SendString(const String& _sMessage)
{
	for (PeerContextPtr pContext : m_qPeerContext) {
		pContext->SendString(_sMessage);
	}
}

void PeerContextComposite::SendData(const Vector<Byte>& _vBuffer)
{
	for (PeerContextPtr pContext : m_qPeerContext) {
		pContext->SendData(_vBuffer);
	}
}
