#pragma once
#include "ITcpListener.h"

class TcpListener : public ITcpListener
{
public:

	TcpListener() = delete;
	TcpListener(const TcpListener&) = default;
	TcpListener(AddressPtr _pAddress);
	virtual ~TcpListener() = default;

	virtual SocketPtr AcceptSocket() const override;
	virtual TcpClientPtr AcceptClient() const override;

	virtual void Start() const override;
	virtual void Start(S32 _iBacklog) const override;
	virtual void Stop() override;

	virtual bool Pending() const override;
	virtual bool IsActive() const override;

protected:

	TcpListener(SocketPtr _pSocket);

private:

	SocketPtr m_pSocket;
};
