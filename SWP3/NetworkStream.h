#pragma once
#include "IStream.h"
#include "ISocket.h"

class ITcpClient;

class NetworkStream;
typedef Pointer<NetworkStream> NetworkStreamPtr;

class NetworkStream : public INetworkStream
{
public:

	NetworkStream() = delete;
	NetworkStream(const NetworkStream&) = default;

	NetworkStream(SocketPtr _pSocket);
	virtual ~NetworkStream() = default;

	virtual bool CanRead() const override;
	virtual bool CanWrite() const override;

	virtual S32 Read(Vector<Byte>& _vBuffer_, S32 _iOffset, S32 _iSize) override;
	virtual S32 ReadByte() override;

	virtual S32 Write(const Vector<Byte>& _vBuffer, S32 _iOffset, S32 _iSize) override;
	virtual void WriteByte(Byte _Value) override;

	virtual void Close() override;

protected:

private:

	SocketPtr m_pSocket;
};
