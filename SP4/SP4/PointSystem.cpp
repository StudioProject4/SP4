#include "PointSystem.h"

CPointSystem :: CPointSystem()
{
	points = 0;	
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
	{
		this->points = points;
	}
}

int CPointSystem :: GetPoints()
{
	return points;
}