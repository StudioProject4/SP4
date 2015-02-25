#include "Slope.h"


CSlope::CSlope(void)
{
}


CSlope::~CSlope(void)
{
}

bool CSlope::Init(Vector3 pos,Vector3 size)
{
	this->pos=pos;
	this->phys.Init(pos,size);
	angle=45;
	return true;
}

bool CSlope::Update()
{
	return true;
}

bool CSlope::Render()
{
	return true;

}

bool CSlope::OnCollision(CBaseObject* obj)
{
	//check pos against this object
	Vector3 startPos=this->pos-this->phys.size*0.5;//bottom right
	float offset=obj->pos.x-startPos.x;
	if(offset<0)//means middle not past the bottom right
	{
		return false;
	}
	//find new y pos
	float nYpos=0;
	nYpos=sin(angle)*offset;//get y pos based on the angle and the offset
	//offset it based on height of object
	nYpos+=pos.y;
	//adjust y pos
	return true;
}