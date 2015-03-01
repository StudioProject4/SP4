#pragma once
#include "powerup.h"
#include "Character.h"

class CHealthPU :
	public CPowerUp
{
public:
	CHealthPU(void);
	~CHealthPU(void);
	
	bool Update();
	
	bool Render();

	bool Init();
	
	bool OnCollision2(CBaseObject* a_obj);

};


