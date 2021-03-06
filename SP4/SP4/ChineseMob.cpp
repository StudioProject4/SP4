#include "CodeDefination.h"


#ifdef NETWORK_CODE
#include "RakNet\WindowsIncludes.h"
#include "RakNet\RakPeerInterface.h"
#include "RakNet\BitStream.h"
#include "MyMsgIDs.h"
#endif

#include "myApplication.h"

#include "ChineseMob.h"
#include "Character.h"
#include "ImageManager.h"

extern RakNet::RakPeerInterface* rakPeerGlobal;

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
	
	AI.SetCharacterPos(myApplication::GetInstance()->playerTwo->pos);
	if(charControl==1||charControl==3)
	{
		dir = AI.GetDir();
		//pos.x = 
		pos = AI.Update(pos);//,phys);
		if(MVCTime::GetInstance()->TestTime(refTime))
		{
			RakNet::BitStream bs;
			unsigned char msgid=ID_OBJ_UPDATE;

			bs.Write(msgid);
			bs.Write(genericTag);
			bs.Write(true);//mode;
			bs.Write(this->id);
			bs.Write(pos.x);
			bs.Write(pos.y);
		
			rakPeerGlobal->Send(&bs,HIGH_PRIORITY,RELIABLE_ORDERED,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true);
		}
		/*if(AI.state == AI_WANDER)
		{
			pos.x = phys.Update(pos).x;
		}*/
		theSprite->LiveOn(4);
	}
	return true;
}
bool CChineseMob :: Init()
{
	name = "ChineseMob";
	tag = "ChineseMob";
	genericTag = "Enemy";

	AI.SetTag(tag);
	AI.SetID(id);

	theSprite = new CSprite(8,2,0);
	CImageManager::GetInstance()->RegisterTGA("mobChinese.tga");
	theSprite->OverrideTGATexture(CImageManager::GetInstance()->GetTGAImage("mobChinese.tga"));

	phys.Init(pos,Vector3(theSprite->GetImageSizeX(),theSprite->GetImageSizeY(),1));
	this->UpdateObjectTopLeftAndBottomRightPoint(false);

	refTime = MVCTime::GetInstance()->PushNewTime(1000);
	//setting up timer class
	//Timer = MVCTime :: GetInstance();
	//refTime = Timer->PushNewTime(1000);
	
	//if i want reset timer
	//Timer->SetActive(false,refTime);
	//Timer->ResetTime(refTime);

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
	if(dir.x > 0)
	{
		theSprite->SetAnimationLayer(0);
	}
	else if(dir.x < 0)
	{
		theSprite->SetAnimationLayer(1);
	}
	theSprite->Render();
	glPopMatrix();

	return true;
}

bool CChineseMob :: OnCollision2(CBaseObject* a_obj,bool again)
{
	if(a_obj->genericTag == "Character")
	{
		if(a_obj->tag == "MalayFemale")
		{
			CCharacter* temp=(CCharacter*)a_obj;
			if(temp->GetIsInvulnerable() == false)
			{
				temp->hp.TakeDMG();
				temp->SetIsInvulnerable(true);
				//temp->invulTimer->ResetTime(refTime);
				
				unsigned char msgID=ID_OBJ_UPDATE;
				RakNet::BitStream bs;
				bs.Write(msgID);
				bs.Write(genericTag);
				bs.Write(false);//mode
				bs.Write(this->tag);
				bs.Write(this->id);
				bs.Write(a_obj->id);
				bs.Write(temp->hp.GetHealth());
				rakPeerGlobal->Send(&bs,HIGH_PRIORITY,RELIABLE_ORDERED,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true);
			}
		}
	}
	return true;
}

void CChineseMob :: SetPos(Vector3 newPos)
{
	this->pos = newPos;
	AI.SetOriPos(newPos);
}

void CChineseMob :: SetUpMap(CMap theMap)
{
	AI.pathFinding.SetUpGraph(theMap);
}