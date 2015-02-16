#include "RandomManager.h"

//CRandomManager * CRandomManager::Instance = NULL;

CRandomManager::CRandomManager()
{
	initbasechance = basechance = 5;
	currentchance = 1;
	initblocker = blocker = 0;
	initturntoguranteechance = turntoguranteechance = rint(initbasechance*0.5);
	guranteedturn = initturntoguranteechance + initblocker;
	AutoSetNumOfGurantee();
	compulsoryblockerpercent = 0.0f;

	RNG = CRandomGenerator::GetInstance();
	RNG->Init(CRandomGenerator::RNG_NON_DETERMINISTIC, CRandomGenerator::RNG_RANDOM_TWISTER);

	rawdata = &RNG->rawdata;
}
CRandomManager::CRandomManager(unsigned short numOfBaseChance,float guranteelootturnpercent,float fixeddelaypercent)
{
	initbasechance = basechance = numOfBaseChance;
	currentchance = 1;
	initblocker = blocker = 0;
	initturntoguranteechance = turntoguranteechance = rint(initbasechance*guranteelootturnpercent);
	guranteedturn = initturntoguranteechance + initblocker;
	AutoSetNumOfGurantee();
	compulsoryblockerpercent = fixeddelaypercent;

	RNG = CRandomGenerator::GetInstance();
	RNG->Init(CRandomGenerator::RNG_NON_DETERMINISTIC, CRandomGenerator::RNG_RANDOM_TWISTER);

	rawdata = &RNG->rawdata;
	
}
void CRandomManager::ReValueRawData(bool randomIntervel, bool onceRandom, short intervalue )
{
	if (rawdata != NULL)
	{
		rawdata->ReInitValues(randomIntervel, onceRandom, intervalue);
	}
	else
	{
		cout << "RawData pointer is NULL" << endl;
	}
	
}
CRandomManager::CRandomManager(unsigned short bc, unsigned short cc,unsigned short b,unsigned short k)
{
	initbasechance = basechance = bc;
	currentchance = cc;
	initblocker =  blocker = b;
	initturntoguranteechance = turntoguranteechance = k;
	AutoSetNumOfGurantee();
	guranteedturn = initturntoguranteechance + initblocker;
	compulsoryblockerpercent = 0.0f;

	RNG = CRandomGenerator::GetInstance();
	RNG->Init(CRandomGenerator::RNG_NON_DETERMINISTIC, CRandomGenerator::RNG_RANDOM_TWISTER);

	rawdata = &RNG->rawdata;
}
CRandomManager::~CRandomManager()
{

}
//CRandomManager * CRandomManager::GetInstance(void)
//{
//	if (Instance == NULL)
//	{
//		Instance = new CRandomManager();
//	}
//	return Instance;
//}
void CRandomManager::ResetAllValues()
{
	initbasechance = basechance = 5;
	currentchance = 1;
	initblocker = blocker = 0;
	initturntoguranteechance = turntoguranteechance = 10;
	guranteedturn = initturntoguranteechance + initblocker;
	AutoSetNumOfGurantee();
	compulsoryblockerpercent = 0.0f;
}
void CRandomManager::ResetValues(bool adjustSmallPrority,bool adjustBigPrority,float BigAdjustPercent, float SmallAdjustPercent)//to prepare the DestinyRoll another iteration.*Note* Successfully getting a true from DetinyRoll is consider one complete iteration
{

	while (BigAdjustPercent > 1)//if user mistake it as value such as 100,37,68. Instead of 0.1,0.2,0.3 basicaly in fraction.
	{	
		BigAdjustPercent *= 0.1;
	}
	while (SmallAdjustPercent > 1)
	{
		SmallAdjustPercent *= 0.1;
	}
	//values for calculation
	unsigned short baseblocker = 0;
	unsigned short balance = 0;
	unsigned short ExperienceAdjustment = 0;
	//values which are confirmed;
	basechance = initbasechance;
	currentchance = 1;
	turntoguranteechance = initturntoguranteechance;

	//amount of new blocker calculation
	baseblocker = initblocker + rint(turntoguranteechance * compulsoryblockerpercent);
	balance = initturntoguranteechance - turnused;
	if (balance > initturntoguranteechance * 0.5 )//if the the turn is lucky
	{
		//cout << "User is lucky" << endl;
		rawdata->TranverseSelfIndex(false, true);
		//cout << "current backwardindex" << rawdata->bcurrentindex << endl;
		ExperienceAdjustment = rint(    MathPlus::SinCurve( Math::DegreeToRadian(rawdata->PositiveIntergalData[rawdata->bcurrentindex]) ) * 10   ); //give backward sin curve experience adjustment// backward sin curve is from 1 to 0 btw

	}else//if user is unlucky 
	{
		//cout << "User is Unlucky" << endl;
		rawdata->TranverseSelfIndex(true, true);
		//cout << "current foward index" << rawdata->fcurrentindex << endl;
		ExperienceAdjustment = rint(MathPlus::SinCurve(Math::DegreeToRadian(rawdata->PositiveIntergalData[rawdata->fcurrentindex])) * 10); //give Forward sin curve experience adjustment // forward sin curve is from 0 to 1 btw
	}

	//the if blocks below are just to determine whether to fine adjust the resultant blocker.
	if (adjustSmallPrority == false && adjustBigPrority == false)
	{
		//this is without any adjustment
		blocker = baseblocker + ExperienceAdjustment;//this can be quite harsh =P
		//cout << "not adjust anything" << endl;
	}
	else
	{
		if (adjustSmallPrority == true)//both big and small adjust can happen together.
		{
			//cout << " adjusting small blocker" << endl;
			//cout << SmallAdjustPercent << endl;
			//cout << "Blocker before small adjust " << baseblocker << endl;
			blocker = baseblocker + rint(ExperienceAdjustment * SmallAdjustPercent);
			//cout << "Blocker after small adjust " << blocker << endl;
		}
		if (adjustBigPrority == true)
		{
			//cout << " adjusting big blocker" << endl;
			//cout << BigAdjustPercent << endl;
			//cout << "Blocker before Bigger adjust " << blocker << endl;
			short digit = 0;
			unsigned short temp = basechance;
			
			while (temp > 1)
			{
				temp *= 0.1;
				++digit;
			}
			//cout << "Digit"<<digit << endl;
			//cout << " basechance" << basechance << endl;
			float influence = rint( blocker * BigAdjustPercent * digit);

			if ( (basechance + influence) < 0)
			{
				basechance = 1;
			}
			else
			{
				basechance += influence;
			}
			//cout << "Value in question" << influence << endl;
			//cout << "Adjusted basechance" << basechance << endl;
			//cout << "Blocker after Bigger adjust " << blocker << endl;
		}

	}

	
	//cout <<"BLOCKER for next till next loot: "<< blocker << endl;
	//cout <<"adjustment blocker"<< ExperienceAdjustment << endl;
	//cout << "Turn Used to get Loot " << turnused << endl;

	//cout << "Amount of ExperienceAdjustment " << ExperienceAdjustment << endl;



	//others reinit
	leeway = basechance / turntoguranteechance;
	guranteedturn = turntoguranteechance + blocker;
	turnused = 0;


	//RNG = CRandomGenerator::GetInstance();
	//RNG->Init(CRandomGenerator::RNG_NON_DETERMINISTIC, CRandomGenerator::RNG_RANDOM_TWISTER);
}
void CRandomManager::SetAllValues(unsigned short bc, unsigned short cc, unsigned short b, unsigned short k)
{
	basechance = bc;
	currentchance = cc;
	blocker = b;
	turntoguranteechance = k;
	AutoSetNumOfGurantee();
	guranteedturn = turntoguranteechance + blocker;
	turnused = 0;
	RNG = CRandomGenerator::GetInstance();
	RNG->Init(CRandomGenerator::RNG_NON_DETERMINISTIC, CRandomGenerator::RNG_RANDOM_TWISTER);
}
void CRandomManager::AutoSetNumOfGurantee()
{
	if (turntoguranteechance > 0)//protect against divide by zero.
	{
		leeway = basechance / turntoguranteechance;
	}
	else
	{
		turntoguranteechance = 1;
		leeway = basechance;
		//cout << "ERROR: turntoguranteechance cannot be zero,auto set to gurantee next chance." << endl;
	}
}
void CRandomManager::AutoSetNumOfGurantee(short newkey)
{
	if (newkey > 0)//protect against divide by zero.
	{
		turntoguranteechance = newkey;
		leeway = basechance / turntoguranteechance;
	}
	else
	{
		turntoguranteechance = 1;
		leeway = basechance;
		//cout << "ERROR: turntoguranteechance cannot be zero,auto set to gurantee next chance." << endl;
	}
}
bool CRandomManager::DestinyRoll(bool lowproritymode, bool highproritymode, float lowerProrityfrequency, float upperProrityfrequency)
{
	bool result = false;
	if (blocker == 0)//if no blocker,then roll
	{
		
		currentchance = RNG->getImmediateResult(0, basechance - leeway);
		AutoSetNumOfGurantee(--turntoguranteechance);
		++turnused;

		if (currentchance == 0)//if tio then reset the chance for next whole iteration
		{
			//cout << "win~!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;

			if (lowproritymode == false && highproritymode == false)
			{
				ResetValues();//prepare for the whole RandomManager next iteration,using normal blocker frequency
			}
			else
			{
				if (lowproritymode == true)
				{
					ResetValues(true, false, upperProrityfrequency, lowerProrityfrequency);
				}
				if (highproritymode == true)
				{
					ResetValues(false, true, upperProrityfrequency, lowerProrityfrequency);
				}
			}
			//ResetAllValues();//if using not as detailed chance.



			result = true;
		}

	}else
	{	
		--blocker;
		//if (blocker > turntoguranteechance)
		//{
		//	cout << "Blocker exceed turntoguranteechance.Effect of this is that blocker must expire first before the turn to gurantee chance will kick in" << endl;
		//}
		//if (blocker < 0)
		//{
		//	cout << "OOpps bad error" << endl;
		//}
		//result = false;
	}
	return result;
}
CRandomGenerator * CRandomManager::getRandomGenerator()
{
	return RNG;
}
unsigned short CRandomManager::getCurrentBaseChance()
{
	return basechance;
}
unsigned short CRandomManager::getCurrentChance()
{
	return currentchance;
}
unsigned short CRandomManager::getNumberOfBlocker()
{
	return blocker;
}
unsigned short CRandomManager::getNumberOfKey()
{
	return turntoguranteechance;
}
void CRandomManager::setNumberOfKey(unsigned short k )
{
	turntoguranteechance = k;
}
float CRandomManager::getCurrentLeeway()
{
	return leeway;
}
void CRandomManager::setCurrentBaseChance(unsigned short bc)
{
	if (bc < 0)
	{
		bc = 0;
	}
	basechance = bc;
}
void CRandomManager::setCurrentChance(unsigned short cc)
{
	if (cc < 0)
	{
		cc = 0;
	}
	currentchance = cc;
}
void CRandomManager::setNumberOfBlocker(unsigned short b)
{
	if (b < 0)
	{
		b = 0;
	}
	blocker = b;
}
void CRandomManager::setCurrentLeeway(float l)
{
	leeway = l;
}
unsigned short  CRandomManager::getNumofGuranteedTurn()
{
	return guranteedturn;
}
void CRandomManager::Print()
{
//	cout << "Random Generator Engine: " << " TYPE: " << RNG->PrintTypeText() << " MODE: " << RNG->PrintModeText() << endl;
	cout << "\nBaseChance: "<< basechance << endl;
	cout << "CurrentChance: " << currentchance << endl;
	cout << "Turned Used to get Loot: " << turnused << endl;
	cout << "Leeway: " << leeway << endl;
	cout << "Bloker: " << blocker << endl;
	cout << "turntoguranteechance: " << turntoguranteechance << endl;
}


