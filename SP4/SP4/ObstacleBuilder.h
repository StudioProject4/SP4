#pragma once
#include "ObstacleFactory.h"
class CObstacleBuilder
{
public:

	CObstacleFactory* factory;
public:
	CObstacleBuilder(void);
	~CObstacleBuilder(void);
	
	void SetManufactureLeverDoor();
	void SetManufactureDoor();
	void SetManufactureChinesePoints();
	void SetManufactureMalayPoints();
	void SetManufactureChineseHp();
	void SetManufactureMalayHp();
	CObstacleFactory* GetFactory();
	CObstacleBase* GetProduct();

};

