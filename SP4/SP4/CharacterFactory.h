#pragma once
#include "factory.h"

//forward declaration
class CCharacter;

class CCharacterFactory// :
	//public CBaseObjectFactory
{
public:

	enum ECharacterType
	{
		CHARACTER_NONE,
		CHARACTER_CHINESEMALE,
		CHARACTER_MALAYFEMALE,
		//CHARACTER_CHINESEMOB,
		//CHARACTER_MALAYMOB,
		CHARACTER_TOTAL
	};
	CCharacter * product;
	ECharacterType currentManufactureType;
public:
	CCharacterFactory(void);
	CCharacterFactory(ECharacterType typeToMake);
	~CCharacterFactory(void);

	void CreateProduct();
	CCharacter* GetProduct(){return product;};

	void SetManufactureType(ECharacterType typeToMake);
	void SetManufactureNone();
	void SetManufactureCHINESEMALE();
	void SetManufactureMALAYFEMALE();
	//void SetManufactureCHINESEMOB();
	//void SetManufactureMALAYMOB();
};

