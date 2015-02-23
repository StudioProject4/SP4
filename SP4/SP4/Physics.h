#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "Vector3.h"
#include "Map.h"

class CPhysics
{
private:
	//remove when map is done
	int tempMap[10][10];
	int getTile(Vector3 thePos);
	//end of removal
	//have a map reference here when map is done
	bool inAir;
	float gravity;
	Vector3 vel;
	Vector3 pos;
	Vector3 size;
	Vector3 SlopePhysics(Vector3 Dir);//direction of the slope

	CMap* Map;

public:
	CPhysics();
	~CPhysics();
	void Jump();
	//void SetVelocity(Vector3 nVel);
	bool Init(Vector3 pos,Vector3 size);
	bool TestCol(Vector3 pos2,Vector3 size2);//only for with other objects not for with the map
	Vector3 Update(Vector3 pos);//will apply gravity here and test for map collision
};

#endif