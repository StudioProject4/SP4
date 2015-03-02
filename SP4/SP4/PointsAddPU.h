#pragma once
#include "powerup.h"
#include "PointSystem.h"

class CPointsAddPU :
	public CPowerUp
{
public:
	CPointsAddPU(void);
	~CPointsAddPU(void);

	bool Update();
	
	bool Render();

	bool Init();

	bool OnCollision2(CBaseObject* a_obj);

	CPointSystem* pts;
};

