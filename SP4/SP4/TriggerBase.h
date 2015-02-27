#pragma once
#include "ObstacleBase.h"

class CDoor;

class CTriggerBase:public CObstacleBase
{
protected:
	bool triggered;
	CDoor* doorLink;
public:
	virtual bool GetTriggered()
	{
		return triggered;
	}
	void SetDoorLink(CDoor* ndoor)
	{
		doorLink=ndoor;
	}
	virtual bool Init(Vector3 pos,Vector3 size)=0;
	virtual bool Update()=0;
	virtual bool Render()=0;
	virtual bool OnCollision(CBaseObject*) = 0;
	CTriggerBase(void);
	~CTriggerBase(void);
};

