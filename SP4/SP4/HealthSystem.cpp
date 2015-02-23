#include "HealthSystem.h"

CHealthSystem :: CHealthSystem()
{
	health = 3;
}

CHealthSystem :: ~CHealthSystem()
{
	
}

void CHealthSystem :: TakeDMG()
{
	if(health != 0)
	{
		health -= 1;
	}
}

void CHealthSystem :: RecoverHealth()
{
	if(health < 4)
	{
		health += 1;
	}
}
int CHealthSystem :: GetHealth()
{
	return health;
}
