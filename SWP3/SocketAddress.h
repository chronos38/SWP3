#pragma once
#include "ISocketAddress.h"

class SocketAddress : public ISocketAddress
{
public:

	SocketAddress(AddressFamily _eAddressFamily);

	virtual ~SocketAddress() = default;

	virtual AddressFamily GetAddressFamily() const override;

protected:

private:

	AddressFamily m_eAddressFamily;
};
