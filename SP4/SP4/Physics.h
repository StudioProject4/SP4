#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "Vector3.h"

class CPhysics
{
private:
	//remove when map is done
	int tempMap[10][10];
	int getTile(Vector3 thePos);
	//end of removal
	//have a map reference here when map is done
	Vector3 pos;
public:
	float gravity;
	bool inAir;
	Vector3 vel;
	Vector3 size;
	CPhysics();
	~CPhysics();
	void Jump();
	//void SetVelocity(Vector3 nVel);
	bool Init(Vector3 pos,Vector3 size);
	bool TestCol(Vector3 otherPos,Vector3 otherSize);//only for other objects not for with the map
	Vector3 Update(Vector3 pos);//will apply gravity here and test for map collision
};

#endif