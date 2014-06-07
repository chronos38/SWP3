#pragma once
#include "Definitions.h"

enum class AddressFamily {
	Unknown = AF_UNKNOWN1,
	Unspecified = AF_UNSPEC,
	InterNetwork = AF_INET,
	InterNetworkV6 = AF_INET6
	// TODO: Mehr hinzufügen
};

class ISocketAddress;
typedef Pointer<ISocketAddress> SocketAddressPtr;

class ISocketAddress
{
public:

	static SocketAddressPtr Create(AddressFamily _eAddressFamily);

	Vector<Byte> Item;

	virtual AddressFamily GetAddressFamily() const = 0;
};
