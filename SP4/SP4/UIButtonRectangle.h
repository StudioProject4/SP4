#pragma once
#include "uibutton.h"

class CUIButtonRectangle :
	public CUIButton
{
public:
	Vector3 TopLeft;
	Vector3 BottomRight;
public:
	CUIButtonRectangle(void);
	~CUIButtonRectangle(void);
	bool Update();
	bool Render();
	bool ColisionCheck(CMouse* theMouse);
	bool CollisionCheckColliderBox(Vector3& pos);
	//bool CollisionCheckColliderSphere();


	void CalculateTopLeftAndBottomRightPoint();

	void SetSize(Vector3& Size);

	void SetSize(float x = 0.f,float y = 0.f);

	void PrintDebugInformation();
};

