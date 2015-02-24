#include "CharacterFactory.h"

#include "ChineseMale.h"
#include "MalayFemale.h"

//#include "ChineseMob.h"
//#include "MalayMob.h"


CCharacterFactory::CCharacterFactory(void)
	:currentManufactureType(CHARACTER_NONE)
{
}

CCharacterFactory::CCharacterFactory(ECharacterType typeToMake)
	:currentManufactureType(typeToMake)
{
}

CCharacterFactory::~CCharacterFactory(void)
{
}

void CCharacterFactory::SetManufactureType(ECharacterType typeToMake)
{
	this->currentManufactureType = typeToMake;
}

void CCharacterFactory::SetManufactureNone()
{
	this->currentManufactureType = CHARACTER_NONE;
}

void CCharacterFactory::SetManufactureCHINESEMALE()
{
	this->currentManufactureType = CHARACTER_CHINESEMALE;
}

void CCharacterFactory::SetManufactureMALAYFEMALE()
{
	this->currentManufactureType = CHARACTER_MALAYFEMALE;
}
//
//void CCharacterFactory::SetManufactureCHINESEMOB()
//{
//	this->currentManufactureType = CHARACTER_CHINESEMOB;
//}
//
//void CCharacterFactory::SetManufactureMALAYMOB()
//{
//	this->currentManufactureType = CHARACTER_MALAYMOB;
//}
void CCharacterFactory::CreateProduct()
{
	/*
		CHARACTER_NONE,
		CHARACTER_CHINESEMALE,
		CHARACTER_MALAYFEMALE,
		CHARACTER_CHINESEMOB,
		CHARACTER_MALAYMOB,
		CHARACTER_TOTAL
	*/
	switch(currentManufactureType)
	{
		default:
			std::cout<<"<ERROR>Invalid Character creation"<<std::endl;
			break;

		case CHARACTER_NONE:
			std::cout<<"<ERROR>Invalid Character creation"<<std::endl;
			break;

		case CHARACTER_CHINESEMALE:
			product = new CChineseMale();
			break;

		case CHARACTER_MALAYFEMALE:
			product = new CMalayFemale();
			break;

		//case CHARACTER_CHINESEMOB:
		//	product = new CChineseMob();
		//	break;

		//case CHARACTER_MALAYMOB:
		//	break;
	};
}