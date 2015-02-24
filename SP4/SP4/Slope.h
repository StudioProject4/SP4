#pragma once
#include "ObstacleBase.h"
class CSlope :
	public CObstacleBase
{
private:
	float angle;
	Vector3 normal;
public:
	CSlope(void);
	~CSlope(void);
	bool Init(Vector3 pos,Vector3 size);
	bool Update();
	bool Render();
	bool OnCollision(CBaseObject*);
};

