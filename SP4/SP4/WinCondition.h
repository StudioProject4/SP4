#pragma once
#include "BaseObject.h"
#include "Character.h"
#include "Sprite.h"
#include "Map.h"

class CWinCondition: public CBaseObject
{
public:
	CWinCondition(void);
	~CWinCondition(void);

	bool Render();
	bool Update();
	bool Init();
	bool OnCollision2(CBaseObject* a_obj);
	void LevelChange();

	CMap lvC;		//level change

private:

	bool ChineseMaleIn, MalayFemaleIn;		//player got into the door		

};

