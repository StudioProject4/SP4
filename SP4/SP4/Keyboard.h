#pragma once
#include "Entity.h"
class CKeyboard:public CEntity
{
public:
	bool myKeys[255];
	bool leftArrow;
	bool rightArrow;
	bool upArrow;
	static CKeyboard* instance;
private:
	CKeyboard(void);
public:
	static CKeyboard* GetInstance();
	~CKeyboard(void);
	bool Reset();
	bool Update();
	bool Init() ;
	bool CleanUp();
};

