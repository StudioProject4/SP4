#include "PointSystem.h"
#include <stdlib.h>

CPointSystem * CPointSystem :: GetInstance(void)
{
	if(s_instance == NULL)
	{
		s_instance = new CPointSystem();
	}
	return s_instance;
}

void CPointSystem :: Drop(void)
{
	if(s_instance != NULL)
	{
		delete s_instance;
	}
}

CPointSystem * CPointSystem :: s_instance = NULL;

CPointSystem :: CPointSystem()
	:points(0)
{
	//points = 0;	
}

CPointSystem :: ~CPointSystem()
{
	
}

void CPointSystem :: PointsReceive(int points)
{
	//if(hasPowerUp == true)
	//{
	//	this->points = ( points * 2 );	
	//}
	//else
	//{

	this->points += this->points + points;
//	}
}

int CPointSystem :: GetPoints()
{
	return points;
}