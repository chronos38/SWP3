#pragma once
#include "PeerContext.h"
#include "Exception.h"

ExceptionClass(PeerStateException)

class PeerState
{
public:

	virtual void Connect(PeerContext* _pPeerContext, const String& _sHost, const String& _sService) = 0;

	virtual void Listen(PeerContext* _pPeerContext, const String& _sHost, const String& _sService) = 0;

	virtual void Open(PeerContext* _pPeerContext) = 0;
	virtual void Close(PeerContext* _pPeerContext) = 0;

	virtual void SendString(PeerContext* _pPeerContext, const String& _sMessage) = 0;
	virtual void SendData(PeerContext* _pPeerContext, const Vector<Byte>& _vBuffer) = 0;

	virtual void ReceiveString(PeerContext* _pPeerContext, String& _sMessage_) = 0;
	virtual void ReceiveData(PeerContext* _pPeerContext, Vector<Byte>& _vBuffer_) = 0;

	virtual String GetState(PeerContext* _pPeerContext) const = 0;

protected:

	virtual void ChangeState(PeerContext* _pPeerContext, PeerStatePtr _pState) const final;
};

class PeerReady : public PeerState
{
public:

	static PeerStatePtr Instance();

	virtual void Connect(PeerContext* _pPeerContext, const String& _sHost, const String& _sService) override;

	virtual void Listen(PeerContext* _pPeerContext, const String& _sHost, const String& _sService) override;

	virtual void Open(PeerContext* _pPeerContext) override;
	virtual void Close(PeerContext* _pPeerContext) override;

	virtual void SendString(PeerContext* _pPeerContext, const String& _sMessage) override;
	virtual void SendData(PeerContext* _pPeerContext, const Vector<Byte>& _vBuffer) override;

	virtual void ReceiveString(PeerContext* _pPeerContext, String& _sMessage_) override;
	virtual void ReceiveData(PeerContext* _pPeerContext, Vector<Byte>& _vBuffer_) override;

	virtual String GetState(PeerContext* _pPeerContext) const override;

protected:

private:
};

class PeerListen : public PeerState
{
public:

	PeerListen(TcpListenerPtr _pListener);

	virtual void Connect(PeerContext* _pPeerContext, const String& _sHost, const String& _sService) override;

	virtual void Listen(PeerContext* _pPeerContext, const String& _sHost, const String& _sService) override;

	virtual void Open(PeerContext* _pPeerContext) override;
	virtual void Close(PeerContext* _pPeerContext) override;

	virtual void SendString(PeerContext* _pPeerContext, const String& _sMessage) override;
	virtual void SendData(PeerContext* _pPeerContext, const Vector<Byte>& _vBuffer) override;

	virtual void ReceiveString(PeerContext* _pPeerContext, String& _sMessage_) override;
	virtual void ReceiveData(PeerContext* _pPeerContext, Vector<Byte>& _vBuffer_) override;

	virtual String GetState(PeerContext* _pPeerContext) const override;

protected:

private:

	TcpListenerPtr m_pListener;
};

class PeerAlive : public PeerState
{
public:

	PeerAlive(TcpClientPtr _pClient);

	virtual void Connect(PeerContext* _pPeerContext, const String& _sHost, const String& _sService) override;

	virtual void Listen(PeerContext* _pPeerContext, const String& _sHost, const String& _sService) override;

	virtual void Open(PeerContext* _pPeerContext) override;
	virtual void Close(PeerContext* _pPeerContext) override;

	virtual void SendString(PeerContext* _pPeerContext, const String& _sMessage) override;
	virtual void SendData(PeerContext* _pPeerContext, const Vector<Byte>& _vBuffer) override;

	virtual void ReceiveString(PeerContext* _pPeerContext, String& _sMessage_) override;
	virtual void ReceiveData(PeerContext* _pPeerContext, Vector<Byte>& _vBuffer_) override;

	virtual String GetState(PeerContext* _pPeerContext) const override;

protected:

private:

	TcpClientPtr m_pClient;
};

class PeerDead : public PeerState
{
public:

	PeerDead(TcpClientPtr _pClient);

	virtual void Connect(PeerContext* _pPeerContext, const String& _sHost, const String& _sService) override;

	virtual void Listen(PeerContext* _pPeerContext, const String& _sHost, const String& _sService) override;

	virtual void Open(PeerContext* _pPeerContext) override;
	virtual void Close(PeerContext* _pPeerContext) override;

	virtual void SendString(PeerContext* _pPeerContext, const String& _sMessage) override;
	virtual void SendData(PeerContext* _pPeerContext, const Vector<Byte>& _vBuffer) override;

	virtual void ReceiveString(PeerContext* _pPeerContext, String& _sMessage_) override;
	virtual void ReceiveData(PeerContext* _pPeerContext, Vector<Byte>& _vBuffer_) override;

	virtual String GetState(PeerContext* _pPeerContext) const override;

protected:

private:

	TcpClientPtr m_pClient;
};

class PeerClosed : public PeerState
{
public:

	PeerClosed(TcpClientPtr _pClient);

	virtual void Connect(PeerContext* _pPeerContext, const String& _sHost, const String& _sService) override;

	virtual void Listen(PeerContext* _pPeerContext, const String& _sHost, const String& _sService) override;

	virtual void Open(PeerContext* _pPeerContext) override;
	virtual void Close(PeerContext* _pPeerContext) override;

	virtual void SendString(PeerContext* _pPeerContext, const String& _sMessage) override;
	virtual void SendData(PeerContext* _pPeerContext, const Vector<Byte>& _vBuffer) override;

	virtual void ReceiveString(PeerContext* _pPeerContext, String& _sMessage_) override;
	virtual void ReceiveData(PeerContext* _pPeerContext, Vector<Byte>& _vBuffer_) override;

	virtual String GetState(PeerContext* _pPeerContext) const override;

protected:

private:

	TcpClientPtr m_pClient;
};
