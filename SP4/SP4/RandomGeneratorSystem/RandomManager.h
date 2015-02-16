#ifndef RANDOMMANAGER_H
#define RANDOMMANAGER_H
#include "RandomGenerator.h"

class CRandomManager
{
private:
	unsigned short basechance;//max number of range
	unsigned short currentchance;// the resultant// must be in between max range and 0
	unsigned short blocker;//the number of times which the chance will be blocked.Blocker must expires first then allow player to have a chance again.
	unsigned short turntoguranteechance;// the number of times until the chance will be guranteed/pretty much like the reverse blocker
	float leeway;// the amount of increase chanced or reduced chance
	unsigned short guranteedturn;//the number of turn to secure the loot
	unsigned short turnused;//the amount of turn player used to get the loot
	//static CRandomManager * Instance;

	unsigned short initbasechance;//to store the init values,because there is an overloaded constructor,so i cannot just reset using those valuesdefault constructor 
	unsigned short initblocker;
	unsigned short initturntoguranteechance;
	float compulsoryblockerpercent;

	
protected:
	CRandomGenerator * RNG;

public:

	//static CRandomManager * GetInstance();
	CRandomManager();
	CRandomManager(unsigned short numOfBaseChance, float guranteelootturnpercent, float fixeddelaypercent);
	CRandomManager(unsigned short bc, unsigned short cc, unsigned short b, unsigned short k);
	~CRandomManager();

	CRawData * rawdata ;

	void ReValueRawData(bool randomIntervel, bool onceRandom, short intervalue = 10);
	unsigned short getCurrentBaseChance();
	unsigned short getCurrentChance();
	unsigned short getNumberOfBlocker();
	unsigned short getNumberOfKey();
	float getCurrentLeeway();
	unsigned short getNumofGuranteedTurn();
	CRandomGenerator * getRandomGenerator();
	

	void setCurrentBaseChance(unsigned short);
	void setCurrentChance(unsigned short);
	void setNumberOfBlocker(unsigned short);
	void setNumberOfKey(unsigned short);
	void setCurrentLeeway(float);

	void ResetAllValues();
	void ResetValues(bool adjustSmallPrority = false, bool adjustBigPrority = false, float BigAdjustPercent = 1, float SmallAdjustPercent = 1);
	void SetAllValues(unsigned short bc, unsigned short cc, unsigned short b, unsigned short k);
	void AutoSetNumOfGurantee();
	void AutoSetNumOfGurantee(short newkey);
	bool DestinyRoll(bool lowproritymode = false, bool highproritymode = false, float lowerProrityfrequency = 1 , float upperProrityfrequency = 1);//one is regular blocker frequecy
	void Print();
};

#endif