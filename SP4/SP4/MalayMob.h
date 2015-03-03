#pragma once
#include "BaseObject.h"
#include "AI.h"
#include "Sprite.h"

class CMalayMob : public CBaseObject
{
	public:
		CMalayMob();
		~CMalayMob();
		
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
	private:
		
};