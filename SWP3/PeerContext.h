#pragma once
#include "ITcpClient.h"
#include "ITcpListener.h"

class PeerState;
typedef Pointer<PeerState> PeerStatePtr;

class PeerContext;
typedef Pointer<PeerContext> PeerContextPtr;

class PeerContextComposite;
typedef Pointer<PeerContextComposite> PeerContextCompositePtr;

class PeerContext
{
	friend class PeerState;

public:

	PeerContext() = default;
	PeerContext(const PeerContext&) = default;
	PeerContext(TcpClientPtr _pClient);
	virtual ~PeerContext() = default;

	virtual void Connect(const String& _sHost, const String& _sService);

	virtual void Listen(const String& _sHost, const String& _sService);

	virtual void Open();
	virtual void Close();

	virtual void SendString(const String& _sMessage);
	virtual void SendData(const Vector<Byte>& _vBuffer);

	virtual void ReceiveString(String& _sMessage_);
	virtual void ReceiveData(Vector<Byte>& _vBuffer_);

	virtual String GetState();
	virtual TcpClientPtr GetClient() const;

protected:

	virtual void ChangeState(PeerStatePtr _pPeerState);

private:

	PeerStatePtr m_pPeerState;
	TcpClientPtr m_pClient;
};

class PeerContextComposite : PeerContext
{
	friend class PeerState;

public:

	PeerContextComposite() = default;
	PeerContextComposite(const PeerContextComposite&) = default;
	virtual ~PeerContextComposite() = default;

	virtual void Remove(PeerContextPtr _pPeerContext) final;
	virtual void Add(PeerContextPtr _pPeerContext) final;
	virtual PeerContextPtr GetChild(S32 _iIndex) final;
	virtual void RemoveAll() final;
	virtual S32 Count() final;

	virtual void Open() override;
	virtual void Close() override;

	virtual void SendString(const String& _sMessage) override;
	virtual void SendData(const Vector<Byte>& _vBuffer) override;

private:

	Deque<PeerContextPtr> m_qPeerContext;
};
