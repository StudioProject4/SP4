#include "CodeDefination.h"

#ifdef NETWORK_CODE
#include "RakNet\WindowsIncludes.h"
#include "RakNet\RakPeerInterface.h"
#include "RakNet\BitStream.h"
#include "MyMsgIDs.h"
#endif

#include "ChineseMob.h"
#include "Character.h"
#include "ImageManager.h"
CChineseMob::CChineseMob()
{
	Init();
}
CChineseMob::~CChineseMob()
{
	if(theSprite != NULL)
	{
		delete theSprite;
		theSprite = NULL;
	}
}
bool CChineseMob :: Update()
{	
	dir = AI.GetDir();
	//pos.x = 
	pos = AI.Update(pos,phys);
	/*if(AI.state == AI_WANDER)
	{
		pos.x = phys.Update(pos).x;
	}*/
	return true;
}
bool CChineseMob :: Init()
{
	name = "ChineseMob";
	tag = "ChineseMob";
	genericTag = "Enemy";

	theSprite = new CSprite(1,1,0);
	theSprite->OverrideTGATexture(CImageManager::GetInstance()->GetTGAImage("tenri.tga"));
	//theSprite->LoadTGA("tenri.tga");

	phys.Init(pos,Vector3(theSprite->GetImageSizeX(),theSprite->GetImageSizeY(),1));
	this->UpdateObjectTopLeftAndBottomRightPoint(false);

	return true;
}
bool CChineseMob :: Reset()
{
	Init();
	return true;
}
bool CChineseMob :: CleanUp()
{
	return true;
}
bool CChineseMob :: Render()
{
	glPushMatrix();
	glTranslatef(pos.x,pos.y,pos.z);
	theSprite->Render();
	glPopMatrix();

	return true;
}

bool CChineseMob :: OnCollision2(CBaseObject* a_obj,bool again)
{
#ifdef NETWORK_CODE
	if(a_obj->genericTag = "Character")
	{
		if(a_obj->tag = "MalayFemale")
		{
			CCharacter* temp=(CCharacter*)a_obj;
			temp->hp.TakeDMG();
			unsigned char msgID=ID_OBJ_UPDATE;
			RakNet::BitStream bs;
			bs.Write(msgID);
			bs.Write(this->tag);
			bs.Write(this->id);
			bs.Write(a_obj->id);
			//bs.Write(temp->hp.GetHealth());
			RakNet::RakPeerInterface::GetInstance()->Send(&bs,HIGH_PRIORITY,RELIABLE_ORDERED,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true);
		}
	}
#endif
	return true;
}

void CChineseMob :: SetPos(Vector3 newPos)
{
	this->pos = newPos;
}

void CChineseMob :: SetUpMap(CMap theMap)
{
	AI.pathFinding.SetUpGraph(theMap);
}