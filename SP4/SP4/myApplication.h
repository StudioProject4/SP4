#pragma once

#include <stdio.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <GL/glext.h>

#include <iostream>
#include "FrameRateManager.h"
#include "RenderUntilty.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "LuaManager.h"

#include "DatatypeDefination.h"
#include "myLibrary.h"
#include "GameStateManager.h"
#include "MenuState.h"
#include "MalayFemale.h"
#include "ChineseMale.h"
#include "AI.h"
#include "WindowManager.h"

#include "PowerUp.h"
#include "Map.h"

#include "MusicSystem\MusicSystem.h"


class myApplication:public CGameState
{
public:
	static myApplication* instance;
private:
	//bool myKeys[255];
	//void *font_style;
	//int frameCount;
	//float fps;
	//int currentTime;
	//int previousTime;
	//long timelastcall;
	//float frequency;

	TextureImage testimage;
public:
	static myApplication* GetInstance();
	~myApplication(void);

	void InputKey(int key, int x, int y);
	void KeyboardDown(unsigned char key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);
	void MouseMove (int x, int y);
	void MouseClick(int button, int state, int x, int y);
	void MouseWheel(int button, int dir, int x, int y);
	void changeSize (int w, int h);

	bool Init();
	bool CleanUp();
	bool Reset();

	void Render2D();
	void Render3D();
	void RenderScene();

	//CFrameRateManager* FRM;
	//CLuaManager* LM;
	//CMouse* mouse;
	//CKeyboard* keyboard;
	

private:
	myApplication(void);
	
	bool Update();
	void SetHUD(bool m_bHUDmode);

	//temp instance until object manager is done
	CChineseMale * playerOne; 
	CMalayFemale * playerTwo;
	CAILogic * theAI;
	CMap* Map;
	CPowerUp* PowerUp;


	//Imagee
	TextureImage BackgroundTexture[2];
	TextureImage TileMapTexture[50];
	int mapOffset_x, mapOffset_y;
	int tileOffset_x, tileOffset_y;
	int mapFineOffset_x, mapFineOffset_y;
	int theNumOfTiles_Height;
	int theNumOfTiles_Width;
	int rearWallOffset_x, rearWallOffset_y;
	int rearWalltileOffset_x, rearWalltileOffset_y;
	int rearWallFineOffset_x, rearWallFineOffset_y;
	
	void RenderTileMap();
	void RenderBackground();

	//void printw (float x, float y, float z, char* format, ...);
	//void calculateFPS();
	//void drawFPS();
	
	//bool LoadTGA(TextureImage *texture,const char *filename);
	//bool LoadTGA(TextureImage *texture,char *filename);
};

