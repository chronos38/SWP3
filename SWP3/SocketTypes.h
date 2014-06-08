#pragma once
#include "ISocket.h"

extern "C" struct AddressInfo {
	AddressFamily eAddressFamily;
	SocketType eSocketType;
	ProtocolType eProtocolType;
	AddrLength iAddressLength;
	Addr* pAddress;
};
