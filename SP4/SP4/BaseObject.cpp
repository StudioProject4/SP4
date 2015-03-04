#include "CodeDefination.h"
#include "MusicSystem\MusicSystem.h"
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
		//if(this->tag == a_obj->tag)
		//	return true;
		//this->numberOfTimeCollided++;
		//a_obj->numberOfTimeCollided++;
		//std::cout<<"this tag"<<this->tag<<"active: "<<this->active <<" collided:"<<this->numberOfTimeCollided<<std::endl;
		//std::cout<<"that tag"<<a_obj->tag<<"active: "<<this->active <<" collided:"<<a_obj->numberOfTimeCollided<<std::endl;
		////++this->numberOfTimeCollided;
		////++a_obj->numberOfTimeCollided;

		//if(this->active && a_obj->active && this->numberOfTimeCollided <= 1 && a_obj->numberOfTimeCollided <= 1)
		//{
		//	std::cout<<"play sound"<<std::endl;
		//	CMusicSystem::GetInstance()->PlaySoundPoolTrack2D("sound1.mp3");//playing the sound cause a little lag when collided.
		//	//this->numberOfTimeCollided = 1000;
		//   // a_obj->numberOfTimeCollided = 1000;
		//}
		
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
		return true;
	}
}