#pragma once
#include "ITcpClient.h"
#include "ITcpListener.h"

class PeerState;
typedef Pointer<PeerState> PeerStatePtr;

class PeerContext;
typedef Pointer<PeerContext> PeerContextPtr;

class PeerContext
{
	friend class PeerState;

public:

	PeerContext() = default;
	PeerContext(const PeerContext&) = default;
	virtual ~PeerContext() = default;

	virtual void Connect(const String& _sHost, const String& _sService);

	virtual void Listen(const String& _sHost, const String& _sService);

	virtual void Open();
	virtual void Close();

	virtual void SendString(const String& _sMessage);
	virtual void SendData(const Vector<Byte>& _vBuffer);

	virtual void ReceiveString(String& _sMessage_);
	virtual void ReceiveData(Vector<Byte>& _vBuffer_);

protected:

	virtual void ChangeState(PeerStatePtr _pPeerState);

private:

	PeerStatePtr m_pPeerState;

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

	virtual void SendString(const String& _sMessage_) override;
	virtual void SendData(const Vector<Byte>& _vBuffer_) override;

private:

	Deque<PeerContextPtr> m_qPeerContext;
};
