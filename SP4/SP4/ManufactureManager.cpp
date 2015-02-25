#include "ManufactureManager.h"

#include "AIMobBuilder.h"
#include "PowerUpBuilder.h"
#include "CharacterBuilder.h"
#include "ChineseMale.h"
#include "ChineseMob.h"
#include "MalayFemale.h"
#include "MalayMob.h"
#include "PowerUp.h"

CManufactureManager* CManufactureManager::instance = 0;

CManufactureManager::CManufactureManager(void)
{
	aiMobBuilder = new CAIMobBuilder;
	powerUpBuilder = new CPowerUpBuilder ;
	characterBuilder = new CCharacterBuilder;
}

CManufactureManager* CManufactureManager::GetInstance()
{
	if(instance == 0)
	{
		instance = new CManufactureManager();
	}
	return instance;
}

CManufactureManager::~CManufactureManager(void)
{
	delete aiMobBuilder;
	delete powerUpBuilder;
	delete characterBuilder;
}

CChineseMale* CManufactureManager::CreateChineseMale()
{
	characterBuilder->SetManufactureChineseMale();
	return dynamic_cast<CChineseMale*>(characterBuilder->GetProduct());
}

CChineseMob* CManufactureManager::CreateChineseMob()
{
	aiMobBuilder->SetManufactureCHINESEMOB();
	return dynamic_cast<CChineseMob*>(aiMobBuilder->GetProduct());
}

CMalayFemale* CManufactureManager::CreateMalayFemale()
{
	characterBuilder->SetManufactureMalayFemale();
	return dynamic_cast<CMalayFemale*>(characterBuilder->GetProduct());
}

CMalayMob* CManufactureManager::CreateMalayMob()
{
	aiMobBuilder->SetManufactureMALAYMOB();
	return dynamic_cast<CMalayMob*>(aiMobBuilder->GetProduct());
}

CPowerUp* CManufactureManager::CreatePowerUpRecovery()
{
	powerUpBuilder->SetManufactureRECOVERY();
	return dynamic_cast<CPowerUp*>(powerUpBuilder->GetProduct());
}

CPowerUp* CManufactureManager::CreatePowerUpPoints()
{
	powerUpBuilder->SetManufacturePOINTS();
	return dynamic_cast<CPowerUp*>(powerUpBuilder->GetProduct());
}

CPowerUp* CManufactureManager::CreatePowerUpInvincible()
{
	powerUpBuilder->SetManufactureINVINCIBLE();
	return dynamic_cast<CPowerUp*>(powerUpBuilder->GetProduct());
}

CPowerUp* CManufactureManager::CreatePowerUpJumpHigh()
{
	powerUpBuilder->SetManufactureHIGHJUMP();
	return dynamic_cast<CPowerUp*>(powerUpBuilder->GetProduct());
}

CPowerUp* CManufactureManager::CreatePowerUpSpeedUp()
{
	powerUpBuilder->SetManufactureSPEEDUP();
	return dynamic_cast<CPowerUp*>(powerUpBuilder->GetProduct());
}
