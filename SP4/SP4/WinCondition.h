#pragma once
#include "ObstacleBase.h"
#include "Character.h"
#include "Sprite.h"
#include "Map.h"
#include "ChineseMale.h"
#include "MalayFemale.h"

class CWinCondition: public CObstacleBase
{
public:
	CWinCondition(void);
	~CWinCondition(void);

	bool Render();
	bool Update();
	bool Init(Vector3 pos, Vector3 size);
	bool OnCollision(CBaseObject* a_obj, bool frame2=false);
	bool OnCollision2(CBaseObject* a_obj, bool again)
	{
		return true;
	}

	void LevelChange();
	void LoseGame();

	CMap* levelChange;		//level change

	CMalayFemale* MF;
	CChineseMale* CM;

private:

	bool ChineseMaleIn, MalayFemaleIn;		//player got into the door		

};

