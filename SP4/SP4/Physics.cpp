#include "Physics.h"

CPhysics::CPhysics()
{
	for(int i=0;i<10;++i)//map[x][y]
	{
		for(int j=1;j<9;++j)
		{
			tempMap[i][j]=0;
		}
		tempMap[i][0]=1;
		tempMap[i][9]=1;
	}
}

CPhysics::~CPhysics()
{

}

int CPhysics::getTile(Vector3 thePos)
{
	if(thePos.x/20>=10)
		thePos.x=9;
	else if(thePos.x/20<0)
		thePos.x=0;
	if(thePos.y/20>=10)
		thePos.y=9;
	else if(thePos.y/20<0)
		thePos.y=0;
	
	return tempMap[(int)(thePos.x/20)][(int)(thePos.y/20)];
}

bool CPhysics::Init(Vector3 pos,Vector3 size)
{
	gravity = 20;
	vel.Set();
	this->size=size;
	this->pos=pos;
	return true;
}

bool CPhysics::TestCol(Vector3 pos2,Vector3 size2)
{
	if(abs(pos.x-pos2.x) > (size.x+size2.x))
		return false;

	if(abs(pos.y-pos2.y) > (size.y+size2.y))
		return false;
	return true;
}

void CPhysics::Jump()
{
	if(!inAir)
	{
		vel.y=80;
	}
}

Vector3 CPhysics::Update(Vector3 pos)
{
	float delta=0.06;
	int maptile=0;
	//if (vel.y>0)//if moving upwards check on top not below
	//{//up is negative
	//	size.y=-size.y;
	//}
	maptile = getTile(pos+size*0.5+vel*delta);//get the y pos of where it will get to based on weather its going up or down

	if (maptile == 0)//==air
	{
		vel.y-=gravity*delta;
		inAir=true;
	}
	else if (maptile == 1)//something solid
	{
		vel.y=0;
		if(size.y>0)
			inAir=false;
	}
	//else if maptile == slope
	//slopePhysics(dir)
	//
	if(size.y<0)
		size.y=-size.y;//set it back to positive
	pos+=vel*delta;
	this->pos.Set(pos.x,pos.y,pos.z);
	return this->pos;
}