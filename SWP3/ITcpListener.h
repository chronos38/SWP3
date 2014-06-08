#pragma once
#include "ITcpClient.h"

class ITcpListener;
typedef Pointer<ITcpListener> TcpListenerPtr;

ExceptionClass(TcpListenerException)

class ITcpListener
{
public:

	static TcpListenerPtr Create(AddressPtr _pAddress);

	virtual SocketPtr AcceptSocket() const = 0;
	virtual TcpClientPtr AcceptClient() const = 0;

	virtual void Start() const = 0;
	virtual void Start(S32 _iBacklog) const = 0;
	virtual void Stop() = 0;

	virtual bool Pending() const = 0;
	virtual bool IsActive() const = 0;
};
