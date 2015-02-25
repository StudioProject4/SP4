#pragma once
#include "BaseObject.h"

#include <queue>
#include <vector>

#include "ManufactureManager.h"

class CObjectManager :
	public CEntity
{
public:
	typedef std::vector<CBaseObject*> TObjectListVector;
	typedef std::deque<CBaseObject*> TObjectListQueue;
	TObjectListVector objectList;
	TObjectListQueue inactiveObjectList;
	CManufactureManager* manufacturer;
	//CObjectManager(void);

public:
	//static CObjectManager* instance;
	//static CObjectManager* GetInstance();
	CObjectManager(void);
	~CObjectManager(void);

	bool Update();
	bool Init();
	bool Reset();
	bool CleanUp();
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
};

