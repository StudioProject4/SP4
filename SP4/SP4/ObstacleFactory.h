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
		OBSTACLE_CHINAPTS,
		OBSTACLE_MALAYPTS,
		OBSTACLE_TOTAL
	};

	EObstacleType currentManufactureType;
	CObstacleBase* product;

public:
	CObstacleFactory(void);
	CObstacleFactory(EObstacleType typeToMake);
	~CObstacleFactory(void);

	void CreateProduct();
	CObstacleBase* GetProduct();
	void SetManufactureType(EObstacleType typeToMake);
	void setManufactureNone();
	void SetManufactureLeverDoor();
	void SetManufactureDoor();
	void SetManufactureChinesePoints();
	void SetManufactureMalayPoints();

	//CChinesePoints* CChinesePoints;
};

