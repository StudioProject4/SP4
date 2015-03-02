#pragma once
#include "uibutton.h"
class CUIButtonCircle :
	public CUIButton
{
public:
	CUIButtonCircle(void);
	~CUIButtonCircle(void);
	bool Update();
	bool Render();
	bool ColisionCheck(CMouse* theMouse);
	//bool CollisionCheckColliderBox();
	bool CollisionCheckColliderSphere();
};

