#include "PeerState.h"

PeerAlive::PeerAlive(TcpClientPtr _pClient)
{
	m_pClient = _pClient;
}

void PeerAlive::Connect(PeerContext* _pPeerContext, const String& _sHost, const String& _sService)
{
}

void PeerAlive::Listen(PeerContext* _pPeerContext, const String& _sHost, const String& _sService)
{
}

void PeerAlive::Open(PeerContext* _pPeerContext)
{
}

void PeerAlive::Close(PeerContext* _pPeerContext)
{
	ChangeState(_pPeerContext, PeerStatePtr(new PeerClosed(m_pClient)));
}

void PeerAlive::SendString(PeerContext* _pPeerContext, const String& _sMessage)
{
	Byte* pData = (Byte*)_sMessage.data();
	Vector<Byte> vBuffer(pData, pData + _sMessage.size());
	m_pClient->GetStream()->Write(vBuffer, 0, vBuffer.size());
}

void PeerAlive::SendData(PeerContext* _pPeerContext, const Vector<Byte>& _vBuffer)
{
	m_pClient->GetStream()->Write(_vBuffer, 0, _vBuffer.size());
}

void PeerAlive::ReceiveString(PeerContext* _pPeerContext, String& _sMessage_)
{
	Vector<Byte> vBuffer(_sMessage_.capacity());
	m_pClient->GetStream()->Read(vBuffer, 0, vBuffer.size());
	_sMessage_ = (String::pointer)vBuffer[0];
}

void PeerAlive::ReceiveData(PeerContext* _pPeerContext, Vector<Byte>& _vBuffer_)
{
	m_pClient->GetStream()->Read(_vBuffer_, 0, _vBuffer_.size());
}
