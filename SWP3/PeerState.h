#pragma once
#include "PeerContext.h"

class PeerState
{
public:

	virtual void Listen(PeerContext* _pPeerContext) = 0;

	virtual void Open(PeerContext* _pPeerContext) = 0;
	virtual void Close(PeerContext* _pPeerContext) = 0;

	virtual void SendState(PeerContext* _pPeerContext) = 0;
	virtual void SendString(PeerContext* _pPeerContext, const String& _sMessage) = 0;
	virtual void SendData(PeerContext* _pPeerContext, const Vector<Byte>& _vBuffer) = 0;

	virtual PeerStates ReceiveState(PeerContext* _pPeerContext) = 0;
	virtual void ReceiveString(PeerContext* _pPeerContext, String& _sMessage) = 0;
	virtual void ReceiveData(PeerContext* _pPeerContext, Vector<Byte>& _vBuffer) = 0;

protected:

	virtual void ChangeState(PeerContext* _pPeerContext, PeerStatePtr pState);
	virtual NetworkStreamPtr GetNetworkStream(PeerContext* _pPeerContext) const = 0;
};

class PeerListen : public PeerState
{
public:

	static PeerStatePtr Instance();

	virtual void Listen(PeerContext* _pPeerContext) override;

	virtual void Open(PeerContext* _pPeerContext) override;
	virtual void Close(PeerContext* _pPeerContext) override;

	virtual void SendState(PeerContext* _pPeerContext) override;
	virtual void SendString(PeerContext* _pPeerContext, const String& _sMessage) override;
	virtual void SendData(PeerContext* _pPeerContext, const Vector<Byte>& _vBuffer) override;

	virtual PeerStates ReceiveState(PeerContext* _pPeerContext) override;
	virtual void ReceiveString(PeerContext* _pPeerContext, String& _sMessage) override;
	virtual void ReceiveData(PeerContext* _pPeerContext, Vector<Byte>& _vBuffer) override;

protected:

	virtual NetworkStreamPtr GetNetworkStream(PeerContext* _pPeerContext) const override;
};

class PeerAlive : public PeerState
{
public:

	static PeerStatePtr Instance();

	virtual void Listen(PeerContext* _pPeerContext) override;

	virtual void Open(PeerContext* _pPeerContext) override;
	virtual void Close(PeerContext* _pPeerContext) override;

	virtual void SendState(PeerContext* _pPeerContext) override;
	virtual void SendString(PeerContext* _pPeerContext, const String& _sMessage) override;
	virtual void SendData(PeerContext* _pPeerContext, const Vector<Byte>& _vBuffer) override;

	virtual PeerStates ReceiveState(PeerContext* _pPeerContext) override;
	virtual void ReceiveString(PeerContext* _pPeerContext, String& _sMessage) override;
	virtual void ReceiveData(PeerContext* _pPeerContext, Vector<Byte>& _vBuffer) override;

protected:

	virtual NetworkStreamPtr GetNetworkStream(PeerContext* _pPeerContext) const override;
};

class PeerNotAlive : public PeerState
{
public:

	static PeerStatePtr Instance();

	virtual void Listen(PeerContext* _pPeerContext) override;

	virtual void Open(PeerContext* _pPeerContext) override;
	virtual void Close(PeerContext* _pPeerContext) override;

	virtual void SendState(PeerContext* _pPeerContext) override;
	virtual void SendString(PeerContext* _pPeerContext, const String& _sMessage) override;
	virtual void SendData(PeerContext* _pPeerContext, const Vector<Byte>& _vBuffer) override;

	virtual PeerStates ReceiveState(PeerContext* _pPeerContext) override;
	virtual void ReceiveString(PeerContext* _pPeerContext, String& _sMessage) override;
	virtual void ReceiveData(PeerContext* _pPeerContext, Vector<Byte>& _vBuffer) override;

protected:

	virtual NetworkStreamPtr GetNetworkStream(PeerContext* _pPeerContext) const override;
};

class PeerClosed : public PeerState
{
public:

	static PeerStatePtr Instance();

	virtual void Listen(PeerContext* _pPeerContext) override;

	virtual void Open(PeerContext* _pPeerContext) override;
	virtual void Close(PeerContext* _pPeerContext) override;

	virtual void SendState(PeerContext* _pPeerContext) override;
	virtual void SendString(PeerContext* _pPeerContext, const String& _sMessage) override;
	virtual void SendData(PeerContext* _pPeerContext, const Vector<Byte>& _vBuffer) override;

	virtual PeerStates ReceiveState(PeerContext* _pPeerContext) override;
	virtual void ReceiveString(PeerContext* _pPeerContext, String& _sMessage) override;
	virtual void ReceiveData(PeerContext* _pPeerContext, Vector<Byte>& _vBuffer) override;

protected:

	virtual NetworkStreamPtr GetNetworkStream(PeerContext* _pPeerContext) const override;
};
