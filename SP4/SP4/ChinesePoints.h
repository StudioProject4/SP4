#pragma once
#include "ObstacleBase.h"
#include "ChineseMale.h"
#include "MalayFemale.h"

class CChinesePoints :
	public CObstacleBase
{
public:
	CChinesePoints(void);
	~CChinesePoints(void);
	
	bool Render();
	bool Init(Vector3 pos,Vector3 size);
	bool Update();
	bool OnCollision2(CBaseObject* a_obj,bool again=false);

};

