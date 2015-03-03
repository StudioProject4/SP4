#pragma once
#include "uibutton.h"


class CUIButtonCircle :
	public CUIButton
{
public:
	float radius;
public:
	CUIButtonCircle(void);
	~CUIButtonCircle(void);
	bool Update();
	bool Render();
	bool ColisionCheck(CMouse* theMouse);
	//bool CollisionCheckColliderBox();
	//bool CollisionCheckColliderSphere(float &posX,float &posY);
	bool CollisionCheckColliderSphere(Vector3& pos);
	void CalculateRadius();
	void SetSize(Vector3& Size);
	void SetSize(float x = 0.f,float y = 0.f);
	void PrintDebugInformation();

};

