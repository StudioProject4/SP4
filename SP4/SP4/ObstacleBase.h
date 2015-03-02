#pragma once
#include "baseobject.h"

#include "Sprite.h"
#include "Physics.h"

class CObstacleBase :
	public CBaseObject
{
public:
	CObstacleBase(void);
	virtual ~CObstacleBase(void);
	bool Init()
	{
		return true;
	}
	virtual bool Init(Vector3 pos,Vector3 size)=0;
	virtual bool Update()=0;
	virtual bool Render()=0;
	virtual bool OnCollision2(CBaseObject*) = 0;
	bool Reset()
	{
		return true;
	}
	bool CleanUp()
	{
		return true;
	}
};

