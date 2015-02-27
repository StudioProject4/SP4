#include "ObstacleFactory.h"

#include "ObstacleBase.h"
#include "LeverDoor.h"
#include "Door.h"

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

		default:
				std::cout << "<ERROR> Invalid Obstacle creation" << std::endl;
			break;

		case OBSTACLE_NONE:

			std::cout << "<ERROR> Invalid Obstacle creation" << std::endl;
			break;

		case OBSTACLE_LEVERDOOR:
			product = new CLeverDoor();
			break;

		case OBSTACLE_DOOR:
			product = new CDoor();
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
	std::cout<<currentManufactureType<<std::endl;
	currentManufactureType = this->OBSTACLE_LEVERDOOR;
}
void CObstacleFactory::SetManufactureDoor()
{
	currentManufactureType = this->OBSTACLE_DOOR;
}