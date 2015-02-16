#pragma once
#include "Entity.h"

class CMouse:public CEntity
{
public:
	bool mLButtonUp;
	bool mRButtonUp;
	bool middleButtonUp;
	int  lastX, lastY;
	float sensitivity;
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
};

