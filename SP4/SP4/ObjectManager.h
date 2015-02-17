#pragma once
#include "BaseObject.h"

#include <queue>
#include <vector>

class CObjectManager :
	public CEntity
{
private:
	typedef std::vector<CBaseObject*> TObjectListVector;
	typedef std::deque<CBaseObject*> TObjectListQueue;
	TObjectListVector objectList;
	TObjectListQueue inactiveObjectList;
public:
	CObjectManager(void);
	~CObjectManager(void);

	bool Update();
	bool Init();
	bool Reset();
	bool CleanUp();
	void AddObject(CBaseObject* a_obj);
	CBaseObject* FetchObject();
	CBaseObject* FetchObjectWithName(std::string objectName);
	CBaseObject* FetchObjectWithTag(std::string objectTag);
	CBaseObject* FetchObjectWithGenericTag(std::string objectTag);
};

