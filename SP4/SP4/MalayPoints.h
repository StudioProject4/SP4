#pragma once
#include "ObstacleBase.h"
#include "Character.h"
#include "ChineseMale.h"
#include "MalayFemale.h"
#include "PointSystem.h"

class CMalayPoints :
	public CObstacleBase
{
public:
	CMalayPoints(void);
	~CMalayPoints(void);

	bool Render();
	bool Init(Vector3 pos,Vector3 size);
	bool Update();
	bool OnCollision2(CBaseObject* a_obj,bool again=false);

	bool ChPtsTaken, MlPtsTaken;
	
	CPointSystem* pts;
};

