#include "ObstacleFactory.h"

#include "ObstacleBase.h"
#include "LeverDoor.h"

CObstacleFactory::CObstacleFactory(void)
	: currentManufactureType(OBSTACLE_NONE)
{
}

CObstacleFactory::CObstacleFactory(EObstacleType typeToMake)
	: currentManufactureType(typeToMake)
{
}

CObstacleFactory::~CObstacleFactory(void)
{
}

void CObstacleFactory::CreateProduct()
{
	switch(currentManufactureType)
	{
	case OBSTACLE_NONE:

		std::cout << "<ERROR> Invalid Obstacle creation" << std::endl;
		break;
	case OBSTACLE_LEVERDOOR:

		product = new CLeverDoor();
		break;
	}
}
	
CObstacleBase* CObstacleFactory::GetProduct()
{
	return product;
}
	
void CObstacleFactory::SetManufactureType(EObstacleType typeToMake)
{
	currentManufactureType = typeToMake;
}
	
void CObstacleFactory::setManufactureNone()
{
	currentManufactureType = this->OBSTACLE_NONE;
}
	
void CObstacleFactory::SetManufactureLeverDoor()
{
	currentManufactureType = this->OBSTACLE_LEVERDOOR;
}
