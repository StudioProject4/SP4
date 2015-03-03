#pragma once
#include "Entity.h"

class CMouse:public CEntity
{
public:
	bool mLButtonUp;
	bool mRButtonUp;
	bool middleButtonUp;
	int  lastX, lastY;
	float gameX,gameY;
	float sensitivity;
	bool lastLButtonState;
	bool lastRButtonState;
	bool lastMiddleButtonState;
private:
	static CMouse* instance;
public:
	static CMouse* GetInstance();
	CMouse(void);
	~CMouse(void);
	bool Reset();
	bool Update();
	bool Init() ;
	bool CleanUp();
	//void UpdateMousePosition(int x,int y);
	void SetLeftButton(bool down);
	void SetMiddleButton(bool down);
	void SetRightButton(bool down);
	bool CheckLeftButtonReleased();
	bool CheckRightButtonReleased();
	bool CheckMiddleButtonReleased();
	bool CheckLeftButtonDown();
	bool CheckRightButtonDown();
	bool CheckMiddleButtonDown();
	void PrintDebugInformation();
};

