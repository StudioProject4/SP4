#ifndef __LEVERDOOR_H__
#define __LEVERDOOR_H__

#include "Door.h"
#include "TriggerBase.h"
#include "Vector3.h"


class CLeverDoor:public CTriggerBase
{
private:
	float offTrigger,onTrigger,maxAngle,minAngle;
	Vector3 normal;
	Vector3 width1,width2;
	Vector3 colPoint;
	float length;
	float width;
	bool applyGrav;
	bool trigger;
	long lastTime;
public:
	float angleVel;
	float curAngle;
	CLeverDoor(void);
	~CLeverDoor(void);
	bool Init(Vector3 pos,Vector3 size);
	bool Update();
	bool Render();
	bool OnCollision2(CBaseObject*,bool again=false);
	int GetDoorID()
	{
		if(doorLink!=NULL)
		{
			return doorLink->id;
		}
		return 0;
	}
};

#endif