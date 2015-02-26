#include "ObjectManager.h"

#include "SpatialPartion.h"
#include "WindowManager.h"
//CObjectManager* CObjectManager::instance = 0;

CObjectManager::CObjectManager(void)
	:SP(0)
	,numOfUniqueId(-1)
{
	Init();
}
//CObjectManager* CObjectManager::GetInstance()
//{
//	if(instance == 0)
//	{
//		instance = new CObjectManager();
//	}
//	return instance;
//}

CObjectManager::~CObjectManager(void)
{
}
void CObjectManager::AddObject(CBaseObject* a_obj)
{
	objectList.push_back(a_obj);
	SP->AddObject(a_obj);
	++numOfUniqueId;
	a_obj->id = numOfUniqueId;
}
bool CObjectManager::Render()
{
	for(TObjectListVector::iterator it = objectList.begin(); it!=objectList.end(); ++it)
	{
		if( (*it)->active == true)
		{
			(*it)->Render();	
		}
	}
	return true;
}

bool CObjectManager::Update()
{
	for(TObjectListVector::iterator it = objectList.begin(); it!=objectList.end(); ++it)
	{
		if( (*it)->active == true)
		{
			(*it)->Update();
		
			//(*it)->Render();
		}else
		{
			inactiveObjectList.push_back((*it));
			objectList.erase(it);
		}
	}
	return true;
}

bool CObjectManager::Init()
{
	name = "objectmanager";
	manufacturer = CManufactureManager::GetInstance();
	SP = new CSpatialPartion(CWindowManager::GetInstance()->GetOriginalWindowWidth(),CWindowManager::GetInstance()->GetOriginalWindowHeight(),TILE_SIZE*2,TILE_SIZE*2);
	return true;
}

bool CObjectManager::Reset()
{
	if(CleanUp())
	{
		return Init();
	}	
	return false;
}

bool CObjectManager::CleanUp()
{
	if(manufacturer != 0)
	{
		delete manufacturer;
		manufacturer = 0;
	}

	for(TObjectListVector::iterator it = objectList.begin(); it!=objectList.end(); ++it)
	{
		if( (*it) != NULL )
		{
			(*it)->CleanUp();
			(*it)->Release();
			(*it) = NULL;			
		}
	}

	for(TObjectListQueue::iterator it2 = inactiveObjectList.begin(); it2!=inactiveObjectList.end(); ++it2)
	{
		if( (*it2) != NULL )
		{
			(*it2)->CleanUp();
			(*it2)->Release();
			(*it2) = NULL;			
		}
	}
	objectList.clear();
	inactiveObjectList.clear();

	return true;
}

CBaseObject* CObjectManager::FindObjectWithName(std::string objectName)
{
	const char* compare = objectName.c_str();

	for(TObjectListVector::iterator it = objectList.begin(); it!=objectList.end(); ++it)
	{
		if( (*it)->name == compare )
		{
			return (*it);
		}
	}
	return 0;
}

CBaseObject* CObjectManager::FindObjectWithTag(std::string objectTag)
{
	const char* compare = objectTag.c_str();

	for(TObjectListVector::iterator it = objectList.begin(); it!=objectList.end(); ++it)
	{
		if( (*it)->tag == compare )
		{
			return (*it);
		}
	}
	return 0;
}

CBaseObject* CObjectManager::FindObjectWithGenericTag(std::string objectTag)
{
	const char* compare = objectTag.c_str();

	for(TObjectListVector::iterator it = objectList.begin(); it!=objectList.end(); ++it)
	{
		if( (*it)->genericTag == compare )
		{
			return (*it);
		}
	}
	return 0;
}

CObjectManager::TObjectListVector CObjectManager::FindObjectsWithName(std::string objectName)
{
	const char* compare = objectName.c_str();
	TObjectListVector resultlist;

	for(TObjectListVector::iterator it = objectList.begin(); it!=objectList.end(); ++it)
	{
		if( (*it)->genericTag == compare )
		{
			resultlist.push_back((*it));
		}
	}
	return resultlist;
}

CObjectManager::TObjectListVector CObjectManager::FindObjectsWithTag(std::string objectTag)
{
	const char* compare = objectTag.c_str();
	TObjectListVector resultlist;

	for(TObjectListVector::iterator it = objectList.begin(); it!=objectList.end(); ++it)
	{
		if( (*it)->genericTag == compare )
		{
			resultlist.push_back((*it));
		}
	}
	return resultlist;
}

CObjectManager::TObjectListVector CObjectManager::FindObjectsWithGenericTag(std::string objectTag)
{
	const char* compare = objectTag.c_str();
	TObjectListVector resultlist;

	for(TObjectListVector::iterator it = objectList.begin(); it!=objectList.end(); ++it)
	{
		if( (*it)->genericTag == compare )
		{
			resultlist.push_back((*it));
		}
	}
	return resultlist;
}

CBaseObject* CObjectManager::FetchObject()
{
	CBaseObject* a_obj = NULL;

	if(!inactiveObjectList.empty())
	{
		a_obj =  inactiveObjectList.front();
		inactiveObjectList.pop_front();
	}else
	{
		std::cout<<"<FATAL ERROR> Cannot Find inactive gameobject to recycle"<<std::endl;
	}
	return a_obj;
}

CBaseObject* CObjectManager::FetchObjectWithName(std::string objectName)
{
	CBaseObject* a_obj = NULL;

	if(!inactiveObjectList.empty())
	{
		const char* compare = objectName.c_str();

		for(TObjectListQueue::iterator it = inactiveObjectList.begin(); it!=inactiveObjectList.end(); ++it)
		{
			if( (*it)->name == compare )
			{
				a_obj = (*it);
				inactiveObjectList.pop_front();
			}
		}
	}else
	{
		std::cout<<"<FATAL ERROR> Cannot Find inactive gameobject to recycle"<<std::endl;
	}
	return a_obj;
}

CBaseObject* CObjectManager::FetchObjectWithTag(std::string objectTag)
{
	CBaseObject* a_obj = NULL;


	if(!inactiveObjectList.empty())
	{
		const char* compare = objectTag.c_str();

		for(TObjectListQueue::iterator it = inactiveObjectList.begin(); it!=inactiveObjectList.end(); ++it)
		{
			if( (*it)->tag == compare )
			{
				a_obj = (*it);
				inactiveObjectList.pop_front();
			}
		}
	}else
	{
		std::cout<<"<FATAL ERROR> Cannot Find inactive gameobject to recycle"<<std::endl;
	}
	return a_obj;
}

CBaseObject* CObjectManager::FetchObjectWithGenericTag(std::string objectTag)
{
	CBaseObject* a_obj = NULL;

	if(!inactiveObjectList.empty())
	{
		const char* compare = objectTag.c_str();

		for(TObjectListQueue::iterator it = inactiveObjectList.begin(); it!=inactiveObjectList.end(); ++it)
		{
			if( (*it)->genericTag == compare )//change to generic tag later
			{
				a_obj = (*it);
				inactiveObjectList.pop_front();
			}
		}
	}else
	{
		std::cout<<"<FATAL ERROR> Cannot Find inactive gameobject to recycle"<<std::endl;
	}
	return a_obj;
}
