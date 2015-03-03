#include "Mouse.h"

CMouse* CMouse::instance = 0;

CMouse::CMouse(void)
	:mLButtonUp(false)
	,mRButtonUp(false)
	,middleButtonUp(false)
	,lastX(0)
	,lastY(0)
	,sensitivity(0.5)
	,lastLButtonState(false)
	,lastRButtonState(false)
	,lastMiddleButtonState(false)
{
	
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

bool CMouse::Update()
{
	return true;
}

bool CMouse::Init() 
{
	tag = "mouse";
	middleButtonUp = mLButtonUp =  mRButtonUp = false;
	lastLButtonState = lastRButtonState = lastMiddleButtonState = false;
	gameX = gameY = lastY = lastX = 0;
	sensitivity = 0.5f;
	return true;
}

void CMouse::SetLeftButton(bool down)
{
	if(lastLButtonState != this->mLButtonUp)
	{
		lastLButtonState = this->mLButtonUp;
	}

	this->mLButtonUp = down;


}

void CMouse::SetMiddleButton(bool down)
{
	if(lastMiddleButtonState != this->middleButtonUp)
	{
		lastMiddleButtonState = this->middleButtonUp;
	}
	this->middleButtonUp = down;
}

void CMouse::SetRightButton(bool down)
{
	if(lastRButtonState != this->mRButtonUp)
	{
		lastRButtonState = this->mRButtonUp;
	}
	this->mRButtonUp = down;
}

bool CMouse::CheckLeftButtonReleased()
{
	if(lastLButtonState == true && this->mLButtonUp == false)
	{
		return true;
	}
	return false;
}

bool CMouse::CheckRightButtonReleased()
{
	if(lastRButtonState == true && this->mRButtonUp == false)
	{
		return true;
	}
	return false;
}

bool CMouse::CheckMiddleButtonReleased()
{
	if(lastMiddleButtonState == true && this->middleButtonUp == false)
	{
		return true;
	}
	return false;
}

bool CMouse::CheckLeftButtonDown()
{
	if(this->mLButtonUp == true)
	{
		return true;
	}

	return false;
}

bool CMouse::CheckRightButtonDown()
{
	if(this->mRButtonUp == true)
	{
		return true;
	}

	return false;
}

bool CMouse::CheckMiddleButtonDown()
{
	if(this->middleButtonUp == true)
	{
		return true;
	}

	return false;
}

bool CMouse::CleanUp()
{
	return true;
}

bool CMouse::Reset()
{
	return Init();
}
//void CMouse::UpdateMousePosition(int x,int y)
//{
//	this->lastX = x;
//	this->lastY = y;
//}
void CMouse::PrintDebugInformation()
{
	CEntity::PrintDebugInformation();
	printf("\n middleButtonUp: %s",middleButtonUp?"true":"false");
	printf("\n mLButtonUp: %s",mLButtonUp?"true":"false");
	printf("\n mRButtonUp: %s",mRButtonUp?"true":"false");
	printf("\n lastleftmousestate: %s",this->lastLButtonState?"true":"false");
	printf("\n LeftMouseReleased: %s",CheckLeftButtonReleased()?"true":"false");
	printf("\n lastX,lastY %d,%d",lastX,lastY);
	printf("\n Sensitivity %f",sensitivity); 
}