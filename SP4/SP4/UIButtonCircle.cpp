#include "UIButtonCircle.h"


CUIButtonCircle::CUIButtonCircle(void)
{

}


CUIButtonCircle::~CUIButtonCircle(void)
{

}

bool CUIButtonCircle::Update()
{
	ownTexture.LiveOn();
	return true;
}

bool CUIButtonCircle::Render()
{
	return true;
}

bool CUIButtonCircle::ColisionCheck(CMouse* theMouse)
{
	return true;
}

bool CUIButtonCircle::CollisionCheckColliderSphere()
{
	return true;
}