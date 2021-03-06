#include "ObstacleBuilder.h"
#include "ObstacleFactory.h"

CObstacleBuilder::CObstacleBuilder(void)
{
	factory = new CObstacleFactory();
}

CObstacleBuilder::~CObstacleBuilder(void)
{
	delete factory;
}
void CObstacleBuilder::SetManufactureDoor()
{
	factory->SetManufactureDoor();
}
void CObstacleBuilder::SetManufactureLeverDoor()
{

	factory->SetManufactureLeverDoor();
}

void CObstacleBuilder::SetManufactureChinesePoints()
{
	factory->SetManufactureChinesePoints();
}
	
void CObstacleBuilder::SetManufactureMalayPoints()
{
	factory->SetManufactureMalayPoints();
}

void CObstacleBuilder::SetManufactureChineseHp()
{
	factory->SetManufactureChineseHp();
}
	
void CObstacleBuilder::SetManufactureMalayHp()
{
	factory->SetManufactureMalayHp();
}

void CObstacleBuilder::SetManufactureWinLoseCondition()
{
	factory->SetManufactureWinLoseCondition();
}

CObstacleFactory* CObstacleBuilder::GetFactory()
{
	return factory;
}
	
CObstacleBase* CObstacleBuilder::GetProduct()
{
	factory->CreateProduct();
	return factory->GetProduct();
}