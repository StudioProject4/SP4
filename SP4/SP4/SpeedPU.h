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
	
	bool OnCollision(CBaseObject* a_obj);
};

