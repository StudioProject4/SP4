#include "PowerUpBuilder.h"


CPowerUpBuilder::CPowerUpBuilder(void)
{
	factory = new CPowerUpFactory();
}

CPowerUpBuilder::~CPowerUpBuilder(void)
{
	delete factory;
}

void CPowerUpBuilder::SetManufactureRECOVERY()
{
	factory->SetManufactureRECOVERY();
}

void CPowerUpBuilder::SetManufacturePOINTS()
{
	factory->SetManufacturePOINTS();
}

void CPowerUpBuilder::SetManufactureSPEEDUP()
{
	factory->SetManufactureSPEEDUP();
}

void CPowerUpBuilder::SetManufactureINVINCIBLE()
{
	factory->SetManufactureINVINCIBLE();
}

void CPowerUpBuilder::SetManufactureHIGHJUMP()
{
	factory->SetManufactureHIGHJUMP();
}

CPowerUp* CPowerUpBuilder::GetProduct()
{
	factory->CreateProduct();
	return factory->GetProduct();
}

CPowerUpFactory* CPowerUpBuilder::GetFactory()
{
	return factory;
}