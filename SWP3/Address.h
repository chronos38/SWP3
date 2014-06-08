#pragma once
#include "IAddress.h"

class Address : public IAddress
{
public:

	Address(SocketAddressPtr _pSocketAddress);
	Address(AddressFamily _eAddressFamily, const String& _sAddress, int _iPort);
	Address(AddressFamily _eAddressFamily, SocketType _eSocketType, ProtocolType _eProtocolType, Addr* _pAddress, AddrLength _iLength);

	virtual ~Address() = default;

	virtual SocketAddressPtr GetSocketAddress() const override;
	virtual AddressInfoPtr GetInfo() const override;
	virtual String ToString() const override;

protected:

private:

	AddressFamily m_eAddressFamily;
	SocketType m_eSocketType = SocketType::Unknwon;
	ProtocolType m_eProtocolType = ProtocolType::Unknown;

	AddrStorage m_sAddressStorage;
};
