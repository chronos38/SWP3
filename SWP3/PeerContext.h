#pragma once
#include "ITcpClient.h"
#include "ITcpListener.h"

enum class PeerStates : Byte {
	Listen,
	Alive,
	NotAlive,
	Closed
};

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

	virtual void Listen();

	virtual void Open();
	virtual void Close();

	virtual void SendState();
	virtual void SendString(const String& _sMessage);
	virtual void SendData(const Vector<Byte>& _vBuffer);

	virtual PeerStates ReceiveState();
	virtual void ReceiveString(String& _sMessage);
	virtual void ReceiveData(Vector<Byte>& _vBuffer);

protected:

	virtual void ChangeState(PeerStatePtr _pPeerState);
	virtual NetworkStreamPtr GetStream() const;

private:

	PeerStatePtr m_pPeerState;
	NetworkStreamPtr m_pNetworkStream;

	Deque<String> m_qReceivedMessages;
	Deque<String> m_qReceivedMessages;
	Deque<String> m_qReceivedMessages;
};

class PeerContextComposite : PeerContext
{
	friend class PeerState;

public:

	PeerContextComposite() = default;
	PeerContextComposite(const PeerContextComposite&) = default;
	virtual ~PeerContextComposite() = default;

	virtual void Add(PeerContextPtr _pPeerContext) final;
	virtual void Remove(PeerContextPtr _pPeerContext) final;
	virtual PeerContextPtr GetChilde(S32 _iIndex) final;

	virtual void Listen() override;

	virtual void Open() override;
	virtual void Close() override;

	virtual void SendState() override;
	virtual void SendString(const String& _sMessage) override;
	virtual void SendData(const Vector<Byte>& _vBuffer) override;

private:

	Deque<PeerContextPtr> m_qPeerContext;
};
