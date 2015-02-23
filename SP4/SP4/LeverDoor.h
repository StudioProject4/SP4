#ifndef __LEVERDOOR_H__
#define __LEVERDOOR_H__

#include "ObstacleBase.h"
#include "Vector3.h"

class CLeverDoor:public CObstacleBase
{
private:
	float offTrigger,onTrigger,maxAngle,minAngle;
	Vector3 normal;
	float length;
	float width;
	float angleVel;
	bool applyGrav;
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