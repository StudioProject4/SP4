#pragma once
#include "uibutton.h"
class CUIButtonRectangle :
	public CUIButton
{
public:
	CUIButtonRectangle(void);
	~CUIButtonRectangle(void);
	bool Update();
	bool Render();
	bool ColisionCheck(CMouse* theMouse);
	bool CollisionCheckColliderBox();
	//bool CollisionCheckColliderSphere();
};

