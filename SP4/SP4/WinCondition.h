#pragma once
#include "BaseObject.h"
#include "Character.h"
#include "Sprite.h"
#include "Map.h"
#include "ChineseMale.h"
#include "MalayFemale.h"

class CWinCondition: public CBaseObject
{
public:
	CWinCondition(void);
	~CWinCondition(void);

	bool Render();
	bool Update();
	bool Init();
	bool OnCollision(CBaseObject* a_obj, bool frame2=false);
	void LevelChange();
	void LoseGame();

	CMap lvC;		//level change

	CMalayFemale* MF;
	CChineseMale* CM;

private:

	bool ChineseMaleIn, MalayFemaleIn;		//player got into the door		

};

