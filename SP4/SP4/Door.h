#pragma once
#include "ObstacleBase.h"
#include <vector>

#include "TriggerBase.h"

class CSprite;

class CDoor :
	public CObstacleBase
{
protected:
	//CSprite* sprite;
	bool triggered;
	std::vector<CTriggerBase*> triggerList;//for triggers that all must be active before it will move
	void TriggerEvent();//what happens when its triggered
public:
	CDoor(void);
	~CDoor(void);
	bool Init(Vector3 pos,Vector3 size);
	bool Update();
	bool Render();
	bool OnCollision2(CBaseObject*);
	void AddTrigger(CTriggerBase*);//add a trigger
	void Trigger();//attempt to trigger it
	std::vector<int> GetTriggerID()
	{
		std::vector<int> temp;
		for(std::vector<CTriggerBase*>::iterator it=triggerList.begin();it!=triggerList.end();++it)
		{
			temp.push_back((*it)->id);
		}
		return temp;
	}
};

