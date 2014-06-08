#include "NetworkStream.h"
#include <exception>

NetworkStream::NetworkStream(SocketPtr _pSocket)
{
	m_pSocket = _pSocket;
}

bool NetworkStream::CanRead() const
{
	return m_pSocket->IsConnected();
}

bool NetworkStream::CanWrite() const
{
	return m_pSocket->IsConnected();
}

S32 NetworkStream::Read(Vector<Byte>& _vBuffer_, S32 _iOffset, S32 _iSize)
{
	if (_iOffset < 0) {
		throw std::out_of_range("_iOffset is less than 0");
	} else if (_iOffset > (S32)_vBuffer_.size()) {
		throw std::out_of_range("_iOffset is greater than the length of _vBuffer_");
	} else if (_iSize < 0) {
		throw std::out_of_range("_iSize is less than 0");
	} else if (_iSize > (S32)_vBuffer_.size() - _iOffset) {
		throw std::out_of_range("_iSize is greater than the length of _vBuffer_ minus the value of the _iOffset parameter");
	}

	Vector<Byte> vBuffer(_vBuffer_.data() + _iOffset, _vBuffer_.data() + _iOffset + _iSize);
	S32 iResult = m_pSocket->Receive(vBuffer);
	_vBuffer_.swap(vBuffer);
	return iResult;
}

S32 NetworkStream::ReadByte()
{
	Vector<Byte> vBuffer(1);
	m_pSocket->Receive(vBuffer);
	return vBuffer[0];
}

S32 NetworkStream::Write(const Vector<Byte>& _vBuffer, S32 _iOffset, S32 _iSize)
{
	if (_iOffset < 0) {
		throw std::out_of_range("_iOffset is less than 0");
	} else if (_iOffset > (S32)_vBuffer.size()) {
		throw std::out_of_range("_iOffset is greater than the length of _vBuffer_");
	} else if (_iSize < 0) {
		throw std::out_of_range("_iSize is less than 0");
	} else if (_iSize > (S32)_vBuffer.size() - _iOffset) {
		throw std::out_of_range("_iSize is greater than the length of _vBuffer_ minus the value of the _iOffset parameter");
	}

	Vector<Byte> vBuffer(_vBuffer.data() + _iOffset, _vBuffer.data() + _iOffset + _iSize);
	return m_pSocket->Send(vBuffer);
}

void NetworkStream::WriteByte(Byte _Value)
{
	Vector<Byte> vBuffer(1, _Value);
	m_pSocket->Send(vBuffer);
}

void NetworkStream::Close()
{
	m_pSocket->Close();
}
