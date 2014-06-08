#pragma once
#include "ISocketAddress.h"
#include "Exception.h"
#include <string>
#include <vector>
#include <cstdint>

enum class SocketType {
	Unknwon = 0,
	Stream = SOCK_STREAM,
	Datagram = SOCK_DGRAM,
	Raw = SOCK_RAW
};

enum class ProtocolType {
	Unknown = 0,
	IP = IPPROTO_IP,
	IPv4 = IPPROTO_IPV4,
	IPv6 = IPPROTO_IPV6,
	TCP = IPPROTO_TCP,
	UDP = IPPROTO_UDP
};

struct AddressInfo;
typedef Pointer<AddressInfo> AddressInfoPtr;

class IAddress;
typedef Pointer<IAddress> AddressPtr;

ExceptionClass(AddressException)

class IAddress
{
public:

	static AddressPtr Create(SocketAddressPtr _pSocketAddress);
	static AddressPtr Create(AddressFamily _eAddressFamily, const String& _sAddress, int _iPort);

	static Vector<AddressPtr> GetHostAddresses(SocketType _eSocketType, const String& _sAddress, int _iPort);
	static Vector<AddressPtr> GetHostAddresses(SocketType _eSocketType, const String& _sAddress, const String& _sService);

	virtual SocketAddressPtr GetSocketAddress() const = 0;
	virtual AddressInfoPtr GetInfo() const = 0;
	virtual String ToString() const = 0;

	static U16 HostToNetwork(U16 _uHost);
	static U32 HostToNetwork(U32 _uHost);
	static U64 HostToNetwork(U64 _uHost);

	static U16 NetworkToHost(U16 _uNetwork);
	static U32 NetworkToHost(U32 _uNetwork);
	static U64 NetworkToHost(U64 _uNetwork);
};
