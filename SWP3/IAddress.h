#pragma once
#include "ISocketAddress.h"
#include <string>
#include <vector>
#include <cstdint>

struct AddressInfo;
typedef Pointer<AddressInfo> AddressInfoPtr;

class IAddress;
typedef Pointer<IAddress> AddressPtr;

class IAddress
{
public:

	static AddressPtr Create(SocketAddressPtr _pSocketAddress);
	static AddressPtr Create(AddressFamily _eAddressFamily, const String& _sAddress, int _iPort);

	static Vector<AddressPtr> GetHostAddresses(const String& _sAddress, int _iPort);
	static Vector<AddressPtr> GetHostAddresses(const String& _sAddress, const String& _sService);

	virtual SocketAddressPtr GetSocketAddress() const = 0;
	virtual AddressInfoPtr GetInfo() const = 0;
	virtual String ToString() const = 0;

	static U16 HostToNetwork(U16 _uHost);
	static U32 HostToNetwork(U32 _uHost);
	static U64 HostToNetwork(U64 _uHost);

	static U16 NetworkToHost(U16 _uHost);
	static U32 NetworkToHost(U32 _uHost);
	static U64 NetworkToHost(U64 _uHost);
};
