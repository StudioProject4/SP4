#pragma once

class CAIMobBuilder;
class CPowerUpBuilder;
class CCharacterBuilder;
class CChineseMale;
class CChineseMob;
class CMalayFemale;
class CMalayMob;
class CPowerUp;
class CHealthPU;
class CPointsAddPU;
class CSpeedPU;
class CJumpPU;
class CInvinciblePU;

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
	CHealthPU* CreatePowerUpRecovery();
	CPointsAddPU* CreatePowerUpPoints();
	CInvinciblePU* CreatePowerUpInvincible();
	CJumpPU* CreatePowerUpJumpHigh();
	CSpeedPU* CreatePowerUpSpeedUp();
};

