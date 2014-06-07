#pragma once
#include "ISocket.h"
#include <exception>

class SocketException : std::exception
{
	String m_sWhat;
public:
	SocketException(const String& _sWhat = "");
	virtual ~SocketException() = default;
	SocketException& operator=(const SocketException&) = default;
	virtual const char* what() const override;
};

extern "C" struct AddressInfo {
	AddressFamily eAddressFamily;
	SocketType eSocketType;
	ProtocolType eProtocolType;
	AddressLength iAddressLength;
	Address* pAddress;
};

class Socket : public ISocket
{
public:

	Socket(
		AddressFamily _eAddressFamily,
		SocketType _eSocketType,
		ProtocolType _eProtocolType
	);
	Socket() = delete;
	Socket(const Socket&) = delete;
	virtual ~Socket();

	virtual AddressFamily GetAddressFamily() const override;
	virtual SocketType GetSocketType() const override;
	virtual ProtocolType GetProtocolType() const override;
	virtual S32 Available() const override;

	virtual void Bind(const AddressPtr _pAddress) override;
	virtual void Bind(const Vector<AddressPtr>& _vAddresses) override;
	virtual bool IsBound() const override;

	virtual void Connect(const AddressPtr _pAddress) override;
	virtual void Connect(const Vector<AddressPtr>& _vAddresses) override;
	virtual bool IsConnected() const override;

	virtual void Listen(S32 _iBacklog) override;
	virtual SocketPtr Accept() override;

	virtual void ShutDown(SocketShutdown _eHow) override;
	virtual void Close() override;

	virtual S32 Receive(Vector<Byte>& _vBuffer_, int _iFlags = SocketFlags::None) const override;
	virtual S32 Send(const Vector<Byte>& _vBuffer, int _iFlags = SocketFlags::None) const override;
	virtual void SendFile(const String& _sPath) const override;
	virtual void SendFile(
		const String& _sPath,
		const Vector<Byte>& _vPreBuffer,
		const Vector<Byte>& _vPostBuffer
	) const override;
	virtual S32 ReceiveFrom(Vector<Byte>& _vBuffer_, AddressPtr& pAddress_, int _iFlags = SocketFlags::None) const override;
	virtual S32 SendTo(const Vector<Byte>& _vBuffer, const AddressPtr _pAddress, int _iFlags = SocketFlags::None) const override;

protected:

	explicit Socket(
		SocketHandle _hSocket,
		AddressFamily _eAddressFamily,
		SocketType _eSocketType,
		ProtocolType _eProtocolType
	);

private:

	SocketHandle m_hSocket;
	AddressFamily m_eAddressFamily;
	SocketType m_eSocketType;
	ProtocolType m_eProtocolType;
	bool m_bIsBound = false;
	bool m_bIsConnected = false;
};

