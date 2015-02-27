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

		bool OnCollision(CBaseObject* a_obj);

		void SetPos(Vector3 newPos);

		CAILogic AI;
		//CSprite * theSprite;
	private:
		
};