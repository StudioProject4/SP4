#pragma once
#include <stdio.h>
class CEntity
{
public:
	char* name;
	char* tag;
	unsigned short id;
public:

	CEntity(void)
		: name(" ")
		, tag(" ")
		, id(0)
	{
	}

	virtual ~CEntity(void)
	{
	}
	virtual bool Update()
	{
		return true;
	}
	virtual bool Init()
	{
		return true;
	}
	virtual bool Reset()
	{
		return true;
	}
	virtual bool CleanUp()
	{
		return true;
	}
	virtual bool Release()
	{
		delete this;
		return true;
	}

	virtual void PrintDebugInformation()
	{
		printf("\n ID: %d",id);
		printf("\n Name: %s",name);
		printf("\n Tag: %s",tag);
	}
};

