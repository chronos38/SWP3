#include "PeerState.h"

PeerStatePtr PeerReady::Instance()
{
	static PeerStatePtr spInstance(new PeerReady());
	return spInstance;
}

void PeerReady::Connect(PeerContext* _pPeerContext, const String& _sHost, const String& _sService)
{
	TcpClientPtr pClient;
	Vector<AddressPtr> vAddresses = IAddress::GetHostAddresses(SocketType::Stream, _sHost, _sService);

	for (AddressPtr pAddress : vAddresses) {
		try {
			pClient = ITcpClient::Create(pAddress);
			break;
		} catch (SocketException&) {
			continue;
		}
	}

	if (!pClient) {
		throw PeerStateException("Could not create socket");
	} else {
		ChangeState(_pPeerContext, PeerStatePtr(new PeerAlive(pClient)));
	}
}

void PeerReady::Listen(PeerContext* _pPeerContext, const String& _sHost, const String& _sService)
{
	TcpListenerPtr pListener;
	Vector<AddressPtr> vAddresses = IAddress::GetHostAddresses(SocketType::Stream, _sHost, _sService);

	for (AddressPtr pAddress : vAddresses) {
		try {
			pListener = ITcpListener::Create(pAddress);
			break;
		} catch (SocketException&) {
			continue;
		}
	}

	if (!pListener) {
		throw PeerStateException("Could not create socket");
	} else {
		ChangeState(_pPeerContext, PeerStatePtr(new PeerListen(pListener)));
	}
}

void PeerReady::Open(PeerContext* _pPeerContext)
{
}

void PeerReady::Close(PeerContext* _pPeerContext)
{
}

void PeerReady::SendString(PeerContext* _pPeerContext, const String& _sMessage)
{
}

void PeerReady::SendData(PeerContext* _pPeerContext, const Vector<Byte>& _vBuffer)
{
}

void PeerReady::ReceiveString(PeerContext* _pPeerContext, String& _sMessage_)
{
}

void PeerReady::ReceiveData(PeerContext* _pPeerContext, Vector<Byte>& _vBuffer_)
{
}
