#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "Vector3.h"

class CPhysics
{
private:
	float Gravity;
	Vector3 vel;
	Vector3 SlopePhysics(Vector3 Pos,Vector3 Dir);
public:
	CPhysics();
	~CPhysics();
	void SetVelocity(Vector3 nVel);
	bool Init();
	bool TestCol(Vector3 pos,Vector3 size,Vector3 pos2,Vector3 size2);
	Vector3 ApplyGravity(Vector3 pos,Vector3 size);
};

#endif