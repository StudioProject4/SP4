#include "CodeDefination.h"

#ifdef NETWORK_CODE
#include "RakNet\BitStream.h"
#include "RakNet\RakPeerInterface.h"
#include "MyMsgIDs.h"
using namespace RakNet;
#endif

#include "BaseObject.h"

extern RakNet::RakPeerInterface* rakPeerGlobal;

bool CBaseObject::OnCollision(CBaseObject* a_obj,bool frame2)
{
	if(frame2!=frame)
	{
		#ifdef NETWORK_CODE
			long now=timeGetTime();
			if(now-lastCall>200)
			{
				BitStream bs;
				unsigned char msgID=ID_COLLISION;
				bs.Write(msgID);
				bs.Write(this->id);
				bs.Write(a_obj->id);
				rakPeerGlobal->Send(&bs,HIGH_PRIORITY,RELIABLE_ORDERED,0,UNASSIGNED_SYSTEM_ADDRESS,true);
				lastCall=now;
			}
		#endif
		frame=frame2;
		return OnCollision2(a_obj);
	}
	else
	{
		return false;
	}
}