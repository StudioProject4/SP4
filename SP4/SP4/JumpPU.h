#pragma once
#include "powerup.h"

class CJumpPU :
	public CPowerUp
{
public:
	CJumpPU(void);
	~CJumpPU(void);

	bool Update();
	
	bool Render();

	bool Init();
	
	bool OnCollision2(CBaseObject* a_obj,bool again=false);
};

