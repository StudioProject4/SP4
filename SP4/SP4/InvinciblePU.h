#pragma once
#include "powerup.h"
class CInvinciblePU :
	public CPowerUp
{
public:
	CInvinciblePU(void);
	~CInvinciblePU(void);

	bool InvinOnP1, InvinOnP2;

	bool Update();
	
	bool Render();

	bool Init();

	bool OnCollision2(CBaseObject* a_obj);
};

