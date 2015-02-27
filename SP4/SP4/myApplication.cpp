#include "RakNet\WindowsIncludes.h"
#include "RakNet\RakPeerInterface.h"
#include "RakNet\BitStream.h"

#include "myApplication.h"
#include "LeverDoor.h"
#include "Door.h"
#include "PowerUpFactory.h"
#include <mmsystem.h>
using namespace RakNet;
myApplication* myApplication::instance = NULL;

myApplication::myApplication(void)
	: Map(NULL)
	,rakpeer_(RakPeerInterface::GetInstance())
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
	rakpeer_->Shutdown(100);
	RakPeerInterface::DestroyInstance(rakpeer_);
}

char** myApplication::argv=NULL;

bool myApplication::CleanUp()
{
	MS->Exit();

	if(Map != NULL)
	{
		delete Map;
		Map = NULL;
	}

	if(instance != NULL)
	{
		Release();
		instance = NULL;
	}
	return true;
	if(playerOne != NULL)
	{
		delete playerOne;
		playerOne = NULL;
	}
	if(playerTwo != NULL)
	{
		delete playerTwo;
		playerTwo - NULL;
	}
	if(theAIOne != NULL)
	{
		delete theAIOne;
		theAIOne = NULL;
	}
	if(theAITwo != NULL)
	{
		delete theAITwo;
		theAITwo = NULL;
	}
	CMusicSystem::GetInstance()->Exit();
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
	//for(unsigned short i = 0; i<255; ++i)
	//{
	//	myKeys[i] = false;
	//}
	
	std::ifstream inData;	
	std::string serverip;

	inData.open("serverip.txt");

	inData >> serverip;
	
	//*
	if (RAKNET_STARTED == rakpeer_->Startup(1,&SocketDescriptor(), 1))
	{
		rakpeer_->SetOccasionalPing(true);
		if (!RAKNET_STARTED == rakpeer_->Connect(serverip.c_str(), 1691, 0, 0))
		{
			cout<<"failed";
			return false;
		}
	}
	//*/
	tag = "application";
	name = "Main Application";

	glEnable(GL_TEXTURE_2D);

	//frameCount = 0;
	//fps = 0;
	//currentTime = 0;
	//previousTime = 0;
	//font_style = GLUT_BITMAP_TIMES_ROMAN_24;
	//timelastcall=timeGetTime();
	//frequency = 30.0f;

	//startupServer("server.exe");

	//loading texture
	//LoadTGA(&testimage,"sonia2.tga");


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
	//LoadTGA( &TileMapTexture[0], "tile0_blank");


	glDisable(GL_TEXTURE_2D);


	//getting instance of managers
	FRM = CFrameRateManager::GetInstance();
	LM = CLuaManager::GetInstance();
	mouse = CMouse::GetInstance();
	keyboard = CKeyboard::GetInstance();
	WM = CWindowManager::GetInstance();
	MS = CMusicSystem::GetInstance();
	OM = new CObjectManager();

	playerOne = OM->manufacturer->CreateChineseMale();
	playerTwo = OM->manufacturer->CreateMalayFemale();
	theAIOne = OM->manufacturer->CreateMalayMob();
	theAITwo = OM->manufacturer->CreateChineseMob();

	playerOne->Init(Vector3(64,64),Vector3(0,0,0),0);
	playerTwo->Init(Vector3(60,20,0),Vector3(0,0,0),0);
	theAIOne->SetPos(Vector3(600,200,0));

	CLeverDoor* lever=new CLeverDoor;
	lever->Init(Vector3(600,568),Vector3(5,50));
	CDoor* door=new CDoor;
	door->Init(Vector3(400,568),Vector3(32,32));
	lever->SetDoorLink(door);
	door->AddTrigger(lever);

	// add all the Game Object into the object manager
	OM->AddObject(playerOne);
	OM->AddObject(playerTwo);
	OM->AddObject(theAIOne);
	OM->AddObject(theAITwo);
	OM->AddObject(lever);
	OM->AddObject(door);


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
	theAIOne->phys.map=Map;
	theAITwo->phys.map=Map;

	isMultiplayer = false;

	////load map
	//if(Map->LevelCount == 1)
	//{
	//	Map->LoadMap("Level1_1.csv");
	//}
	//if(Map->LevelCount == 2)
	//{
	//	Map->LoadMap("Level1_1.csv");
	//}
	//if(Map->LevelCount == 3)
	//{
	//	Map->LoadMap("Level1_1.csv");
	//}
	//if(Map->LevelCount == 4)
	//{
	//	Map->LoadMap("Level1_1.csv");
	//}
	//if(Map->LevelCount == 5)
	//{
	//	Map->LoadMap("Level1_1.csv");
	//}
	
	playerOne->Init(Vector3(64,64),Vector3(0,0,0),0);
	playerTwo->Init(Vector3(60,20,0),Vector3(0,0,0),0);
	theAIOne->SetPos(Vector3(600,200,0));
	theAIOne->SetUpMap(*Map);
	theAITwo->SetPos(Vector3(300,100,0));
	theAITwo->SetUpMap(*Map);
	

	//Map->RunMap();

	theNumOfTiles_Height = Map->getNumOfTiles_ScreenHeight();
	theNumOfTiles_Width = Map->getNumOfTiles_ScreenWidth();

	return true;
}

bool myApplication::Update()
{


	if(!isMultiplayer)
	{
		if(keyboard->myKeys['a'])
		{
			playerOne->MoveLeft();
		}
		if(keyboard->myKeys['d'])
		{
			playerOne->MoveRight();
		}
		if(keyboard->myKeys['w'])
		{
			playerOne->Jump();
		}
		if(!keyboard->myKeys['a']&&!keyboard->myKeys['d'])
		{
			playerOne->phys.vel.x=0;
			keyboard->myKeysUp['a']=false;
			keyboard->myKeysUp['d']=false;
		}
		else if(keyboard->myKeys['s'])
		{
			//playerOne->OnCollision(&Hpadd);
			//playerOne->OnCollision(&ptsAdd);
			ptsAdd.OnCollision(playerOne);
			//Hpadd.OnCollision(playerOne);
			//ptsAdd.OnCollision(&Hpadd);
		}
		
		if(keyboard->leftArrow == true)
		{
			playerTwo->MoveLeft();
		}
		else if(keyboard->rightArrow == true)
		{
			playerTwo->MoveRight();
		}
		else if(keyboard->upArrow == true)
		{
			playerTwo->Jump();
		}

		else if(!keyboard->rightArrow && !keyboard->leftArrow)
		{
			playerTwo->phys.vel.x=0;
			keyboard->rightArrow = false;
			keyboard->leftArrow = false;
		}
		
	}
	else if(isMultiplayer)
	{
		if(keyboard->myKeys['a'])
		{
			//ifplayeroOne
			playerOne->MoveLeft();
			//ifplayerTwo
			playerTwo->MoveLeft();
		}
		if(keyboard->myKeys['d'])
		{
			//ifplayeroOne
			playerOne->MoveRight();
			//ifplayerTwo
			playerTwo->MoveRight();
		}
		if(keyboard->myKeys['w'])
		{
			//ifplayeroOne
			playerOne->Jump();
			//ifplayerTwo
			playerTwo->Jump();
		}
		if(keyboard->myKeys['s'])
		{
		
		}
	}
		if(keyboard->myKeys[VK_ESCAPE] == true)
		{
			exit(0);
		}
		if(keyboard->myKeys['j'] == true)
		{
			playerTwo->MoveLeft();
		}
		if(keyboard->myKeys['l'] == true)
		{
			playerTwo->MoveRight();
		}
		if(keyboard->myKeys['i'] == true)
		{
			playerTwo->Jump();
		}
		if(keyboard->myKeys[VK_ESCAPE] == true)
		{
			exit(0);
			//GSM->PopAndCleanLastState();
		}
		if(keyboard->myKeys['k'] == true)
		{
		
		}
		
	if(FRM->UpdateAndCheckTimeThreehold())
	{
		theAIOne->AI.SetEnemyPos(playerOne->pos);
		//theAIOne->Update();
		theAITwo->AI.SetEnemyPos(playerTwo->pos);
		//theAITwo->Update();
		
	}
	OM->Update();

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
			std::cout<<WM->GetWindowRatioDifferenceX()<<std::endl;
			std::cout<<WM->GetWindowRatioDifferenceY()<<std::endl;
		break;

		case '2':
			//CGameStateManager::GetInstance()->ChangeState(CMenuState::GetInstance());
			//this->PrintDebugInformation();
			//MS->PlayBgmTrack("bgm2.mp3");
			//MS->PlaySoundTrack(1);
			//std::cout<<MS->currentSoundTrack<<std::endl;
			MS->PlaySoundPoolTrack2D("sound2.mp3");
			
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
			OM->PrintDebugAllInActiveObjects();
			break;
		case '7':
			//std::cout<< testmale<<std::endl;
			//testmale->PrintDebugInformation();
			OM->PrintDebugAllActiveObjects();
			break;
		case '8':
			OM->PrintDebugInformation();
			break;
		case '9':
			MS->Exit();
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
