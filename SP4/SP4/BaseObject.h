#ifndef __BASEOBJECT_H__
#define __BASEOBJECT_H__

#include "Vector3.h"
#include "Entity.h"

class CBaseObject:public CEntity
{
public:
	bool active;
	Vector3 pos;
	Vector3 dir;
public:
	CBaseObject()
		:active(true)
	{};
	virtual ~CBaseObject(){};
	virtual bool OnCollision(CBaseObject* a_obj) = 0;
	virtual bool Render() = 0;

	virtual bool Update() = 0;
	virtual bool Init() = 0;
	virtual bool Reset()= 0;
	virtual bool CleanUp() = 0;
};


#endif