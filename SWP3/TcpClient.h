#pragma once
#include "ITcpClient.h"

class TcpClient : public ITcpClient
{
public:

	TcpClient();
	TcpClient(const TcpClient&) = default;
	TcpClient(AddressPtr _pAddress);
	virtual ~TcpClient() = default;

	virtual SocketPtr GetSocket() const override;
	virtual void SetSocket(SocketPtr _pSocket) override;

	virtual void Connect(AddressPtr _pAddress) override;
	virtual bool IsConnected() const override;
	virtual void Close() override;

	virtual NetworkStreamPtr GetStream() const override;

protected:

private:

	SocketPtr m_pSocket;
	NetworkStreamPtr m_nsNetworkStream;
};
