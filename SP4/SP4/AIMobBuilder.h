#pragma once
#include "AIMobFactory.h"

class CAIMobBuilder
{
public:
	CAIMobFactory* factory;
public:
	CAIMobBuilder(void);
	~CAIMobBuilder(void);
	void SetManufactureCHINESEMOB();
	void SetManufactureMALAYMOB();
	CBaseObject* GetProduct();
	CAIMobFactory* GetFactory();
};

