#pragma once
#include "obstaclebase.h"
#include "Character.h"
#include "ChineseMale.h"
#include "MalayFemale.h"

class CMalayHpReduce :
	public CObstacleBase
{
public:
	CMalayHpReduce(void);
	~CMalayHpReduce(void);

	bool Init(Vector3 pos, Vector3 size);
	bool Render();
	bool Update();
	bool OnCollision2(CBaseObject* a_obj);
};

