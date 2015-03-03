#pragma once
#include "BaseObject.h"
#include "AI.h"
#include "Sprite.h"
#include "MVCtime.h"
#include <time.h>

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

		bool OnCollision2(CBaseObject* a_obj,bool again=false);

		void SetPos(Vector3 newPos);
		void SetUpMap(CMap theMap);

		CAILogic AI;
		//CSprite * theSprite;

		MVCTime * Timer ;
		int refTime;

		clock_t timer;
	private:
		
};