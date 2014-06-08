#pragma once
#include "NetworkStream.h"

class ITcpClient;
typedef Pointer<ITcpClient> TcpClientPtr;

ExceptionClass(TcpClientException)

class ITcpClient
{
public:

	static TcpClientPtr Create();
	static TcpClientPtr Create(AddressPtr _pAddress);

	virtual SocketPtr GetSocket() const = 0;
	virtual void SetSocket(SocketPtr _pSocket) = 0;

	virtual void Connect(AddressPtr _pAddress) = 0;
	virtual bool IsConnected() const = 0;
	virtual void Close() = 0;

	virtual NetworkStreamPtr GetStream() const = 0;
};
