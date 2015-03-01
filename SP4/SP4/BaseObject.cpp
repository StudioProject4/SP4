#include "CodeDefination.h"

#ifdef NETWORK_CODE
#include "RakNet\BitStream.h"
#include "RakNet\RakPeerInterface.h"
#include "MyMsgIDs.h"
using namespace RakNet;
#endif

#include "BaseObject.h"

bool CBaseObject::OnCollision(CBaseObject* a_obj)
{

#ifdef NETWORK_CODE
	BitStream bs;
	unsigned char msgID=ID_COLLISION;
	bs.Write(msgID);
	bs.Write(this->id);
	bs.Write(a_obj->id);
	RakPeerInterface::GetInstance()->Send(&bs,HIGH_PRIORITY,RELIABLE_ORDERED,0,UNASSIGNED_SYSTEM_ADDRESS,true);
#endif

	return OnCollision2(a_obj);
}