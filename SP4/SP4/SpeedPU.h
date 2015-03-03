#pragma once
#include "powerup.h"
class CSpeedPU :
	public CPowerUp
{
public:
	CSpeedPU(void);
	~CSpeedPU(void);
			
	bool Update();
	
	bool Render();

	bool Init();
	
	bool OnCollision2(CBaseObject* a_obj,bool again=false);
};

