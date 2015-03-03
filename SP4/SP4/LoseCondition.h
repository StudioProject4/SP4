#pragma once
#include "BaseObject.h"
#include "Character.h"

class CLoseCondition: public CBaseObject
{
public:
	CLoseCondition(void);
	~CLoseCondition(void);

	bool Render();
	bool Update();
	bool Init();
	bool OnCollision(CBaseObject* a_obj);
};

