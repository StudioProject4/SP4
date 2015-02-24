#pragma once

class CAIMobBuilder;
class CPowerUpBuilder;
class CCharacterBuilder;
class CChineseMale;
class CChineseMob;
class CMalayFemale;
class CMalayMob;
class CPowerUp;

class CManufactureManager
{
private:
	CManufactureManager(void);
public:
	CAIMobBuilder* aiMobBuilder;
	CPowerUpBuilder* powerUpBuilder;
	CCharacterBuilder* characterBuilder;
public:
	
	static CManufactureManager* instance;
	static CManufactureManager* GetInstance();
	~CManufactureManager(void);

	CChineseMale* CreateChineseMale();
	CChineseMob* CreateChineseMob();
	CMalayFemale* CreateMalayFemale();
	CMalayMob* CreateMalayMob();
	CPowerUp* CreatePowerUpRecovery();
	CPowerUp* CreatePowerUpPoints();
	CPowerUp* CreatePowerUpInvincible();
	CPowerUp* CreatePowerUpJumpHigh();
	CPowerUp* CreatePowerUpSpeedUp();
};

