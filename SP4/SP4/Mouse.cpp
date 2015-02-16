#include "Mouse.h"

CMouse* CMouse::instance = 0;

CMouse::CMouse(void)
	:mLButtonUp(false)
	,mRButtonUp(false)
	,middleButtonUp(false)
	,lastX(0)
	,lastY(0)
	,sensitivity(0.5)
{
	tag = "mouse";
}
CMouse* CMouse::GetInstance()
{
	if(instance == 0)
	{
		instance = new CMouse();
	}

	return instance;
}

CMouse::~CMouse(void)
{
}
bool CMouse::Reset()
{
	middleButtonUp = mRButtonUp = mLButtonUp = false;
	lastY = lastX = 0;
	sensitivity = 0.5f;
	return true;
}
