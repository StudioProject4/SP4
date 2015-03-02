#include "CodeDefination.h"

#ifdef NETWORK_CODE
#include "RakNet\WindowsIncludes.h"
#include "RakNet\RakPeerInterface.h"
#include "RakNet\BitStream.h"
#include "MyMsgIDs.h"
using namespace RakNet;
#endif

#include "myApplication.h"
#include "ManufactureManager.h"
#include "LeverDoor.h"
#include "Door.h"
#include "PowerUpFactory.h"
#include <mmsystem.h>
#include <string>

RakNet::RakPeerInterface* rakPeerGlobal;


myApplication* myApplication::instance = NULL;

myApplication::myApplication(void)
	: Map(NULL)
#ifdef NETWORK_CODE
	,rakpeer_(RakPeerInterface::GetInstance())
#endif
{
	//Init();
}
myApplication* myApplication::GetInstance()
{
	if(instance==NULL)
	{
		instance = new myApplication();
	}
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

//bool myApplication::Init(bool setMultiplayer)
bool myApplication::Init()
{
	inited = true;

#ifdef NETWORK_CODE
	std::ifstream inData;	
	std::string serverip;

	inData.open("serverip.txt");

	inData >> serverip;
	
	//startupServer("server.exe");

	//*
	if (RAKNET_STARTED == rakpeer_->Startup(1,&SocketDescriptor(), 1))
	{
		rakpeer_->SetOccasionalPing(true);
		if (!RAKNET_STARTED == rakpeer_->Connect(serverip.c_str(), 1691, 0, 0))
		{
			cout<<"failed";
			//return false;
		}
	}
	rakPeerGlobal=rakpeer_;
#endif
	tag = "application";
	name = "myApplication";
	
	glEnable(GL_TEXTURE_2D);


	//background
	LoadTGA( &BackgroundTexture[0], "back.tga");

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
	OM = new CObjectManager();
	
	GSM->currentState = GSM->STATE_MYAPPLICATION;

	playerOne = OM->manufacturer->CreateChineseMale();
	playerTwo = OM->manufacturer->CreateMalayFemale();
	theAIOne = OM->manufacturer->CreateMalayMob();
	theAITwo = OM->manufacturer->CreateChineseMob();
	
	playerOne->Init(Vector3(64,64),Vector3(0,0,0),0);
	playerTwo->Init(Vector3(84,20,0),Vector3(0,0,0),0);
	theAIOne->SetPos(Vector3(600,200,0));
	theAITwo->SetPos(Vector3(300,100,0));


	CLeverDoor* lever= OM->manufacturer->CreateObstacleLeverDoor();
	lever->Init(Vector3(LM->GetWithCheckNumber<float>("LEVER_POS_X"),LM->GetWithCheckNumber<float>("LEVER_POS_Y")),Vector3(LM->GetWithCheckNumber<float>("LEVER_SIZE_X"),LM->GetWithCheckNumber<float>("LEVER_SIZE_Y")));
	CDoor* door= OM->manufacturer->CreateObstacleDoor();
	door->Init(Vector3(LM->GetWithCheckNumber<float>("DOOR_POS_X"),LM->GetWithCheckNumber<float>("DOOR_POS_Y")),Vector3(LM->GetWithCheckNumber<float>("DOOR_SIZE_X"),LM->GetWithCheckNumber<float>("DOOR_SIZE_Y")));

	lever->SetDoorLink(door);
	door->AddTrigger(lever);

	// add all the Game Object into the object manager
#ifndef DEBUG_MODE
	OM->AddObject(playerOne);
	OM->AddObject(playerTwo);
	OM->AddObject(theAIOne);
	OM->AddObject(theAITwo);
	OM->AddObject(lever);
	OM->AddObject(door);
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
	theAIOne->SetUpMap(*Map);
	theAITwo->SetUpMap(*Map);
	theAIOne->phys.map=Map;
	theAITwo->phys.map=Map;

#ifdef NETWORK_CODE
	isMultiplayer = false;
		charControl=3;

#endif

	//Map->RunMap();

	theNumOfTiles_Height = Map->getNumOfTiles_ScreenHeight();
	theNumOfTiles_Width = Map->getNumOfTiles_ScreenWidth();

	return true;
}


bool myApplication::Update()
{
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

#ifdef NETWORK_CODE
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
							playerOne->pos.Set(x,y,z);
							playerOne->hp.SetHealth(currentHp);
						}
						else if(thing2=="MalayFemale")
						{
							playerTwo->pos.Set(x,y,z);
							playerTwo->hp.SetHealth(currentHp);
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
					}
					else 
					{
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
				short charControl;
				float x,y,z,x1,y1,z1;
				bs.Read(charControl);
				if(charControl==3)
					break;
				bs.Read(x);
				bs.Read(y);
				bs.Read(z);
				bs.Read(x1);
				bs.Read(y1);
				bs.Read(z1);
				switch(charControl)
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
			}
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
					temp1->OnCollision2(temp2);
				}
				else
				{
					assert(true);
					int i=0;
				}
			}
			break;
		}

	}
	{
		if(keyboard->myKeys['a'])
		{
			if(charControl==1||charControl==3)
			{
				if(playerOne->phys.vel.x>=0)
					velChanged=true;		
				playerOne->MoveLeft();
			}
			else if(charControl==2)
			{
				if(playerTwo->phys.vel.x>=0)
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
		if(keyboard->myKeys['s'])
		{
		
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
			if(keyboard->myKeys['k'] == true)
			{
		
			}

		}
		if(velChanged==true)
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
#endif

		if(keyboard->myKeys[VK_ESCAPE] == true)
		{
			GSM->ExitApplication();
		}
		
		if(FRM->UpdateAndCheckTimeThreehold())
		{
			theAIOne->AI.SetEnemyPos(playerOne->pos);
			//theAIOne->Update();
			theAITwo->AI.SetEnemyPos(playerTwo->pos);
			//theAITwo->Update();
		
		}
		

		OM->Update(charControl);



#ifdef NETWORK_CODE
	//OM->Update(charControl);
#endif

	Map->RunMap();
		
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
		glBindTexture(GL_TEXTURE_2D, BackgroundTexture[0].texID );
		glPushMatrix();
			glBegin(GL_QUADS);
				int height = 100 * 1.333/1.5;
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

void myApplication::Render2D()
{	
	
	RenderBackground();
	RenderTileMap();

#ifdef DEBUG_CODE
	//uncomment this to render the spatial partition grid

	this->OM->SP->RenderGrid();
#endif


	OM->Render();
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
			
			temp = OM->FetchObjectWithName("ball");
			std::cout<<temp<<std::endl;
			if(temp)
			{
				temp->phys.size.Set(100,100);
			}else
			{
				std::cout<<"nothing came out"<<std::endl;
			}
		break;

		case '2':
			//CGameStateManager::GetInstance()->ChangeState(CMenuState::GetInstance());
			//this->PrintDebugInformation();
			//MS->PlayBgmTrack("bgm2.mp3");
			//MS->PlaySoundTrack(1);
			//std::cout<<MS->currentSoundTrack<<std::endl;
			//MS->PlaySoundPoolTrack2D("sound2.mp3");
			//ballList[0]->active = false;
			temp = OM->FindObjectWithName("ball");
			temp->active = false;
		break;
		
		case '3':
			MS->PrintSoundPoolList();
			//MS->TranverseSoundTrack();
			
			break;
		case '4':
			MS->PrintCurrentSoundTrack();
			
			break;
		case '5':
			MS->ResetSoundTrackPlayPosition(MS->currentSoundTrack);
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
			OM->PrintDebugAllInActiveObjects();
			break;
		case '8':
			//OM->PrintDebugInformation();
			OM->PrintDebugAllActiveObjects();
			break;
		case '9':
			//GSM->GoBackToPreviousState();
			break;
		case 'c':
			system("cls");
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
	mouse->lastX = x;
	mouse->lastY = y;

	switch (button) {

		case GLUT_LEFT_BUTTON:
			mouse->mLButtonUp = state;		
			break;

		case GLUT_RIGHT_BUTTON:
			mouse->mRButtonUp = state;		
			break;

		case GLUT_MIDDLE_BUTTON:
			mouse->middleButtonUp = state;
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

#ifdef NETWORK_CODE
void myApplication::startupServer(LPCTSTR lpApplicationName)
{
	// additional information
	
	// set the size of the structures
	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );

	// start the program up
	CreateProcess( lpApplicationName,   // the path
		NULL,			// Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi );          // Pointer to PROCESS_INFORMATION structure
}

void myApplication::closeServer()
{
	// Close process and thread handles. 
	CloseHandle( pi.hProcess );
	CloseHandle( pi.hThread );
}
#endif
