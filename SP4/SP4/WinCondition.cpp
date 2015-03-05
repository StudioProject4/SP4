#include "CodeDefination.h"
#ifdef NETWORK_CODE
#include "RakNet\BitStream.h"
#include "RakNet\RakPeerInterface.h"
#include "MyMsgIDs.h"
using namespace RakNet;
#endif
#include "WinCondition.h"
#include "myApplication.h"

extern RakNet::RakPeerInterface* rakPeerGlobal;

CWinCondition::CWinCondition(void)
	: ChineseMaleIn(false)
	, MalayFemaleIn(false)
	, levelChange(NULL)
{
	genericTag = "WinCondition";
	name = "WinLose";
	tag = "WC";
}
	
CWinCondition::~CWinCondition(void)
{
	if(theSprite != NULL)
	{
		delete theSprite;
		theSprite = NULL;
	}
}

bool CWinCondition::Render()
{
	glPushMatrix();
	glTranslatef(pos.x,pos.y,pos.z);
	theSprite->Render();
	glPopMatrix();
	return true;
}
	
bool CWinCondition::Update()
{
	if(CM->hp.GetHealth() == 0 || MF->hp.GetHealth() == 0)
	{
		CM->hp.SetHealth(3);
		MF->hp.SetHealth(3);
		myApplication::GetInstance()->ResetLevel(levelChange->Level);
	}

	return true;
}
	
bool CWinCondition::Init(Vector3 pos, Vector3 size)
{
	theSprite = new CSprite(1,1,0);
	theSprite->LoadTGA("MalayVillage.tga");
	this->pos=pos;
	phys.Init(pos, Vector3(theSprite->GetImageSizeX(), theSprite->GetImageSizeY()));

	MF = myApplication::GetInstance()->playerTwo;
	CM=myApplication::GetInstance()->playerOne;

	return true;
}
	
bool CWinCondition::OnCollision(CBaseObject* a_obj, bool frame2)
{
	if(frame != frame2)
	{
		ChineseMaleIn = false;
		MalayFemaleIn = false;

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
				
				if(a_obj->tag=="MalayFemale")//means that it can win
				{
					bs.Reset();
					msgID=ID_REQUEST_MAP_CLEAR;
					bs.Write(msgID);
					bs.Write(this->id);
					rakPeerGlobal->Send(&bs,HIGH_PRIORITY,RELIABLE_ORDERED,0,UNASSIGNED_SYSTEM_ADDRESS,true);
				}
			}
		#endif
		frame = frame2;
	}else
	{	
	}

		//if(this->active == true)
		{
			//if(ChineseMaleIn == false && MalayFemaleIn == false)
			{
				if(a_obj->tag == "ChineseMale")
				{
					ChineseMaleIn = true;
				}
				if(a_obj->tag == "MalayFemale")
				{
					MalayFemaleIn = true;
				}
			}

			
		}
		
			if(ChineseMaleIn == true && MalayFemaleIn == true)
			{
				if(levelChange->Level >= 1 && levelChange->Level < 5)
				{
					levelChange->Level += 1;
					myApplication::GetInstance()->ResetLevel(levelChange->Level);
				}else
				if(levelChange->Level >5)
				{
					levelChange->Level = 5;
					myApplication::GetInstance()->gameStateWin = true;
				}

				RakNet::BitStream bs;
				unsigned char msgid=ID_NEW_MAP;
				bs.Write(msgid);
				bs.Write(levelChange->Level);
				rakPeerGlobal->Send(&bs,HIGH_PRIORITY,RELIABLE_ORDERED,0,UNASSIGNED_SYSTEM_ADDRESS,true);
				return false;
			}

	return OnCollision2(a_obj, true);
}
	
void CWinCondition::LevelChange()
{
	/*if(ChineseMaleIn == true && MalayFemaleIn == true)
	{
		lvC.Level += 1;
	}*/
}

void CWinCondition::LoseGame()
{
	//if(CM->hp.GetHealth() <= 0 || MF->hp.GetHealth() <= 0)
	//{
	//	myApplication::GetInstance()->ResetLevel(1);
	//}
}
