#pragma once
#include "obstaclebase.h"
#include "Character.h"
#include "ChineseMale.h"
#include "MalayFemale.h"

class CChineseHpReduce :
	public CObstacleBase
{
public:
	CChineseHpReduce(void);
	~CChineseHpReduce(void);

	bool Init(Vector3 pos, Vector3 size);
	bool Render();
	bool Update();
	bool OnCollision2(CBaseObject* a_obj,bool again=false);

};

