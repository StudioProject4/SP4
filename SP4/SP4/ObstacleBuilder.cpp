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
	
CObstacleFactory* CObstacleBuilder::GetFactory()
{
	return factory;
}
	
CObstacleBase* CObstacleBuilder::GetProduct()
{
	factory->CreateProduct();
	return factory->GetProduct();
}