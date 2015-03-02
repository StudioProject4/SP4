#pragma once

#include <stdio.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <GL/glext.h>

#include "RenderUntilty.h"
#include "Entity.h"

class CFrameRateManager:public CEntity
{
public:
	int frameCount;
	float fps;
	int currentTime;
	int previousTime;
	long timelastcall;
	float frequency;
	float deltaTime;
	void *font_style;
	float timethreeshold;

	static CFrameRateManager* instance;
private:
	bool Update();
	CFrameRateManager(void);
public:
	static CFrameRateManager* GetInstance();
	~CFrameRateManager(void);
	bool Init();
	bool Reset();
	bool CleanUp();
	bool Exit();
	bool UpdateAndCheckTimeThreehold();
	void drawFPS(float xpos = 25.f,float ypos = 25.f);
	void CalculateFPS();
	//void printw (float x, float y, float z, char* format, ...);
};

