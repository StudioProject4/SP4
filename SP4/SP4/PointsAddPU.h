#pragma once
#include "powerup.h"
class CPointsAddPU :
	public CPowerUp
{
public:
	CPointsAddPU(void);
	~CPointsAddPU(void);

	bool Update();
	
	bool Render();

	bool Init();
};

