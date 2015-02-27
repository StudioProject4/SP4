#pragma once
#include "ObstacleFactory.h"
class CObstacleBuilder
{
public:

	CObstacleFactory* factory;

	CObstacleBuilder(void);
	~CObstacleBuilder(void);
	
	void SetManufactureLeverDoor();
	void SetManufactureDoor();
	CObstacleFactory* GetFactory();
	CObstacleBase* GetProduct();

};

