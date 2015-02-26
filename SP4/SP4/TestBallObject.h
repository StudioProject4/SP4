#pragma once

class CTestBallObject
{
public:
	float radius;
	float colour_red;
	float colour_blue;
	float colour_green;
	float posX;
	float posY;
	float velocityX;
	float velocityY;
	float delta_theta ;
public:
	CTestBallObject(void);
	~CTestBallObject(void);
	void Update();
	void Render();
	void SetVelocity(float x,float y);
	void SetPosition(float x,float y = -1);
	void SetColour(float red,float green = -1,float blue = -1);
	void Move(float posx = 0,float posy = 0);
	void PrintDebugInformation();
};
typedef CTestBallObject ball;


