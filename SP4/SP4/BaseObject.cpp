#include "RakNet\BitStream.h"
#include "RakNet\RakPeerInterface.h"
#include "BaseObject.h"
#include "MyMsgIDs.h"
using namespace RakNet;

bool CBaseObject::OnCollision(CBaseObject* a_obj)
{
	BitStream bs;
	unsigned char msgID=ID_COLLISION;
	bs.Write(msgID);
	bs.Write(this->id);
	bs.Write(a_obj->id);
	RakPeerInterface::GetInstance()->Send(&bs,HIGH_PRIORITY,RELIABLE_ORDERED,0,UNASSIGNED_SYSTEM_ADDRESS,true);
	
	return OnCollision2(a_obj);
}