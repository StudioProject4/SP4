#pragma once
#include "Physics.h"
#include "baseobject.h"
class CObstacleBase :
	public CBaseObject
{
public:
	CPhysics phys;
	CObstacleBase(void);
	virtual ~CObstacleBase(void);
	virtual bool Init(Vector3 pos,Vector3 size)=0;
	virtual bool Update()=0;
	virtual bool Render()=0;
	virtual bool OnCollision(CBaseObject*) = 0;
};

