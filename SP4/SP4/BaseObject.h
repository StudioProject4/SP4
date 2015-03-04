#ifndef __BASEOBJECT_H__
#define __BASEOBJECT_H__

#include "Vector3.h"
#include "Entity.h"
#include "Physics.h"
#include <vector>
class CSprite;
class Cell;

#include "CodeDefination.h"

class CBaseObject:public CEntity
{
public:
	CPhysics phys;
	bool active;
	Vector3 pos;
	Vector3 dir;
	//unsigned short numberOfTimeCollided;
	CSprite * theSprite;
	short cellvectorindex;
	Cell* ownerCell;


#ifdef SP_V2
	Vector3 TopLeft;
	Vector3 BottomRight;
	Vector3 TopLeftCellIndex;
	Vector3 BottomRightCellIndex;
	std::vector<Cell*> ownerCellList;
#endif

public:
	CBaseObject()
		:active(true)
		,cellvectorindex(-1)
		,lastCall(0)
		,frame(false)
		//,numberOfTimeCollided(0)
	{};
	virtual ~CBaseObject(){};
	
	virtual bool OnCollision(CBaseObject* a_obj,bool frame);
	virtual bool OnCollision2(CBaseObject* a_obj,bool again=false)=0;
	virtual bool Render() = 0;

	virtual bool Update() = 0;
	virtual bool Init() = 0;
	virtual bool Reset()= 0;
	virtual bool CleanUp() = 0;
	virtual void UpdateObjectTopLeftAndBottomRightPoint(bool sizeOfObjectIsInRadius)
	{
		if(sizeOfObjectIsInRadius)
		{
			TopLeft.Set(pos.x - phys.size.x,pos.y - phys.size.y);
			BottomRight.Set(pos.x + phys.size.x,pos.y + phys.size.y);
		}else
		{
			TopLeft.Set(pos.x - phys.size.x *0.5f,pos.y - phys.size.y*0.5f);
			BottomRight.Set(pos.x + phys.size.x*0.5f,pos.y + phys.size.y*0.5f);
		}
	};
protected:
	long lastCall;
	bool frame;
};


#endif