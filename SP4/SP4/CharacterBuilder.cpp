#include "CharacterBuilder.h"


CCharacterBuilder::CCharacterBuilder(void)
{
	factory = new CCharacterFactory;
}

CCharacterBuilder::~CCharacterBuilder(void)
{
	delete factory;
}

void CCharacterBuilder::SetManufactureChineseMale()
{
	factory->SetManufactureCHINESEMALE();
}

void CCharacterBuilder::SetManufactureMalayFemale()
{
	factory->SetManufactureMALAYFEMALE();
}
CCharacter* CCharacterBuilder::GetProduct()
{
	factory->CreateProduct();
	return factory->GetProduct();
}
CCharacterFactory* CCharacterBuilder::GetFactory()
{
	return factory;
}