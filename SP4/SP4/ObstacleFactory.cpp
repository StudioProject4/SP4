#include "ObstacleFactory.h"

#include "ObstacleBase.h"
#include "LeverDoor.h"
#include "Door.h"
#include "ChinesePoints.h"
#include "MalayPoints.h"
#include "ChineseHpReduce.h"
#include "MalayHpReduce.h"
#include "WinCondition.h"

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

		case OBSTACLE_CHINAPTS:
			product = new CChinesePoints();
			break;
		case OBSTACLE_MALAYPTS:
			product = new CMalayPoints();
			break;
		case OBSTACLE_CHINAHP:
			product = new CChineseHpReduce();
			break;
		case OBSTACLE_MALAYHP:
			product = new CMalayHpReduce();
			break;
		case OBSTACLE_WINLOSE:
			product = new CWinCondition();
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

void CObstacleFactory::SetManufactureChinesePoints()
{
	currentManufactureType = this->OBSTACLE_CHINAPTS;
}
	
void CObstacleFactory::SetManufactureMalayPoints()
{
	currentManufactureType = this->OBSTACLE_MALAYPTS;
}

void CObstacleFactory::SetManufactureChineseHp()
{
	currentManufactureType = this->OBSTACLE_CHINAHP;
}
	
void CObstacleFactory::SetManufactureMalayHp()
{
	currentManufactureType = this->OBSTACLE_MALAYHP;
}

void CObstacleFactory::SetManufactureWinLoseCondition()
{
	currentManufactureType = this->OBSTACLE_WINLOSE;
}