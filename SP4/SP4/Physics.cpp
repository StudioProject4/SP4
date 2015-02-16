#include "Physics.h"

CPhysics::CPhysics()
{

}

CPhysics::~CPhysics()
{

}

bool CPhysics::Init()
{
	Gravity = 10;
}

bool TestCol(Vector3 pos,Vector3 size,Vector3 pos2,Vector3 size2)
{

}

Vector3 ApplyGravity(Vector3 pos,Vector3 size)
{
	//if vel.y>0
	//size.y=-size.y
	//maptile = map.gettile(pos.y+size.y/2+vel.y*delta)//get the y pos of where it will get to based on weather its going up or down
	//if maptile == air
	//vel.y-=gravity*delta
	//else if maptile == something solid
	//vel.y=0
	//
	//pos+=vel*delta
}