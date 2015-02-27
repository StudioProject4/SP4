#ifndef __LEVERDOOR_H__
#define __LEVERDOOR_H__

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
	float angleVel;
	bool applyGrav;
	bool trigger;
public:
	float curAngle;
	CLeverDoor(void);
	~CLeverDoor(void);
	bool Init(Vector3 pos,Vector3 size);
	bool Update();
	bool Render();
	bool OnCollision(CBaseObject*);

};

#endif