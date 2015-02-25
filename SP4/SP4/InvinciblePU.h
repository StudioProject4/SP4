#pragma once
#include "powerup.h"
class CInvinciblePU :
	public CPowerUp
{
public:
	CInvinciblePU(void);
	~CInvinciblePU(void);

		
	bool Update();
	
	bool Render();
	bool OnActivate();

	bool Init();
};

