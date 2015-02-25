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
	Vector3 getTileV(Vector3 thePos);
	Vector3 getTileV(float posX,float posY);
	//end of removal
	//have a map reference here when map is done
	Vector3 pos;

public:
	CMap* map;
	float gravity;
	bool inAir;
	Vector3 vel;
	Vector3 size;
	CPhysics();
	~CPhysics();
	void Jump();
	//set x velocity
	void MoveSide(bool mode);
	//void SetVelocity(Vector3 nVel);
	bool Init(Vector3 pos,Vector3 size);
	bool TestCol(Vector3 otherPos,Vector3 otherSize);//only for other objects not for with the map
	Vector3 Update(Vector3 pos);//will apply gravity here and test for map collision
	bool TestColMap(Vector3 pos, bool m_bCheckUpwards, bool m_bCheckDownwards, bool m_bCheckLeft, bool m_bCheckRight, CMap* map,int x_offset=0,int y_offset=0);
};

#endif