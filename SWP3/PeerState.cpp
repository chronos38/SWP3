#include "PeerState.h"

void PeerState::ChangeState(PeerContext* _pPeerContext, PeerStatePtr _pState) const
{
	_pPeerContext->ChangeState(_pState);
}
