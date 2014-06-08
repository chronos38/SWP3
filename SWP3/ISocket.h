#pragma once
#include "IAddress.h"
#include <exception>

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

class SocketException : std::exception
{
	String m_sWhat;
public:
	SocketException(const String& _sWhat = "");
	virtual ~SocketException() = default;
	SocketException& operator=(const SocketException&) = default;
	virtual const char* what() const override;
};

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
