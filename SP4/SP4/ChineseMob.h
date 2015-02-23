#pragma once
#include "BaseObject.h"
#include "AI.h"
#include "Sprite.h"

class CChineseMob : public CBaseObject
{
	public:
		CChineseMob();
		~CChineseMob();

		bool Update();
		bool Init();
		bool Reset();
		bool CleanUp();
		bool Render();

		bool OnCollision(CBaseObject* a_obj);
		
		CAILogic AI;
		CSprite * theSprite;
	private:
		
};