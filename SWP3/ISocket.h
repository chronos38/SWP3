#pragma once
#include "IAddress.h"

enum class SocketType {
	Stream = SOCK_STREAM,
	Datagram = SOCK_DGRAM,
	Raw = SOCK_RAW
};

enum class ProtocolType {
	IP = IPPROTO_IP,
	IPv4 = IPPROTO_IPV4,
	IPv6 = IPPROTO_IPV6,
	TCP = IPPROTO_TCP,
	UDP = IPPROTO_UDP
};

enum class SocketShutdown {
	Receive = 0,
	Send = 1,
	Both = 2
};

enum SocketFlags {
	None = 0,
	OutOfBand = MSG_OOB,
	Peek = MSG_PEEK,
	DontRoute = MSG_DONTROUTE,
	Truncated = MSG_CTRUNC
};

class ISocket;
typedef Pointer<ISocket> SocketPtr;

class ISocket
{
public:

	static SocketPtr Create(
		AddressFamily _eAddressFamily, 
		SocketType _eSocketType, 
		ProtocolType _eProtocolType
	);

	S32 ReceiveBufferSize = 8 * KB;
	S32 ReceiveTimeout = 0;
	S32 SendBufferSize = 8 * KB;
	S32 SendTimeout = 0;

	virtual AddressFamily GetAddressFamily() const = 0;
	virtual SocketType GetSocketType() const = 0;
	virtual ProtocolType GetProtocolType() const = 0;
	virtual S32 Available() const = 0;

	virtual void Bind(const AddressPtr _pAddress) = 0;
	virtual void Bind(const Vector<AddressPtr>& _vAddresses) = 0;
	virtual bool IsBound() const = 0;

	virtual void Connect(const AddressPtr _pAddress) = 0;
	virtual void Connect(const Vector<AddressPtr>& _vAddresses) = 0;
	virtual bool IsConnected() const = 0;

	virtual void Listen(S32 _iBacklog) = 0;
	virtual SocketPtr Accept() = 0;

	virtual void ShutDown(SocketShutdown _eHow) = 0;
	virtual void Close() = 0;

	virtual S32 Receive(Vector<Byte>& _vBuffer_, int _iFlags = SocketFlags::None) const = 0;
	virtual S32 Send(const Vector<Byte>& _vBuffer, int _iFlags = SocketFlags::None) const = 0;
	virtual void SendFile(const String& _sPath) const = 0;
	virtual void SendFile(
		const String& _sPath,
		const Vector<Byte>& _vPreBuffer,
		const Vector<Byte>& _vPostBuffer
	) const = 0;
	virtual S32 ReceiveFrom(Vector<Byte>& _vBuffer_, AddressPtr& pAddress_, int _iFlags = SocketFlags::None) const = 0;
	virtual S32 SendTo(const Vector<Byte>& _vBuffer, const AddressPtr _pAddress, int _iFlags = SocketFlags::None) const = 0;
};
