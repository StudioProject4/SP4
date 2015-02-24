#pragma once
#include "CharacterFactory.h"


class CCharacterBuilder
{
public:
	CCharacterFactory* factory;
public:
	CCharacterBuilder(void);
	~CCharacterBuilder(void);
	void SetManufactureChineseMale();
	void SetManufactureMalayFemale();
	CCharacter* GetProduct();
	CCharacterFactory* GetFactory();
};

