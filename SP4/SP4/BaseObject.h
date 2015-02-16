#ifndef __BASEOBJECT_H__
#define __BASEOBJECT_H__

#include "Vector3.h"
#include "Entity.h"


class CBaseObject:public CEntity
{
	CBaseObject();
	~CBaseObject();
	Vector3 pos;
	Vector3 dir;
	virtual bool Render()=0;
};


#endif