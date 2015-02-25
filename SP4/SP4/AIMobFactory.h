#pragma once
//#include "factory.h"

class CBaseObject;

class CAIMobFactory //:
	//public CBaseObjectFactory
{
public:
	enum EAIMobType
	{
		AIMOB_NONE,
		AIMOB_CHINESEMOB,
		AIMOB_MALAYMOB,
		AIMOB_TOTAL
	};
	CBaseObject* product;
	EAIMobType currentManufactureType;
public:
	CAIMobFactory(void);
	CAIMobFactory(EAIMobType typeToMake);
	~CAIMobFactory(void);

	CBaseObject* GetProduct(){return product;};
	void CreateProduct();

	void SetManufactureType(EAIMobType typeToMake);
	void SetManufactureNone();
	void SetManufactureCHINESEMOB();
	void SetManufactureMALAYMOB();
};

