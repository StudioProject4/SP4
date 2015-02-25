#include "PowerUpFactory.h"

#include "PowerUp.h"//remove if not needed

CPowerUpFactory::CPowerUpFactory(void)
	:currentManufactureType(POWERUP_NONE)
{
}
CPowerUpFactory::CPowerUpFactory(EPowerUpType typeToMake)
	:currentManufactureType(typeToMake)
{
}

CPowerUpFactory::~CPowerUpFactory(void)
{
}
void  CPowerUpFactory::SetManufactureType(EPowerUpType typeToMake)
{
	currentManufactureType = typeToMake;
}

void CPowerUpFactory::SetManufactureNone()
{
	currentManufactureType = this->POWERUP_NONE;
}
void  CPowerUpFactory::SetManufacturePOINTS()
{
	currentManufactureType = this->POWERUP_POINTS;
}

void CPowerUpFactory::SetManufactureRECOVERY()
{
	currentManufactureType = this->POWERUP_RECOVERY;
}

void CPowerUpFactory::SetManufactureSPEEDUP()
{
	currentManufactureType = this->POWERUP_SPEEDUP;
}

void CPowerUpFactory::SetManufactureINVINCIBLE()
{
	currentManufactureType = this->POWERUP_INVINCIBLE;
}

void CPowerUpFactory::SetManufactureHIGHJUMP()
{
	currentManufactureType = this->POWERUP_HIGHJUMP;
}

CPowerUp* CPowerUpFactory::GetProduct()
{
	return product;
}

void CPowerUpFactory::CreateProduct()
{
	/*
		POWERUP_NONE,
		POWERUP_RECOVERY,
		POWERUP_SPEEDUP,
		POWERUP_INVINCIBLE,
		POWERUP_HIGHJUMP,
		POWERUP_TOTAL
	*/
	// if power up don't have dereived class then no need the currentmanufacturetype and the switch case, just //product = new CPowerUp(); can liao.
	switch(currentManufactureType)
	{
		default:
			std::cout<<"<ERROR>Invalid Ai Mob creation"<<std::endl;
			break;

		case POWERUP_NONE:
			// for testing//Demo
			//product = new CPowerUp();
			std::cout<<"<ERROR>Invalid Power up creation"<<std::endl;
			break;

		case POWERUP_RECOVERY:
			//Demo
			//product = new CRecoveryPowerUp();
			break;

		case POWERUP_SPEEDUP:
			//Demo
			//product = new CSpeedUpPowerUp();
			break;

		case POWERUP_INVINCIBLE:
			//Demo
			//product = new CInvincibleUp();
			break;

		case POWERUP_HIGHJUMP:
			//
			//Demo
			//product = new CHighJump();
			break;

	};
	
}