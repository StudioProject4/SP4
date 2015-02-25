#pragma once
#include "powerup.h"
class CHealthPU :
	public CPowerUp
{
public:
	CHealthPU(void);
	~CHealthPU(void);
	
	bool Update();
	
	bool Render();
	bool OnActivate();

	bool Init();
};

