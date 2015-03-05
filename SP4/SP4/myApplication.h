
#include "CodeDefination.h"
#ifdef NETWORK_CODE
#include "RakNet\WindowsIncludes.h"
#include "RakNet\BitStream.h"
#include "RakNet\RakPeerInterface.h"
#endif

#pragma once


#include "MenuState.h"
#include "ChineseMob.h"
#include "ObjectManager.h"
#include "WinCondition.h"

#include "FrameRateManager.h"
#include "RenderUntilty.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "LuaManager.h"

#include "KeeYangTestState.h"
#include "KennardTestState.h"

#include "SplashState.h"

#include "DatatypeDefination.h"

#include "GameStateManager.h"
#include "ImageManager.h"

#include "MalayFemale.h"
#include "ChineseMale.h"
#include "MalayMob.h"
#include "WindowManager.h"

#include "PointSystem.h"
#include "PowerUp.h"
#include "PointsAddPU.h"
#include "HealthPU.h"
#include "InvinciblePU.h"
#include "JumpPU.h"
#include "SpeedPU.h"
#include "Map.h"

#include "ChinesePoints.h"
#include "MalayPoints.h"
#include "ChineseHpReduce.h"
#include "MalayHpReduce.h"

#include "Physics.h"

#include "MusicSystem\MusicSystem.h"

#include "SpatialPartion.h"

#include <stdio.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#include <stdlib.h>
#include <iostream>

class myApplication:public CGameState
{
public:
	static myApplication* instance;
	bool gameStateWin;
private:
	//bool myKeys[255];
	//void *font_style;
	//int frameCount;
	//float fps;
	//int currentTime;
	//int previousTime;
	//long timelastcall;
	//float frequency;
	//CChineseMale* testmale;
	//TextureImage testimage;
public:
	static char** argv;
	static myApplication* GetInstance(bool multiplayerMode=false,std::string ip="127.0.0.1");
	~myApplication(void);

	void InputKey(int key, int x, int y);
	void InputUpKey(int key, int x, int y);
	void KeyboardDown(unsigned char key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);
	void MouseMove (int x, int y);
	void MouseClick(int button, int state, int x, int y);
	void MouseWheel(int button, int dir, int x, int y);
	void changeSize (int w, int h);

	//bool Init(bool setMultiplayer);
	bool Init();
	bool CleanUp();
	bool Reset();
	bool ResetLevel(short level);

	void Render2D();
	void Render3D();
	void RenderScene();
	//CFrameRateManager* FRM;
	//CLuaManager* LM;
	//CMouse* mouse;
	//CKeyboard* keyboard;
	
	
	CChineseMale * playerOne; 
	CMalayFemale * playerTwo;
private:
	myApplication(void);
	
	bool Update();
	void SetHUD(bool m_bHUDmode);

	//temp instance until object manager is done
	CMalayMob * theAIOne;
	CChineseMob * theAITwo;
	CMap* Map;
	CPowerUp* PowerUp;
	CPhysics* Physics;
	CHealthPU Hpadd;
	CPointsAddPU ptsAdd;
	CPointsAddPU* pts;
	CInvinciblePU InvinOn;
	CPointSystem* points;
	CWinCondition* win;
//	CWinCondition w;
	

	int timeRef;

#ifdef NETWORK_CODE
	STARTUPINFO si;     
	PROCESS_INFORMATION pi;
	RakNet::RakPeerInterface* rakpeer_;

	//multiplayer stuff
	bool isMultiplayer;
	std::string serverip;
	
	short charControl;//1: player 1,2: player 2,3: both players

	bool velChanged;

	//something to control who sends what
	int control;

	//end of multiplayer stuff

#endif

	//Imagee
	TextureImage BackgroundTexture[2];
	TextureImage gameoverTexture[1];
	TextureImage TileMapTexture[50];
	TextureImage* tempimage;
	int mapOffset_x, mapOffset_y;
	int tileOffset_x, tileOffset_y;
	int mapFineOffset_x, mapFineOffset_y;
	int theNumOfTiles_Height;
	int theNumOfTiles_Width;
	int rearWallOffset_x, rearWallOffset_y;
	int rearWalltileOffset_x, rearWalltileOffset_y;
	int rearWallFineOffset_x, rearWallFineOffset_y;
	
	CSprite* playerOneHud;
	CSprite* playerTwoHud;
	CSprite HeartShape;
	CSprite PointIcon;
	CSprite GameLose;
	CSprite GameWin;

	void RenderGameResult(bool gameresult);
	void RenderLoseResult();
	void RenderWinResult();
	void RenderTileMap();
	void RenderBackground();
	void RenderPointHUD();
	void RenderPlayerOneHUD();
	void RenderPlayerTwoHUD();
	void RenderCharacterHealthHud(CCharacter* a_character,float startingPosX,float startingPosY,float paddingX,bool buildToRight = true);

	//void printw (float x, float y, float z, char* format, ...);
	//void calculateFPS();
	//void drawFPS();
	
	//bool LoadTGA(TextureImage *texture,const char *filename);
	//bool LoadTGA(TextureImage *texture,char *filename);

	typedef std::vector<ball*> TBallVector;
	TBallVector ballList;


	void StateChangeMusicCheck();

};

