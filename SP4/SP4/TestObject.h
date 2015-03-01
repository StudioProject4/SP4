#pragma once
#include "baseobject.h"
class CTestObject :
	public CBaseObject
{
public:
	CTestObject(void);
	~CTestObject(void);
	bool OnCollision2(CBaseObject* a_obj)
	{
		return false;
	}
	bool Render();
	bool Update()
	{		
		pos=phys.Update(pos);
		return true;
	}
	bool Init()
	{		
		return true;
	}
	bool Reset()
	{
		return true;
	}
	bool CleanUp()
	{
		return true;
	}
};

