#include "AIMobBuilder.h"


CAIMobBuilder::CAIMobBuilder(void)
{
	factory = new CAIMobFactory;
}

CAIMobBuilder::~CAIMobBuilder(void)
{
	delete factory;
}

void CAIMobBuilder::SetManufactureCHINESEMOB()
{
	factory->SetManufactureCHINESEMOB();
}

void CAIMobBuilder::SetManufactureMALAYMOB()
{
	factory->SetManufactureMALAYMOB();
}

CBaseObject* CAIMobBuilder::GetProduct()
{
	factory->CreateProduct();
	return factory->GetProduct();
}

CAIMobFactory* CAIMobBuilder::GetFactory()
{
	return factory;
}
