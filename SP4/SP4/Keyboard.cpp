#include "Keyboard.h"

CKeyboard* CKeyboard::instance = 0;

CKeyboard::CKeyboard(void)
{
	tag = "keyboard";
	Reset();
}


CKeyboard::~CKeyboard(void)
{
}
CKeyboard* CKeyboard::GetInstance()
{
	if(instance == 0)
	{
		instance = new CKeyboard();
	}

	return instance;
}

bool CKeyboard::Reset()
{
	for(unsigned short i = 0; i<255; ++i)
	{
		myKeys[i] = false;
	}
	return true;
}
