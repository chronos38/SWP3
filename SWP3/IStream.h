#pragma once
#include "Definitions.h"

// TODO: Klasse auf IStream umbennen
class INetworkStream
{
public:

	// TODO: Interface ausbauen

	virtual bool CanRead() const = 0;
	virtual bool CanWrite() const = 0;

	virtual S32 Read(Vector<Byte>& _vBuffer_, S32 _iOffset, S32 _iSize) = 0;
	virtual S32 ReadByte() = 0;

	virtual S32 Write(const Vector<Byte>& _vBuffer, S32 _iOffset, S32 _iSize) = 0;
	virtual void WriteByte(Byte _Value) = 0;

	virtual void Close() = 0;
};
