#include "CodeDefination.h"

#ifdef NETWORK_CODE
#include "RakNet\WindowsIncludes.h"
#include "RakNet\RakPeerInterface.h"
#include "RakNet\BitStream.h"
#include "MyMsgIDs.h"
#endif

#include "MalayMob.h"
#include "Character.h"
#include "ImageManager.h"

CMalayMob :: CMalayMob()
{
	Init();
}
CMalayMob :: ~CMalayMob()
{
	if(theSprite != NULL)
	{
		delete theSprite;
		theSprite = NULL;
	}
}
bool CMalayMob :: Update()
{
	dir = AI.GetDir();
	//pos.x = 
	pos = AI.Update(pos);//,phys);
	/*if(AI.state == AI_WANDER)
	{
		pos.x = phys.Update(pos).x;
	}*/
	return true;
}
bool CMalayMob :: Init()
{
	name = "MalayMob";
	tag = "MalayMob";
	genericTag = "Enemy";

	theSprite = new CSprite(1,1,0);
	theSprite->OverrideTGATexture(CImageManager::GetInstance()->GetTGAImage("rockyground.tga"));
	//theSprite->LoadTGA("rockyground.tga");
	
	phys.Init(pos,Vector3(theSprite->GetImageSizeX(),theSprite->GetImageSizeY(),1));
	this->UpdateObjectTopLeftAndBottomRightPoint(false);

	timer = clock();

	return true;
}	
bool CMalayMob :: Reset()
{
	Init();
	return true;
}
bool CMalayMob :: CleanUp()
{
	return true;
}
bool CMalayMob :: Render()
{
	glPushMatrix();
	glTranslatef(pos.x,pos.y,pos.z);
	theSprite->Render();
	glPopMatrix();

	return true;
}

bool CMalayMob :: OnCollision2(CBaseObject* a_obj,bool again)
{

	if(clock() - timer > 5000)
	{
#ifdef NETWORK_CODE
	if(a_obj->genericTag == "Character")
	{
		if(a_obj->tag == "ChineseMale")
		{
			CCharacter* temp=(CCharacter*)a_obj;
			temp->hp.TakeDMG();
			cout << temp->hp.GetHealth() << endl;
			unsigned char msgID=ID_OBJ_UPDATE;
			RakNet::BitStream bs;
			bs.Write(msgID);
			bs.Write(this->id);
			bs.Write(this->tag);
			bs.Write(a_obj->id);
			bs.Write(temp->hp.GetHealth());
			RakNet::RakPeerInterface::GetInstance()->Send(&bs,HIGH_PRIORITY,RELIABLE_ORDERED,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true);
		}
	}
#endif
	timer = clock();
	}

	return true;
}

void CMalayMob :: SetPos(Vector3 newPos)
{
	this->pos = newPos;
	AI.SetOriPos(newPos);
}

void CMalayMob :: SetUpMap(CMap theMap)
{
	AI.pathFinding.SetUpGraph(theMap);
}