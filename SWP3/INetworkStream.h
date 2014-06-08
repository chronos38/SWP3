#pragma once
#include "ISocket.h"

class INetworkStream;
typedef Pointer<INetworkStream> NetworkStreamPtr;

class INetworkStream : public IStream
{
public:

	static NetworkStreamPtr Create(SocketPtr _pSocket);
};
