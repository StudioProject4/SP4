#include "AIMobFactory.h"
#include "ChineseMob.h"
#include "MalayMob.h"

CAIMobFactory::CAIMobFactory(void)
	:currentManufactureType(AIMOB_NONE)
{
}

CAIMobFactory::CAIMobFactory(EAIMobType typeToMake)
	:currentManufactureType(typeToMake)
{
}

CAIMobFactory::~CAIMobFactory(void)
{
}

void CAIMobFactory::SetManufactureType(EAIMobType typeToMake)
{
	this->currentManufactureType = typeToMake;
}

void CAIMobFactory::SetManufactureNone()
{
	this->currentManufactureType = AIMOB_NONE;
}

void CAIMobFactory::SetManufactureCHINESEMOB()
{
	this->currentManufactureType = AIMOB_CHINESEMOB;
}

void CAIMobFactory::SetManufactureMALAYMOB()
{
	this->currentManufactureType = AIMOB_MALAYMOB;
}

void CAIMobFactory::CreateProduct()
{
	/*
	enum EAIMobType
	{
		AIMOB_NONE,
		AIMOB_CHINESEMOB,
		AIMOB_MALAYMOB,
		AIMOB_TOTAL
	};
	*/
	switch(currentManufactureType)
	{
		default:
			std::cout<<"<ERROR>Invalid Ai Mob creation"<<std::endl;
			break;

		case AIMOB_NONE:
			std::cout<<"<ERROR>Invalid Ai Mob creation"<<std::endl;
			break;

		case AIMOB_CHINESEMOB:
			product = new CChineseMob();
			break;

		case AIMOB_MALAYMOB:
			product = new CMalayMob();
			break;
	};
}