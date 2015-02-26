#pragma once
#include "ObstacleBase.h"
#include <vector>

class CTriggerBase;
class CSprite;

class CDoor :
	public CObstacleBase
{
protected:
	CSprite* sprite;
	bool triggered;
	std::vector<CTriggerBase*> triggerList;//for triggers that all must be active before it will move
	void TriggerEvent();//what happens when its triggered
public:
	CDoor(void);
	~CDoor(void);
	bool Init(Vector3 pos,Vector3 size);
	bool Update();
	bool Render();
	bool OnCollision(CBaseObject*);
	void AddTrigger(CTriggerBase*);//add a trigger
	void Trigger();//attempt to trigger it
};

