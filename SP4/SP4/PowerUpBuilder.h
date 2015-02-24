#pragma once
#include "PowerUpFactory.h"

class CPowerUpBuilder
{
public:
	CPowerUpFactory* factory;
public:
	CPowerUpBuilder(void);
	~CPowerUpBuilder(void);

	void SetManufactureRECOVERY();
	void SetManufacturePOINTS();
	void SetManufactureSPEEDUP();
	void SetManufactureINVINCIBLE();
	void SetManufactureHIGHJUMP();
	CPowerUpFactory* GetFactory();
	CPowerUp* GetProduct();
};

