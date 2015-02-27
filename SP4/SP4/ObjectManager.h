#pragma once
#include "BaseObject.h"

#include <queue>
#include <vector>

#include "ManufactureManager.h"

class CSpatialPartion;

class CObjectManager :
	public CEntity
{
public:
	typedef std::vector<CBaseObject*> TObjectListVector;
	//typedef std::deque<CBaseObject*> TObjectListQueue;
	TObjectListVector objectList;
	TObjectListVector inactiveObjectList;
	CManufactureManager* manufacturer;
	CSpatialPartion* SP;
	int numOfUniqueId;
	//CObjectManager(void);

public:
	//static CObjectManager* instance;
	//static CObjectManager* GetInstance();
	CObjectManager(void);
	~CObjectManager(void);
	bool Render();
	bool Update();
	bool Init();
	bool Reset();
	bool CleanUp();
	void CheckCollisionCharacterWithObject(CBaseObject* a_obj, TObjectListVector& listOfObjectToCheck,int startingIndex);
	void CheckObjectCollision(CBaseObject* a_obj, TObjectListVector& listOfObjectToCheck,int startingIndex);
	void UpdateCollision();
	void AddObject(CBaseObject* a_obj);
	CBaseObject* FindObjectWithName(std::string objectName);
	CBaseObject* FindObjectWithTag(std::string objectTag);
	CBaseObject* FindObjectWithGenericTag(std::string objectTag);
	TObjectListVector FindObjectsWithName(std::string objectName);
	TObjectListVector FindObjectsWithTag(std::string objectTag);
	TObjectListVector FindObjectsWithGenericTag(std::string objectTag);

	CBaseObject* FetchObject();
	CBaseObject* FetchObjectWithName(std::string objectName);
	CBaseObject* FetchObjectWithTag(std::string objectTag);
	CBaseObject* FetchObjectWithGenericTag(std::string objectTag);
	void PrintDebugAllActiveObjects();
	void PrintDebugAllInActiveObjects();
	void PrintDebugInformation();
};

