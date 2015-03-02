#pragma once

#include "CodeDefination.h"

#ifdef NETWORK_CODE
#include "RakNet\WindowsIncludes.h"
#include "RakNet\BitStream.h"
#endif

#include "BaseObject.h"

#include <queue>
#include <vector>

#include "ManufactureManager.h"
//#include "SpatialPartion.h"

class CSpatialPartion;
class CTestBallObject;

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
	bool Update(int multiplayerMode);
	bool Update();
	bool Init();
	bool Reset();
	bool CleanUp();

	bool LoadingSetup();

	void CheckCollisionCharacterWithObject(CBaseObject* a_obj, TObjectListVector& listOfObjectToCheck,int startingIndex = 0);
	void CheckObjectCollision(CBaseObject* a_obj, TObjectListVector& listOfObjectToCheck,int startingIndex);
	void UpdateCollision();
	void AddObject(CBaseObject* a_obj);

#ifdef NETWORK_CODE
	void WriteAllObjects(RakNet::BitStream &bs);
#endif

	CBaseObject* FindObjectWithName(std::string objectName);
	CBaseObject* FindObjectWithTag(std::string objectTag);
	CBaseObject* FindObjectWithGenericTag(std::string objectTag);
	TObjectListVector FindObjectsWithName(std::string objectName);
	TObjectListVector FindObjectsWithTag(std::string objectTag);
	TObjectListVector FindObjectsWithGenericTag(std::string objectTag);

	//CBaseObject* FetchObject();
	CBaseObject* FetchObjectWithName(std::string objectName);
	CBaseObject* FetchObjectWithTag(std::string objectTag);
	CBaseObject* FetchObjectWithGenericTag(std::string objectTag);

	bool ChangeSpatialParition(CSpatialPartion* newSP);

#ifdef SP_V2
	void UpdateGridTestBallCheckCall();
	void UpdateGridCheckCall();
#endif

	void PrintDebugAllActiveObjects();
	void PrintDebugAllInActiveObjects();
	void PrintDebugInformation();

	inline void AddToInActiveList(CBaseObject* a_obj)
	{ 
		a_obj->active = false;
		this->inactiveObjectList.push_back(a_obj);
	};

	inline void AddToActiveList(CBaseObject* a_obj)
	{
		a_obj->active = true;
		this->objectList.push_back(a_obj);
	};

};

