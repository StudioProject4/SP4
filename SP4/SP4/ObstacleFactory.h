#pragma once
#include "Factory.h"

class CObstacleBase;

class CObstacleFactory
{
public:
	
	enum EObstacleType
	{
		OBSTACLE_NONE,
		OBSTACLE_LEVERDOOR,
		OBSTACLE_DOOR,
		OBSTACLE_TOTAL
	};

	CObstacleFactory(void);
	CObstacleFactory(EObstacleType typeToMake);
	~CObstacleFactory(void);

	EObstacleType currentManufactureType;
	CObstacleBase* product;

	void CreateProduct();
	CObstacleBase* GetProduct();
	void SetManufactureType(EObstacleType typeToMake);
	void setManufactureNone();
	void SetManufactureLeverDoor();
	void SetManufactureDoor();

};

