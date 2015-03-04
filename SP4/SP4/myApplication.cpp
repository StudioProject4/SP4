#include "CodeDefination.h"

#ifdef NETWORK_CODE
#include "RakNet\WindowsIncludes.h"
#include "RakNet\RakPeerInterface.h"
#include "RakNet\BitStream.h"
#include "MyMsgIDs.h"
using namespace RakNet;
#endif

#include "myApplication.h"
#include "OptionState.h"
#include "ManufactureManager.h"
#include "LeverDoor.h"
#include "Door.h"
#include "PowerUpFactory.h"
#include <mmsystem.h>
#include <string>

RakNet::RakPeerInterface* rakPeerGlobal;

bool sendPos=true;

myApplication* myApplication::instance = NULL;

myApplication::myApplication(void)
	: Map(NULL)
#ifdef NETWORK_CODE
	,rakpeer_(RakPeerInterface::GetInstance())
	,timeRef(-1)
#endif
{
	//Init();
}
myApplication* myApplication::GetInstance(bool multiplayer,string ip)
{
	if(instance==NULL)
	{
		instance = new myApplication();
		
	}
	instance->isMultiplayer=multiplayer;
	instance->serverip=ip;
	
	return instance;
}

myApplication::~myApplication(void)
{
#ifdef NETWORK_CODE
	rakpeer_->Shutdown(100);
	RakPeerInterface::DestroyInstance(rakpeer_);
#endif
}

char** myApplication::argv=NULL;

bool myApplication::CleanUp()
{

	if(Map != NULL)
	{
		delete Map;
		Map = NULL;
	}	
	if(playerOneHud != 0)
	{
		delete playerOneHud;
		playerOneHud = 0;
	}
	if(playerTwoHud != 0)
	{
		delete playerTwoHud;
		playerTwoHud = 0;
	}
	//if(playerOne != NULL)
	//{
	//	delete playerOne;
	//	playerOne = NULL;
	//}
	//if(playerTwo != NULL)
	//{
	//	delete playerTwo;
	//	playerTwo - NULL;
	//}
	//if(theAIOne != NULL)
	//{
	//	delete theAIOne;
	//	theAIOne = NULL;
	//}
	//if(theAITwo != NULL)
	//{
	//	delete theAITwo;
	//	theAITwo = NULL;
	//}
	if(instance != NULL)
	{
		Release();
		instance = NULL;
	}
	return true;

}
bool myApplication::Reset()
{
	return Init();
}
bool myApplication::ResetLevel(short level)
{

	OM->LoadingSetup();
	Map->Level=level;
	Map->RunMap();

	theNumOfTiles_Height = Map->getNumOfTiles_ScreenHeight();
	theNumOfTiles_Width = Map->getNumOfTiles_ScreenWidth();
	switch(level)
	{
	case 1:
		{

			playerOne->Init(Vector3(LM->GetWithCheckNumber<float>("PLAYERONE_POS_X_Lv1"),LM->GetWithCheckNumber<float>("PLAYERONE_POS_Y_Lv1")),Vector3(0,0,0),0);
			playerTwo->Init(Vector3(LM->GetWithCheckNumber<float>("PLAYERTWO_POS_X_Lv1"),LM->GetWithCheckNumber<float>("PLAYERTWO_POS_Y_Lv1"),0),Vector3(0,0,0),0);
			
			//OM->AddObject(theAIOne);
			//OM->AddObject(theAITwo);
		}

		break;
	case 2:
		{

			playerOne->Init(Vector3(LM->GetWithCheckNumber<float>("PLAYERONE_POS_X_Lv2"),LM->GetWithCheckNumber<float>("PLAYERONE_POS_Y_Lv2")),Vector3(0,0,0),0);
			playerTwo->Init(Vector3(LM->GetWithCheckNumber<float>("PLAYERTWO_POS_X_Lv2"),LM->GetWithCheckNumber<float>("PLAYERTWO_POS_Y_Lv2"),0),Vector3(0,0,0),0);

			CLeverDoor* lever= OM->manufacturer->CreateObstacleLeverDoor();
			lever->Init(Vector3(LM->GetWithCheckNumber<float>("LEVER1_POS_X_Lv2"),LM->GetWithCheckNumber<float>("LEVER1_POS_Y_Lv2")),Vector3(LM->GetWithCheckNumber<float>("LEVER_SIZE_X"),LM->GetWithCheckNumber<float>("LEVER_SIZE_Y")));
			CLeverDoor* lever2 = OM->manufacturer->CreateObstacleLeverDoor();
			lever2->Init(Vector3(LM->GetWithCheckNumber<float>("LEVER2_POS_X_Lv2"),LM->GetWithCheckNumber<float>("LEVER2_POS_Y_Lv2")),Vector3(LM->GetWithCheckNumber<float>("LEVER_SIZE_X"),LM->GetWithCheckNumber<float>("LEVER_SIZE_Y")));
	
			CDoor* door= OM->manufacturer->CreateObstacleDoor();
			door->Init(Vector3(LM->GetWithCheckNumber<float>("DOOR1_POS_X_Lv2"),LM->GetWithCheckNumber<float>("DOOR1_POS_Y_Lv2")),Vector3(LM->GetWithCheckNumber<float>("DOOR_SIZE_X"),LM->GetWithCheckNumber<float>("DOOR_SIZE_Y")));
			CDoor* door2 = OM->manufacturer->CreateObstacleDoor();
			door2->Init(Vector3(LM->GetWithCheckNumber<float>("DOOR2_POS_X_Lv2"),LM->GetWithCheckNumber<float>("DOOR2_POS_Y_Lv2")),Vector3(LM->GetWithCheckNumber<float>("DOOR_SIZE_X"),LM->GetWithCheckNumber<float>("DOOR_SIZE_Y")));
	
			lever->SetDoorLink(door);
			door->AddTrigger(lever);
			lever2->SetDoorLink(door2);
			door2->AddTrigger(lever2);
			OM->AddObject(lever);
			OM->AddObject(lever2);
			OM->AddObject(door);
			OM->AddObject(door2);

		}


		break;
	case 3:
		{
		
			theAIOne = OM->manufacturer->CreateMalayMob();
			theAITwo = OM->manufacturer->CreateChineseMob();
			playerOne->Init(Vector3(LM->GetWithCheckNumber<float>("PLAYERONE_POS_X_Lv3"),LM->GetWithCheckNumber<float>("PLAYERONE_POS_Y_Lv3")),Vector3(0,0,0),0);
			playerTwo->Init(Vector3(LM->GetWithCheckNumber<float>("PLAYERTWO_POS_X_Lv3"),LM->GetWithCheckNumber<float>("PLAYERTWO_POS_Y_Lv3"),0),Vector3(0,0,0),0);
			theAIOne->SetPos(Vector3(LM->GetWithCheckNumber<float>("AIONE_POS_X_Lv3"),LM->GetWithCheckNumber<float>("AIONE_POS_Y_Lv3"),0));
			theAITwo->SetPos(Vector3(LM->GetWithCheckNumber<float>("AITWO_POS_X_Lv3"),LM->GetWithCheckNumber<float>("AITWO_POS_Y_Lv3"),0));
			theAIOne->SetUpMap(*Map);
			theAITwo->SetUpMap(*Map);
			theAIOne->phys.map=Map;
			theAITwo->phys.map=Map;
			
			OM->AddObject(theAIOne);
			OM->AddObject(theAITwo);
		}

		break;
	case 4:
		{
			theAIOne = OM->manufacturer->CreateMalayMob();
			theAITwo = OM->manufacturer->CreateChineseMob();
			playerOne->Init(Vector3(LM->GetWithCheckNumber<float>("PLAYERONE_POS_X_Lv4"),LM->GetWithCheckNumber<float>("PLAYERONE_POS_Y_Lv4")),Vector3(0,0,0),0);
			playerTwo->Init(Vector3(LM->GetWithCheckNumber<float>("PLAYERTWO_POS_X_Lv4"),LM->GetWithCheckNumber<float>("PLAYERTWO_POS_Y_Lv4"),0),Vector3(0,0,0),0);
			theAIOne->SetPos(Vector3(LM->GetWithCheckNumber<float>("AIONE_POS_X_Lv4"),LM->GetWithCheckNumber<float>("AIONE_POS_Y_Lv4"),0));
			theAITwo->SetPos(Vector3(LM->GetWithCheckNumber<float>("AITWO_POS_X_Lv4"),LM->GetWithCheckNumber<float>("AITWO_POS_Y_Lv4"),0));
			theAIOne->SetUpMap(*Map);
			theAITwo->SetUpMap(*Map);
			theAIOne->phys.map=Map;
			theAITwo->phys.map=Map;

			CLeverDoor* lever= OM->manufacturer->CreateObstacleLeverDoor();
			lever->Init(Vector3(LM->GetWithCheckNumber<float>("LEVER_POS_X_Lv4"),LM->GetWithCheckNumber<float>("LEVER_POS_Y_Lv4")),Vector3(LM->GetWithCheckNumber<float>("LEVER_SIZE_X"),LM->GetWithCheckNumber<float>("LEVER_SIZE_Y")));
			CLeverDoor* lever2 = OM->manufacturer->CreateObstacleLeverDoor();
			lever2->Init(Vector3(LM->GetWithCheckNumber<float>("LEVER2_POS_X_Lv4"),LM->GetWithCheckNumber<float>("LEVER2_POS_Y_Lv4")),Vector3(LM->GetWithCheckNumber<float>("LEVER_SIZE_X"),LM->GetWithCheckNumber<float>("LEVER_SIZE_Y")));
			CDoor* door= OM->manufacturer->CreateObstacleDoor();
			door->Init(Vector3(LM->GetWithCheckNumber<float>("DOOR_POS_X_Lv4"),LM->GetWithCheckNumber<float>("DOOR_POS_Y_Lv4")),Vector3(LM->GetWithCheckNumber<float>("DOOR_SIZE_X"),LM->GetWithCheckNumber<float>("DOOR_SIZE_Y")));
			CDoor* door2 = OM->manufacturer->CreateObstacleDoor();
			door2->Init(Vector3(LM->GetWithCheckNumber<float>("DOOR2_POS_X_Lv4"),LM->GetWithCheckNumber<float>("DOOR2_POS_Y_Lv4")),Vector3(LM->GetWithCheckNumber<float>("DOOR_SIZE_X"),LM->GetWithCheckNumber<float>("DOOR_SIZE_Y")));
	
			lever->SetDoorLink(door);
			door->AddTrigger(lever);
			
			lever2->SetDoorLink(door2);
			door2->AddTrigger(lever2);

			OM->AddObject(lever);
			OM->AddObject(lever2);
			OM->AddObject(door);
			OM->AddObject(door2);
			OM->AddObject(theAIOne);
			OM->AddObject(theAITwo);
		}

		break;
	case 5:
		{
			theAIOne = OM->manufacturer->CreateMalayMob();
			theAITwo = OM->manufacturer->CreateChineseMob();
			playerOne->Init(Vector3(LM->GetWithCheckNumber<float>("PLAYERONE_POS_X_Lv5"),LM->GetWithCheckNumber<float>("PLAYERONE_POS_Y_Lv5")),Vector3(0,0,0),0);
			playerTwo->Init(Vector3(LM->GetWithCheckNumber<float>("PLAYERTWO_POS_X_Lv5"),LM->GetWithCheckNumber<float>("PLAYERTWO_POS_Y_Lv5"),0),Vector3(0,0,0),0);
			theAIOne->SetPos(Vector3(LM->GetWithCheckNumber<float>("AIONE_POS_X_Lv5"),LM->GetWithCheckNumber<float>("AIONE_POS_Y_Lv5"),0));
			theAITwo->SetPos(Vector3(LM->GetWithCheckNumber<float>("AITWO_POS_X_Lv5"),LM->GetWithCheckNumber<float>("AITWO_POS_Y_Lv5"),0));
			theAIOne->SetUpMap(*Map);
			theAITwo->SetUpMap(*Map);
			theAIOne->phys.map=Map;
			theAITwo->phys.map=Map;

			CLeverDoor* lever= OM->manufacturer->CreateObstacleLeverDoor();
			lever->Init(Vector3(LM->GetWithCheckNumber<float>("LEVER_POS_X_Lv5"),LM->GetWithCheckNumber<float>("LEVER_POS_Y_Lv5")),Vector3(LM->GetWithCheckNumber<float>("LEVER_SIZE_X"),LM->GetWithCheckNumber<float>("LEVER_SIZE_Y")));
			CLeverDoor* lever2 = OM->manufacturer->CreateObstacleLeverDoor();
			lever2->Init(Vector3(LM->GetWithCheckNumber<float>("LEVER2_POS_X_Lv5"),LM->GetWithCheckNumber<float>("LEVER2_POS_Y_Lv5")),Vector3(LM->GetWithCheckNumber<float>("LEVER_SIZE_X"),LM->GetWithCheckNumber<float>("LEVER_SIZE_Y")));
			CDoor* door= OM->manufacturer->CreateObstacleDoor();
			door->Init(Vector3(LM->GetWithCheckNumber<float>("DOOR_POS_X_Lv5"),LM->GetWithCheckNumber<float>("DOOR_POS_Y_Lv5")),Vector3(LM->GetWithCheckNumber<float>("DOOR_SIZE_X"),LM->GetWithCheckNumber<float>("DOOR_SIZE_Y")));
			CDoor* door2 = OM->manufacturer->CreateObstacleDoor();
			door2->Init(Vector3(LM->GetWithCheckNumber<float>("DOOR2_POS_X_Lv5"),LM->GetWithCheckNumber<float>("DOOR2_POS_Y_Lv5")),Vector3(LM->GetWithCheckNumber<float>("DOOR_SIZE_X"),LM->GetWithCheckNumber<float>("DOOR_SIZE_Y")));
	

			lever->SetDoorLink(door);
			door->AddTrigger(lever);
			
			lever2->SetDoorLink(door2);
			door2->AddTrigger(lever2);

			OM->AddObject(lever);
			OM->AddObject(lever2);
			OM->AddObject(door);
			OM->AddObject(door2);
			OM->AddObject(theAIOne);
			OM->AddObject(theAITwo);
		}

		break;
	}



		
	return true;

}
//bool myApplication::Init(bool setMultiplayer)
bool myApplication::Init()
{
	inited = true;
	points=CPointSystem::GetInstance();
#ifdef NETWORK_CODE
	
	//startupServer("server.exe");

	//*
	if(isMultiplayer)
	{
		if (RAKNET_STARTED == rakpeer_->Startup(1,&SocketDescriptor(), 1))
		{
			rakpeer_->SetOccasionalPing(true);
			if (!RAKNET_STARTED == rakpeer_->Connect(serverip.c_str(), 1691, 0, 0))
			{
				cout<<"failed";
				//return false;
			}
		}
	}
	else
	{
		rakpeer_->Shutdown(100);
	}
	rakPeerGlobal=rakpeer_;
	if(timeRef==-1)
	{
		timeRef=MVCTime::GetInstance()->PushNewTime(80);
	}
#endif
	tag = "application";
	name = "myApplication";
	
	theAIOne=0;
	theAITwo=0;

	glEnable(GL_TEXTURE_2D);


	//background
	//LoadTGA( &BackgroundTexture[0], "back.tga");
	
	LoadTGA( &TileMapTexture[0], "BlackWalls.tga");
	LoadTGA( &TileMapTexture[1], "tile0_blank.tga");
	//LoadTGA( &TileMapTexture[1], "LavaGround.tga");
	LoadTGA( &TileMapTexture[2], "BlackWallCut.tga");
	LoadTGA( &TileMapTexture[3], "HealthCross.tga");
	LoadTGA( &TileMapTexture[4], "SpeedUp.tga");
	LoadTGA( &TileMapTexture[5], "Invincible.tga");
	LoadTGA( &TileMapTexture[6], "PointsAdd.tga");
	LoadTGA( &TileMapTexture[7], "Jump.tga");
	LoadTGA( &TileMapTexture[8], "ChineseSign.tga");
	LoadTGA( &TileMapTexture[9], "HalalSign.tga");
	LoadTGA( &TileMapTexture[10], "MalayVillage.tga");
	//LoadTGA( &TileMapTexture[0], "tile0_blank");


	glDisable(GL_TEXTURE_2D);


	//getting instance of managers
	FRM = CFrameRateManager::GetInstance();
	LM = CLuaManager::GetInstance();
	mouse = CMouse::GetInstance();
	keyboard = CKeyboard::GetInstance();
	WM = CWindowManager::GetInstance();
	MS = CMusicSystem::GetInstance();
	GSM = CGameStateManager::GetInstance();
	IM = CImageManager::GetInstance();
	OM = new CObjectManager();

#ifndef PRELOAD_TEXTURE
	IM->RegisterTGA("background.tga");
	IM->RegisterTGA("rockyground.tga");
	IM->RegisterTGA("health.tga");
	IM->RegisterTGA("pointIcon.tga");

	//test image
	IM->RegisterTGA("sonia2.tga");
	IM->RegisterTGA("tenri.tga");
#endif


	tempimage = IM->GetTGAImage("background.tga");
	GSM->currentState = GSM->STATE_MYAPPLICATION;

	if(MS->GetCurrentBgm()->audioname != "bgm6.mp3")
	{
		if(MS->StopCurrentBGM())
		{
			MS->PlayBgmTrack("bgm6.mp3");
			//std::cout<<"finding"<<MS->FindBgm("bgm6.mp3")<<std::endl;
			if(MS->FindBgm("bgm6.mp3")->EnableAudioEffectControl())
			{
				MS->FindBgm("bgm6.mp3")->EnableChorusEffect();
			}
		}
	}


	
	HeartShape.Init(1);
	HeartShape.OverrideTGATexture(IM->GetTGAImage("health.tga"));
	PointIcon.Init(1);
	PointIcon.OverrideTGATexture(IM->GetTGAImage("pointIcon.tga"));
	GameLose.Init(1);
	GameLose.OverrideTGATexture(IM->GetTGAImage("sonia2.tga"));
	GameWin.Init(1);
	GameWin.OverrideTGATexture(IM->GetTGAImage("tenri.tga"));

	playerOne = OM->manufacturer->CreateChineseMale();
	playerTwo = OM->manufacturer->CreateMalayFemale();
	//theAIOne = OM->manufacturer->CreateMalayMob();
	//theAITwo = OM->manufacturer->CreateChineseMob();

	playerOne->Init(Vector3(LM->GetWithCheckNumber<float>("PLAYERONE_POS_X_START"),LM->GetWithCheckNumber<float>("PLAYERONE_POS_Y_START")),Vector3(0,0,0),0);
	playerTwo->Init(Vector3(LM->GetWithCheckNumber<float>("PLAYERTWO_POS_X_START"),LM->GetWithCheckNumber<float>("PLAYERTWO_POS_Y_START"),0),Vector3(0,0,0),0);
	//theAIOne->SetPos(Vector3(LM->GetWithCheckNumber<float>("AIONE_POS_X_START"),LM->GetWithCheckNumber<float>("AIONE_POS_Y_START"),0));
	//theAITwo->SetPos(Vector3(LM->GetWithCheckNumber<float>("AITWO_POS_X_START"),LM->GetWithCheckNumber<float>("AITWO_POS_Y_START"),0));

	playerOneHud = new CSprite(*playerOne->theSprite);
	playerTwoHud = new CSprite(*playerTwo->theSprite);

	//CLeverDoor* lever= OM->manufacturer->CreateObstacleLeverDoor();
	//lever->Init(Vector3(LM->GetWithCheckNumber<float>("LEVER_POS_X_START"),LM->GetWithCheckNumber<float>("LEVER_POS_Y_START")),Vector3(LM->GetWithCheckNumber<float>("LEVER_SIZE_X"),LM->GetWithCheckNumber<float>("LEVER_SIZE_Y")));
	//CDoor* door= OM->manufacturer->CreateObstacleDoor();
	//door->Init(Vector3(LM->GetWithCheckNumber<float>("DOOR_POS_X_START"),LM->GetWithCheckNumber<float>("DOOR_POS_Y_START")),Vector3(LM->GetWithCheckNumber<float>("DOOR_SIZE_X"),LM->GetWithCheckNumber<float>("DOOR_SIZE_Y")));

	//lever->SetDoorLink(door);
	//door->AddTrigger(lever);
	//
	// add all the Game Object into the object manager
#ifndef DEBUG_MODE
	OM->AddObject(playerOne);
	OM->AddObject(playerTwo);
	////OM->AddObject(theAIOne);
	//OM->AddObject(theAITwo);
	//OM->AddObject(lever);
	//OM->AddObject(door);
#endif

#ifdef DEBUG_MODE
	CTestBallObject *newball = new ball;
	newball->SetPosition( 10,20);
	newball->id = 1;
	ballList.push_back(newball);
	OM->AddObject(newball);

	//newball = new ball;
	//newball->SetPosition(300,400);
	//newball->SetColour(0,1,0);
	//newball->radius = 100.f;
	//ballList.push_back(newball);
	//OM->AddObject(newball);

	//newball = new ball;
	//newball->SetPosition(100,100);
	//newball->SetColour(0,0,1);
	//newball->radius = 20.f;
	//ballList.push_back(newball);
	//OM->AddObject(newball);
#endif
	 mapOffset_x =  mapOffset_y=
	 tileOffset_x =tileOffset_y=
	 mapFineOffset_x= mapFineOffset_y=
	 theNumOfTiles_Height
	= theNumOfTiles_Width
	= rearWallOffset_x=rearWallOffset_y
	 =rearWalltileOffset_x= rearWalltileOffset_y
	= rearWallFineOffset_x= rearWallFineOffset_y = 0;

	//map
	Map = new CMap(this->OM);
	Map->Init(SCREEN_HEIGHT,SCREEN_WIDTH*2,SCREEN_HEIGHT,SCREEN_WIDTH*2,TILE_SIZE);
	Map->RunMap();

	playerTwo->phys.map=Map;
	playerOne->phys.map=Map;
	//theAIOne->SetUpMap(*Map);
	//theAITwo->SetUpMap(*Map);
	//theAIOne->phys.map=Map;
	//theAITwo->phys.map=Map;

#ifdef NETWORK_CODE
		charControl=3;

#endif

	//Map->RunMap();

	theNumOfTiles_Height = Map->getNumOfTiles_ScreenHeight();
	theNumOfTiles_Width = Map->getNumOfTiles_ScreenWidth();
	this->ResetLevel(Map->Level);
	return true;
}

void myApplication::StateChangeMusicCheck()
{
	if(MS->GetCurrentBgm()->audioname != "bgm6.mp3")
	{
		if(MS->StopCurrentBGM())
		{
			MS->PlayBgmTrack("bgm6.mp3");
		}
	}
};

bool myApplication::Update()
{
	StateChangeMusicCheck();
	//use for debugging spatial partition inside myApplication
#ifdef DEBUG_MODE
	if(keyboard->myKeys['a'])
	{
		ballList[0]->SetVelocity(-5,0);
	}
	if(keyboard->myKeys['d'])
	{
		ballList[0]->SetVelocity(5,0);
	}
	if(keyboard->myKeys['w'])
	{
		ballList[0]->SetVelocity(0,-5);
	}
	if(keyboard->myKeys['s'])
	{
		ballList[0]->SetVelocity(0,5);
	}
	if(keyboard->myKeys['r'])
	{
		ballList[0]->radius *= 0.5;
	}
	if(keyboard->myKeys['t'])
	{
		ballList[0]->radius*=2;
	}
	if(keyboard->myKeys[VK_SPACE] == true)
	{
		ballList[0]->SetVelocity(0,0);
	}
#endif

	if (Packet* packet = rakpeer_->Receive())
	{
		RakNet::BitStream bs(packet->data, packet->length, false);
		
		unsigned char msgid = 0;
		RakNet::Time timestamp = 0;

		bs.Read(msgid);

		if (msgid == ID_TIMESTAMP)
		{
			bs.Read(timestamp);
			bs.Read(msgid);
		}

		switch(msgid)
		{
		case ID_GAME_PACKAGE:
			{
				int objNum=0;
				int mapNum;

				bs.Read(mapNum);
				bs.Read(objNum);
				Map->Level=mapNum;
				OM->LoadingSetup();
				vector<CLeverDoor*> leverList;
				vector<CDoor*> doorList;
				vector<int> doorRefList;
				vector<CHealthPU* > healthList;
				vector<CPointsAddPU* > pointsaddList;
				vector<CInvinciblePU* > invincibleList;
				vector<CJumpPU* > jumpList;
				vector<CSpeedPU* > speedList;
				vector<CChinesePoints* > chinaptsList;
				vector<CMalayPoints* > malayptsList;

				charControl=2;//if you recieve this u are for sure player 2

				char* genTag=new char[256];
				char* tag=new char[256];
				for(int i=0;i<objNum;++i)
				{
					float x,y,z;
					unsigned short id;
					bs.Read(genTag);
					bs.Read(tag);
					bs.Read(id);
					bs.Read(x);
					bs.Read(y);
					bs.Read(z);
					string thing;
					string thing2;
					thing=genTag;
					thing2=tag;
					if(thing=="Character")
					{
						int currentHp;
						bs.Read(currentHp);
						if(thing2=="ChineseMale")
						{
							//playerOne->pos.Set(x,y,z);
							playerOne->hp.SetHealth(currentHp);
							playerOne->id=id;
						}
						else if(thing2=="MalayFemale")
						{
							//playerTwo->pos.Set(x,y,z);
							playerTwo->hp.SetHealth(currentHp);
							playerTwo->id=id;
						}
					}
					else if(thing2=="CLeverDoor")
					{
						float angle;
						int doorID;
						bs.Read(angle);
						bs.Read(doorID);
						CLeverDoor* temp=CManufactureManager::GetInstance()->CreateObstacleLeverDoor();
						temp->Init(Vector3(x,y,z),Vector3(LM->GetWithCheckNumber<float>("LEVER_SIZE_X"),LM->GetWithCheckNumber<float>("LEVER_SIZE_Y")));
						temp->curAngle=angle;
						temp->id=id;
						OM->AddObject(temp);
						leverList.push_back(temp);
						doorRefList.push_back(doorID);												
					}
					else if(thing2=="CDoor")
					{
						CDoor* temp=CManufactureManager::GetInstance()->CreateObstacleDoor();
						temp->Init(Vector3(x,y,z),Vector3(LM->GetWithCheckNumber<float>("DOOR_SIZE_X"),LM->GetWithCheckNumber<float>("DOOR_SIZE_Y")));
						temp->id=id;
						OM->AddObject(temp);
						doorList.push_back(temp);

					}else if(thing2 == "CHINAS")
					{
						CChinesePoints* temp = CManufactureManager::GetInstance()->CreateChinesePoints();
						temp->Init(Vector3(x,y,z),Vector3(temp->phys.size));
						temp->pos.Set(x,y,z);
						temp->id = id;
						OM->AddObject(temp);
						chinaptsList.push_back(temp);

					}else if(thing2 == "MALAYS")
					{
						CMalayPoints* temp = CManufactureManager::GetInstance()->CreateMalayPoints();
						temp->Init(Vector3(x,y,z), Vector3(temp->phys.size));
						temp->pos.Set(x,y,z);
						temp->id = id;
						OM->AddObject(temp);
						malayptsList.push_back(temp);
					}
					else if(thing2 == "CHp")
					{
						//CChineseHpReduce* temp = CManufactureManager::GetInstance()->cre
					}
					else if(thing2 == "MHp")
					{

					}
					else if(thing2 == "HpAdd")
					{
						CHealthPU* temp = CManufactureManager::GetInstance()->CreatePowerUpRecovery();
						temp->Init();
						temp->pos.Set(x,y,z);
						temp->id = id;					
						OM->AddObject(temp);
						healthList.push_back(temp);
					}else if(thing2 == "PtAdd")
					{
						CPointsAddPU* temp = CManufactureManager::GetInstance()->CreatePowerUpPoints();
						temp->Init();
						temp->pos.Set(x,y,z);
						temp->id = id;
						OM->AddObject(temp);
						pointsaddList.push_back(temp);
					}else if(thing2 == "Invin")
					{
						CInvinciblePU* temp = CManufactureManager::GetInstance()->CreatePowerUpInvincible();
						temp->Init();
						temp->pos.Set(x,y,z);
						temp->id = id;
						OM->AddObject(temp);
						invincibleList.push_back(temp);
					}else if(thing2 == "JpUp")
					{
						CJumpPU* temp = CManufactureManager::GetInstance()->CreatePowerUpJumpHigh();
						temp->Init();
						temp->pos.Set(x,y,z);
						temp->id = id;
						OM->AddObject(temp);
						jumpList.push_back(temp);
					}else if(thing2 == "SpdUp")
					{
						CSpeedPU* temp = CManufactureManager::GetInstance()->CreatePowerUpSpeedUp();
						temp->Init();
						temp->pos.Set(x,y,z);
						temp->id = id;
						OM->AddObject(temp);
						speedList.push_back(temp);
					}
					else if(thing == "Enemy")
					{
						if(thing2 == "MalayMob")
						{
							CMalayMob * temp =  CManufactureManager::GetInstance()->CreateMalayMob(); 
							temp->Init();
							temp->SetUpMap(*Map);
							temp->SetPos(Vector3(x,y,z));
							temp->id = id;
							OM->AddObject(temp);
						}
						else if(thing2 == "ChineseMob")
						{
							CChineseMob * temp = CManufactureManager::GetInstance()->CreateChineseMob();
							temp->Init();
							temp->SetUpMap(*Map);
							temp->SetPos(Vector3(x,y,z));
							temp->id = id;
							OM->AddObject(temp);
						}
					}
					else if(thing2=="WC")
					{
						CWinCondition * temp = CManufactureManager::GetInstance()->CreateWinCondition();
						temp->Init(Vector3(x,y,z),Vector3(32,32));
						temp->id = id;
						temp->levelChange=Map;
						OM->AddObject(temp);
					}
				}
				delete[256] tag;
				delete[256] genTag; 
				vector<int>::iterator it2=doorRefList.begin();
				for(vector<CLeverDoor*>::iterator it=leverList.begin();it!=leverList.end()&&it2!=doorRefList.end();++it2,++it)
				{
					for(vector<CDoor*>::iterator it3=doorList.begin();it3!=doorList.end();++it3)
					{
						if((*it3)->id==(*it2))
						{
							(*it3)->AddTrigger((*it));
							(*it)->SetDoorLink((*it3));
							break;
						}
					}
				}
			}
			break;
		case ID_VEL_CHANGED:
			{
				short charControl1;
				float x,y,z,x1,y1,z1;
				bs.Read(charControl1);
				if(charControl==3)
					break;
				bs.Read(x);
				bs.Read(y);
				bs.Read(z);
				bs.Read(x1);
				bs.Read(y1);
				bs.Read(z1);
				switch(charControl1)
				{
				case 1:
					playerOne->phys.vel.Set(x,y,z);
					playerOne->pos.Set(x1,y1,z1);
					break;
				case 2:
					playerTwo->phys.vel.Set(x,y,z);
					playerTwo->pos.Set(x1,y1,z1);
					break;
				}
			}
			break;
		case ID_CLIENT_DISCONNECT:
			{
				charControl=3;//if the other guy disconnect u now control both
			}
			break;
		case ID_WELCOME:
			{

			}
			break;
		case ID_NEW_PLAYER:
			{
				charControl=1;//if you recieve this you are for sure player 1

				BitStream bs2;
				unsigned char msgID=ID_GAME_PACKAGE;
				bs2.Write(msgID);
				bs2.Write(Map->Level);
				OM->WriteAllObjects(bs2);
				rakpeer_->Send(&bs2,HIGH_PRIORITY,RELIABLE_ORDERED,0,UNASSIGNED_SYSTEM_ADDRESS,true);
			}
			break;
		case ID_OBJ_UPDATE:
			{
				char* temp=new char[256];
				bs.Read(temp);
				string temp2=temp;
				if(temp2=="CLeverDoor")
				{
					unsigned short id1,id2;
					bs.Read(id1);
					bs.Read(id2);
					cout<<"id of the objects"<<id1<<" "<<id2<<"\n";
					CLeverDoor* lever=NULL;
					CBaseObject* other=NULL;
					for(vector<CBaseObject*>::iterator it=OM->objectList.begin();it!=OM->objectList.end();++it)
					{
						if(id1==(*it)->id)
						{
							lever=(CLeverDoor*)(*it);
						}
						else if(id2==(*it)->id)
						{
							other=(*it);
						}
						if(lever!=NULL&&other!=NULL)
						{
							break;
						}
					}
					if(lever==0||other==0)
						break;

					float x,y,z;
					
					bs.Read(x);
					bs.Read(y);
					lever->curAngle=x;
					lever->angleVel=y;

					bs.Read(x);
					bs.Read(y);
					bs.Read(z);
					other->pos.Set(x,y,z);

					bs.Read(x);
					bs.Read(y);
					bs.Read(z);
					other->phys.vel.Set(x,y,z);
				}

				else if(temp2=="Enemy")
				{
					bool mode;
					bs.Read(mode);
					if(mode)
					{
						float x, y;
						unsigned short id;
						bs.Read(id);
						//read pos
						bs.Read(x);
						bs.Read(y);

						CBaseObject* temp;
						
						for(vector<CBaseObject*>::iterator it=OM->objectList.begin();it!=OM->objectList.end();++it)
						{
							if(id==(*it)->id)
							{
								temp=(CBaseObject*)(*it);
								break;
							}
						}
						temp->pos.Set(x,y,0);
						//set pos

					}
					else
					{
						unsigned short id1,id2;
						int hp;
						bs.Read(temp);//tag
						temp2=temp;
						bs.Read(id1);
						bs.Read(id2);
						bs.Read(hp);

						CCharacter* character=NULL;
						for(vector<CBaseObject*>::iterator it=OM->objectList.begin();it!=OM->objectList.end();++it)
						{
							if(id2==(*it)->id)
							{
								character=(CCharacter*)(*it);
								break;
							}
						}
						character->hp.SetHealth(hp);
					}

				}
			}
			break;
		case ID_COLLISION:
			{
				unsigned short id,id2;
				bs.Read(id);
				bs.Read(id2);
				CBaseObject* temp1=NULL;
				CBaseObject* temp2=NULL;
				for(vector<CBaseObject*>::iterator it=OM->objectList.begin();it!=OM->objectList.end();++it)
				{
					if(id==(*it)->id)
					{
						temp1=(*it);
					}
					else if(id2==(*it)->id)
					{
						temp2=(*it);
					}
					if(temp1!=NULL&&temp2!=NULL)
					{
						break;
					}
				}
				if(temp1!=NULL&&temp2!=NULL)
				{
					temp1->OnCollision2(temp2,true);
				}
				else
				{
					assert(true);
					int i=0;
				}
			}
			break;
		case ID_REQUEST_MAP_CLEAR:
			{
				unsigned short id;
				bs.Read(id);
				CWinCondition* temp=0;
				for(vector<CBaseObject*>::iterator it=OM->objectList.begin();it!=OM->objectList.end();++it)
				{
					if(id==(*it)->id)
					{
						temp=(CWinCondition*)(*it);
						break;
					}
				}
				if(temp==0)
					break;
				temp->MalayFemaleIn=true;
				temp->frame=OM->frame;
			}
			break;
		case ID_NEW_MAP:
			{
				int newLevel;
				bs.Read(newLevel);
				Map->Level =newLevel;
				ResetLevel(Map->Level);
				RakNet::BitStream bs2;
				unsigned char msgid=ID_NEW_PLAYER;
				bs2.Write(msgid);
				rakpeer_->Send(&bs2,HIGH_PRIORITY,RELIABLE_ORDERED,0,UNASSIGNED_SYSTEM_ADDRESS,true);
			}
			break;
		}

	}
	{
		if(keyboard->myKeys['a'])
		{
			
			if(charControl==1||charControl==3)
			{
				//if(playerOne->phys.vel.x>=0)
					velChanged=true;		
				playerOne->MoveLeft();
			}
			else if(charControl==2)
			{
				//if(playerTwo->phys.vel.x>=0)
					velChanged=true;	
				playerTwo->MoveLeft();
			}
		}
		if(keyboard->myKeys['d'])
		{
			if(charControl==1||charControl==3)
			{
				//if(playerOne->phys.vel.x<=0)
				{
					velChanged=true;
				}
				playerOne->MoveRight();
			}
			else if(charControl==2)
			{
				//if(playerTwo->phys.vel.x<=0)
				{
					velChanged=true;
				}
				playerTwo->MoveRight();
			}
		}
		if(keyboard->myKeys['w'])
		{
			if(charControl==1||charControl==3)
			{
				if(!playerOne->phys.inAir)
					velChanged=true;
				playerOne->Jump();
			}
			else if(charControl==2)
			{
				if(!playerTwo->phys.inAir)
					velChanged=true;
				playerTwo->Jump();
			}
		}
		if(keyboard->myKeys['p'])
		{
			if(charControl==1||charControl==3)
			{
				
			}
			else if(charControl==2)
			{
				
			}
			//win->OnCollision(playerOne, false);
			//win->OnCollision(playerOne, true);
			playerOne->hp.SetHealth(0);
		}
		if(keyboard->myKeys['a'] == false && keyboard->myKeys['d'] == false)
			{
				if(charControl==1||charControl==3)
					playerOne->phys.vel.x = 0;
				else if(charControl==2)
				{
					playerTwo->phys.vel.x=0;
				}

				keyboard->myKeys['a'] = false;
				keyboard->myKeys['d'] = false;
			}
		if(charControl==3)
		{
			if(keyboard->myKeys['j'] == true)
			{
				//if(playerTwo->phys.vel.x<=0)
					velChanged=true;	
				playerTwo->MoveLeft();
			}
			if(keyboard->myKeys['l'] == true)
			{
				//if(playerTwo->phys.vel.x>=0)
					velChanged=true;	
				playerTwo->MoveRight();
			}
			if(keyboard->myKeys['i'] == true)
			{
				if(!playerTwo->phys.inAir)
					velChanged=true;
				playerTwo->Jump();
			}
			if(keyboard->myKeys['p'] == true)
			{
				
			}
			if(keyboard->myKeys['j'] == false && keyboard->myKeys['l'] == false)
			{
				playerTwo->phys.vel.x = 0;
				keyboard->myKeys['j'] = false;
				keyboard->myKeys['l'] = false;
			}

		}
		if(sendPos)
		{
			if(MVCTime::GetInstance()->TestTime(timeRef))
			{
				//send vel message
				BitStream bs;
				unsigned char msgID=ID_VEL_CHANGED;
				bs.Write(msgID);
				bs.Write(charControl);
				switch(charControl)
				{
				case 1:
					bs.Write(playerOne->phys.vel.x);
					bs.Write(playerOne->phys.vel.y);
					bs.Write(playerOne->phys.vel.z);
					bs.Write(playerOne->pos.x);
					bs.Write(playerOne->pos.y);
					bs.Write(playerOne->pos.z);
					break;
				case 2:
					bs.Write(playerTwo->phys.vel.x);
					bs.Write(playerTwo->phys.vel.y);
					bs.Write(playerTwo->phys.vel.z);
					bs.Write(playerTwo->pos.x);
					bs.Write(playerTwo->pos.y);
					bs.Write(playerTwo->pos.z);
					break;
				}
				rakpeer_->Send(&bs,HIGH_PRIORITY,RELIABLE_ORDERED,0,UNASSIGNED_SYSTEM_ADDRESS,true);
				velChanged=false;
			}
		}
		else
		{
			MVCTime::GetInstance()->ResetTime(timeRef);
		}
		sendPos=true;
	}


		if(keyboard->myKeys[VK_ESCAPE] == true)
		{
			GSM->ChangeState(COptionState::GetInstance());
		}
		
		if(FRM->UpdateAndCheckTimeThreehold())
		{
			if(theAIOne!=0)
				theAIOne->AI.SetCharacterPos(playerOne->pos);
			//theAIOne->Update();
			if(theAITwo!=0)
				theAITwo->AI.SetCharacterPos(playerTwo->pos);
			//theAITwo->Update();
		
		}
		
		MVCTime::GetInstance()->UpdateTime();
		OM->Update(charControl);


	//Map->RunMap();
	
//	win->
		
	return true;
}
void myApplication::RenderTileMap()
{
	glEnable(GL_TEXTURE_2D);
	mapFineOffset_x = mapOffset_x % TILE_SIZE;
	
	glPushMatrix();
	//glScalef(WM->GetWindowWidth()/800,WM->GetWindowHeight()/600,1);

	for (int i = 0; i < theNumOfTiles_Height; i++)
	{
		for (int k = 0; k < theNumOfTiles_Width + 1; k++)
		{
			// If we have reached the right side of the Map, then do not display the extra column of tiles.
			if ((tileOffset_x + k) >= Map->getNumOfTiles_MapWidth())
				break;
			glPushMatrix();
			glTranslatef((GLfloat)(k * TILE_SIZE - mapFineOffset_x), (GLfloat)(i * TILE_SIZE), 0.0f);
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture(GL_TEXTURE_2D, TileMapTexture[Map->theScreenMap[i][tileOffset_x + k]].texID);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 1); glVertex2f(0, 0);
			glTexCoord2f(0, 0); glVertex2f(0, TILE_SIZE);
			glTexCoord2f(1, 0); glVertex2f(TILE_SIZE, TILE_SIZE);
			glTexCoord2f(1, 1); glVertex2f(TILE_SIZE, 0);
			glEnd();
			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
			glPopMatrix();
		}
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}
void myApplication::RenderBackground()
{
	glEnable(GL_TEXTURE_2D);

	// Draw Background image
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		//glBindTexture(GL_TEXTURE_2D, BackgroundTexture[0].texID);
		glBindTexture(GL_TEXTURE_2D, IM->GetTGAImage("background.tga")->texID);
		
		//glBindTexture(GL_TEXTURE_2D, tempimage->texID);
		glPushMatrix();
			glBegin(GL_QUADS);
				//int height = 100 * 1.333f/1.5f;
				glTexCoord2f(0,0); glVertex2f(0,800);
				glTexCoord2f(1,0); glVertex2f(1024,800);
				glTexCoord2f(1,1); glVertex2f(1024,0);
				glTexCoord2f(0,1); glVertex2f(0,0);				
			glEnd();
		glPopMatrix();
		glDisable(GL_BLEND);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	
}

void myApplication::RenderCharacterHealthHud(CCharacter* a_character,float startingPosX,float startingPosY,float paddingX,bool buildToRight)
{
	if(buildToRight)
	{
		glPushMatrix();
		glTranslatef(startingPosX,startingPosY,0);
			for(unsigned short i = 0; i < a_character->hp.GetHealth();++i)
			{
				glTranslatef(paddingX,0,0);
				HeartShape.Render();
			}
		
		glPopMatrix();
	}else
	{
		glPushMatrix();
		glTranslatef(startingPosX,startingPosY,0);
			for(unsigned short i = 0; i < a_character->hp.GetHealth();++i)
			{
				glTranslatef(-paddingX,0,0);
				HeartShape.Render();
			}
		
		glPopMatrix();
	}
}

void myApplication::RenderPointHUD()
{
	glPushMatrix();

	glTranslatef(WM->GetOriginalWindowWidth()*0.5f,PointIcon.GetImageSizeY()*0.5f,0);
			PointIcon.Render();
	glPopMatrix();
			printw(WM->GetOriginalWindowWidth()*0.5f-PointIcon.GetImageSizeX()*0.35f,PointIcon.GetImageSizeY()*1.5f,0," %d",this->points->GetPoints());
}

void myApplication::RenderPlayerOneHUD()
{
	glPushMatrix();

			glPushMatrix();
				playerOneHud->SetImageSize(TILE_SIZE*1.5f,TILE_SIZE*1.5f);
				glTranslatef(WM->GetOriginalWindowWidth()*0.1f,playerOneHud->GetImageSizeY()*0.5f,0);
				playerOneHud->Render();
			glPopMatrix();

			RenderCharacterHealthHud(playerOne,WM->GetOriginalWindowWidth()*0.1f +playerOneHud->GetImageSizeX()*0.5f,playerOneHud->GetImageSizeY()*0.5f,playerOne->theSprite->GetImageSizeX(),true);
	glPopMatrix();
}
void myApplication::RenderPlayerTwoHUD()
{
	glPushMatrix();

			glPushMatrix();
				playerTwoHud->SetImageSize(TILE_SIZE*1.5f,TILE_SIZE*1.5f);
				glTranslatef(WM->GetOriginalWindowWidth()*0.9f,playerTwoHud->GetImageSizeY()*0.5f,0);
				playerTwoHud->Render();
			glPopMatrix();

			RenderCharacterHealthHud( playerTwo, WM->GetOriginalWindowWidth()*0.9f - playerTwoHud->GetImageSizeX()*0.5f, playerTwoHud->GetImageSizeY()*0.5f,playerTwo->theSprite->GetImageSizeX(),false);
	glPopMatrix();
}

void myApplication::RenderLoseResult()
{
	glPushMatrix();
		glTranslatef(WM->GetOriginalWindowWidth()*0.5f,WM->GetOriginalWindowHeight()*0.5f,0);
			GameWin.Render();
	glPopMatrix();
}

void myApplication::RenderWinResult()
{
	glPushMatrix();
		glTranslatef(WM->GetOriginalWindowWidth()*0.5f,WM->GetOriginalWindowHeight()*0.5f,0);
			GameLose.Render();
	glPopMatrix();
}
void myApplication::RenderGameResult(bool gameresult)
{
	if(gameresult == true)
	{
		RenderWinResult();
	}else
	{
		RenderLoseResult();
	}
}
void myApplication::Render2D()
{	
	
	RenderBackground();
	RenderTileMap();
	

	RenderPlayerOneHUD();
	RenderPlayerTwoHUD();
#ifdef DEBUG_CODE
	//uncomment this to render the spatial partition grid

	this->OM->SP->RenderGrid();
#endif

	OM->Render();
	RenderPointHUD();
	FRM->drawFPS();
}
void myApplication::Render3D()
{

}
void myApplication::RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);

	//float deltaTime = (timeGetTime()-timelastcall);
	//
	//if (deltaTime>1000/frequency)
	//{
	//	// Calculate the framerate
	//	calculateFPS();

	//	timelastcall=timeGetTime();

	//	Update();
	//}

	Render3D();

	SetHUD( true );
		Render2D();
	SetHUD( false );
	glDisable(GL_DEPTH_TEST);
	// Flush off any entity which is not drawn yet, so that we maintain the frame rate.
	glFlush();

	// swapping the buffers causes the rendering above to be shown
	glutSwapBuffers();
	glutPostRedisplay();
}
void myApplication::InputUpKey(int key, int x, int y)
{
	switch (key) {
		case GLUT_KEY_LEFT : 
			keyboard->leftArrow = false;
			break;
		case GLUT_KEY_RIGHT : 
			keyboard->rightArrow = false;
			break;
		case GLUT_KEY_UP : 
			keyboard->upArrow = false;
			break;;
		case GLUT_KEY_DOWN : 
			break;
	}
}
void myApplication::InputKey(int key, int x, int y)
{
	switch (key) {
		case GLUT_KEY_LEFT : 
			keyboard->leftArrow = true;
			break;
		case GLUT_KEY_RIGHT : 
			keyboard->rightArrow = true;
			break;
		case GLUT_KEY_UP : 
			keyboard->upArrow = true;
			break;
		case GLUT_KEY_DOWN : 
			break;
	}
}
void myApplication::KeyboardDown(unsigned char key, int x, int y)
{
	keyboard->myKeys[key] = true;
	CBaseObject* temp = nullptr;
	TextureImage* tempimage = nullptr;
	switch(key)
	{
		case '1':
			//this->PrintDebugInformation();
			//mouse->PrintDebugInformation();
			//MS->PlayBgmTrack("bgm1.mp3");
			//MS->PlaySoundTrack(0);
			//std::cout<<MS->currentSoundTrack<<std::endl;
			//MS->FetchSound()->PrintDebugInformation();
			//MS->PlaySoundPoolTrack2D("sound1.mp3");
			//std::cout<<WM->GetWindowRatioDifferenceX()<<std::endl;
			//std::cout<<WM->GetWindowRatioDifferenceY()<<std::endl;
			
			//temp = OM->FetchObjectWithName("ball");
			//std::cout<<temp<<std::endl;
			//if(temp)
			//{
			//	temp->phys.size.Set(100,100);
			//}else
			//{
			//	std::cout<<"nothing came out"<<std::endl;
			//}
			GSM->ExitApplication();
		break;

		case '2':
			playerOne->hp.SetHealth(0);
			//CGameStateManager::GetInstance()->ChangeState(CMenuState::GetInstance());
			//this->PrintDebugInformation();
			//MS->PlayBgmTrack("bgm2.mp3");
			//MS->PlaySoundTrack(1);
			//std::cout<<MS->currentSoundTrack<<std::endl;
			//MS->PlaySoundPoolTrack2D("sound2.mp3");
			//ballList[0]->active = false;
			//temp = OM->FindObjectWithName("ball");
			//temp->active = false;
			MS->StopCurrentBGM();
			
		break;
		
		case '3':
			//MS->PrintSoundPoolList();
			MS->PlayBgmTrack(MS->GetCurrentBgmTrackIndex());
			//MS->TranverseSoundTrack();
			
			break;
		case '4':
		//	MS->PrintCurrentSoundTrack();
			
			break;
		case '5':
		//	MS->ResetSoundTrackPlayPosition(MS->currentSoundTrack);
			break;
		case '6':
			//MS->PrintSoundTrackList();
			//OM->PrintDebugAllInActiveObjects();
			
			break;
		case '7':
			//std::cout<< testmale<<std::endl;
			//testmale->PrintDebugInformation();
			//OM->PrintDebugAllActiveObjects();
			//OM->objectList[0]->UpdateObjectTopLeftAndBottomRightPoint(false);
			//OM->PrintDebugAllInActiveObjects();
			break;
		case '8':
			//OM->PrintDebugInformation();
			//OM->PrintDebugAllActiveObjects();
			break;
		case '9':
			//GSM->GoBackToPreviousState();
			break;
		case 'c':
			//system("cls");
			break;
	}
}

void myApplication::KeyboardUp(unsigned char key, int x, int y)
{
	keyboard->myKeys[key]= false;
}

void myApplication::MouseMove (int x, int y)
{
	int diffX = x - mouse->lastX;
	int diffY = y - mouse->lastY;

	mouse->lastX = x;
	mouse->lastY = y;
}
void myApplication::MouseWheel(int button, int dir, int x, int y)
{

}
void myApplication::MouseClick(int button, int state, int x, int y)
{

	switch (button) {
		case GLUT_LEFT_BUTTON:
			switch(state)
			{
				case GLUT_DOWN:
					//mouse->mLButtonUp = true;	
					mouse->SetLeftButton(true);
					break;
				case GLUT_UP:
					//mouse->mLButtonUp = false;	
					mouse->SetLeftButton(false);
					break;
			}
			break;

		case GLUT_RIGHT_BUTTON:

			switch(state)
			{
				case GLUT_DOWN:
					//mouse->mRButtonUp = true;	
					mouse->SetRightButton(true);
					break;
				case GLUT_UP:
					//mouse->mRButtonUp = false;
					mouse->SetRightButton(false);
					break;
			}
			break;

		case GLUT_MIDDLE_BUTTON:
		
			switch(state)
			{
				case GLUT_DOWN:
					//mouse->middleButtonUp = true;	
					mouse->SetMiddleButton(true);
					break;
				case GLUT_UP:
					//mouse->middleButtonUp = false;	
					mouse->SetMiddleButton(false);
					break;
			}
			break;
	}
}
void myApplication::changeSize (int w, int h)
{
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	float ratio = (float) (1.0f* w / h);

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	//WM->SetAndUpdateWindowDimension(w,h);
	//WINDOW_WIDTH = w;
	//WINDOW_HEIGHT = h;
	WM->SetWindowDimension(w,h);
	//std::cout<<"myapp "<<WINDOW_WIDTH<<std::endl;
	// Set the correct perspective.
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
}
void myApplication::SetHUD(bool m_bHUDmode)
{
	if (m_bHUDmode == true)
	{
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();

		//std::cout<<WM->GetWindowWidth()<<std::endl;
		//glOrtho( 0, WM->GetWindowWidth() , WM->GetWindowHeight(), 0, -1, 1 );  
		//glOrtho( 0, 800 , 600, 0, -1, 1 ); 
		glOrtho( 0, WM->GetOriginalWindowWidth() , WM->GetOriginalWindowHeight(), 0, -1, 1 );  

		//std::cout<<"Window width"<<WINDOW_WIDTH<<std::endl;
		//std::cout<<"Window Height"<<WINDOW_HEIGHT<<std::endl;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_TEXTURE_2D);							// Disable Texture Mapping ( NEW )
	}
	else
	{
		//glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glEnable( GL_DEPTH_TEST );

	}
};

