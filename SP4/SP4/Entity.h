#pragma once
#include <stdio.h>
class CEntity
{
public:
	char* name;
	char* genericTag;//for the parent type
	char* tag;//for the child type
	unsigned short id;
public:

	CEntity(void)
		: name(" ")
		, tag(" ")
		, id(0)
		, genericTag(0)
	{
	}
	virtual ~CEntity(void)
	{
	}
	virtual bool Update() = 0;
	virtual bool Init() = 0;
	virtual bool Reset()= 0;
	virtual bool CleanUp() = 0;

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

