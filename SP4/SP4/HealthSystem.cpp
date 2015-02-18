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
	health -= 1;
}

void CHealthSystem :: RecoverHealth()
{
	health += 1;
}
