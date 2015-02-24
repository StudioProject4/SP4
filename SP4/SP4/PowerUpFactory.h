#pragma once
#include "factory.h"

//forward declaration;
class CPowerUp;

class CPowerUpFactory //:
	//public CBaseObjectFactory
{
public:
	enum EPowerUpType
	{
		POWERUP_NONE,
		POWERUP_RECOVERY,
		POWERUP_POINTS,
		POWERUP_SPEEDUP,
		POWERUP_INVINCIBLE,
		POWERUP_HIGHJUMP,
		POWERUP_TOTAL
	};

	EPowerUpType currentManufactureType;
	CPowerUp* product;
public:
	CPowerUpFactory(void);
	CPowerUpFactory(EPowerUpType typeToMake);
	~CPowerUpFactory(void);

	void CreateProduct();
	CPowerUp* GetProduct();
	void SetManufactureType(EPowerUpType typeToMake);
	void SetManufactureNone();
	void SetManufactureRECOVERY();
	void SetManufacturePOINTS();
	void SetManufactureSPEEDUP();
	void SetManufactureINVINCIBLE();
	void SetManufactureHIGHJUMP();

};

