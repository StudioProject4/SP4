#pragma once
#include "ObstacleFactory.h"
class CObstacleBuilder
{
public:

	CObstacleFactory* factory;

	CObstacleBuilder(void);
	~CObstacleBuilder(void);
	
	void SetManufactureLeverDoor();
	CObstacleFactory* GetFactory();
	CObstacleBase* GetProduct();

};

