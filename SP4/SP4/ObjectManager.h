#pragma once
#include "RakNet\BitStream.h"
#include "BaseObject.h"

#include <queue>
#include <vector>

#include "ManufactureManager.h"
//#include "SpatialPartion.h"

#include "CodeDefination.h"

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
	void CheckCollisionCharacterWithObject(CBaseObject* a_obj, TObjectListVector& listOfObjectToCheck,int startingIndex = 0);
	void CheckObjectCollision(CBaseObject* a_obj, TObjectListVector& listOfObjectToCheck,int startingIndex);
	void UpdateCollision();
	void AddObject(CBaseObject* a_obj);
	void WriteAllObjects(RakNet::BitStream &bs);
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

	bool ChangeSpatialParition(CSpatialPartion* newSP);

#ifdef SP_V2
	void UpdateGridTestBallCheckCall();
	void UpdateGridCheckCall();
#endif

	void PrintDebugAllActiveObjects();
	void PrintDebugAllInActiveObjects();
	void PrintDebugInformation();
};

