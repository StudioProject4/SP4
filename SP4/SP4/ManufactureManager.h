#pragma once

class CAIMobBuilder;
class CPowerUpBuilder;
class CCharacterBuilder;
class CObstacleBuilder;
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
class CObstacleBase;
class CLeverDoor;
class CDoor;
class CChinesePoints;
class CMalayPoints;
class CChineseHpReduce;
class CMalayHpReduce;
class CWinCondition;


class CManufactureManager
{
private:
	CManufactureManager(void);
public:
	CAIMobBuilder* aiMobBuilder;
	CPowerUpBuilder* powerUpBuilder;
	CCharacterBuilder* characterBuilder;
	CObstacleBuilder* obstacleBuilder;

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
	CLeverDoor* CreateObstacleLeverDoor();
	CDoor* CreateObstacleDoor();
	CChinesePoints* CreateChinesePoints();
	CMalayPoints* CreateMalayPoints();
	CWinCondition* CreateWinCondition();
	CChineseHpReduce* CreateChineseHpReduce();
	CMalayHpReduce* CreateMalayHpReduce();
};

