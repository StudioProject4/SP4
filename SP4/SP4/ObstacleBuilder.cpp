#include "ObstacleBuilder.h"


CObstacleBuilder::CObstacleBuilder(void)
{
}


CObstacleBuilder::~CObstacleBuilder(void)
{
}

void CObstacleBuilder::SetManufactureLeverDoor()
{
	factory->SetManufactureLeverDoor();
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