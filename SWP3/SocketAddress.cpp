#include "SocketAddress.h"

SocketAddress::SocketAddress(AddressFamily _eAddressFamily)
{
	m_eAddressFamily = _eAddressFamily;
}

AddressFamily SocketAddress::GetAddressFamily() const
{
	return m_eAddressFamily;
}

SocketAddressPtr ISocketAddress::Create(AddressFamily _eAddressFamily)
{
	return SocketAddressPtr(new SocketAddress(_eAddressFamily));
}
