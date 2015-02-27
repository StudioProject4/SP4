#include "ManufactureManager.h"

#include "AIMobBuilder.h"
#include "PowerUpBuilder.h"
#include "CharacterBuilder.h"
#include "ObstacleBuilder.h"
#include "ChineseMale.h"
#include "ChineseMob.h"
#include "MalayFemale.h"
#include "MalayMob.h"
#include "PowerUp.h"
#include "HealthPU.h"
#include "PointsAddPU.h"
#include "JumpPU.h"
#include "InvinciblePU.h"
#include "SpeedPU.h"
#include "LeverDoor.h"
#include "Door.h"

CManufactureManager* CManufactureManager::instance = 0;

CManufactureManager::CManufactureManager(void)
{
	aiMobBuilder = new CAIMobBuilder;
	powerUpBuilder = new CPowerUpBuilder ;
	characterBuilder = new CCharacterBuilder;
	obstacleBuilder = new CObstacleBuilder;
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
	delete obstacleBuilder;
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

CHealthPU* CManufactureManager::CreatePowerUpRecovery()
{
	powerUpBuilder->SetManufactureRECOVERY();
	return dynamic_cast<CHealthPU*>(powerUpBuilder->GetProduct());
}

CPointsAddPU* CManufactureManager::CreatePowerUpPoints()
{
	powerUpBuilder->SetManufacturePOINTS();
	return dynamic_cast<CPointsAddPU*>(powerUpBuilder->GetProduct());
}

CInvinciblePU* CManufactureManager::CreatePowerUpInvincible()
{
	powerUpBuilder->SetManufactureINVINCIBLE();
	return dynamic_cast<CInvinciblePU*>(powerUpBuilder->GetProduct());
}

CJumpPU* CManufactureManager::CreatePowerUpJumpHigh()
{
	powerUpBuilder->SetManufactureHIGHJUMP();
	return dynamic_cast<CJumpPU*>(powerUpBuilder->GetProduct());

}

CSpeedPU* CManufactureManager::CreatePowerUpSpeedUp()
{
	powerUpBuilder->SetManufactureSPEEDUP();
	return dynamic_cast<CSpeedPU*>(powerUpBuilder->GetProduct());
}

CLeverDoor* CManufactureManager::CreateObstacleLeverDoor()
{
	obstacleBuilder->SetManufactureLeverDoor();
	return dynamic_cast<CLeverDoor*>(obstacleBuilder->GetProduct());

}
CDoor* CManufactureManager::CreateObstacleDoor()
{
	obstacleBuilder->SetManufactureDoor();
	return dynamic_cast<CDoor*>(obstacleBuilder->GetProduct());
}