#include "Keyboard.h"

CKeyboard* CKeyboard::instance = 0;

CKeyboard::CKeyboard(void)
{
	Init();
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
	return Init();
}

bool CKeyboard::Update()
{
	return true;
}

bool CKeyboard::Init()
{
	tag = "keyboard";

	for(unsigned short i = 0; i<255; ++i)
	{
		myKeys[i] = false;
	}
	return true;
}

bool CKeyboard::CleanUp()
{
	return true;
}