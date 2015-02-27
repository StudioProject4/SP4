#include "ObjectManager.h"
#include "Map.h"
#include "SpatialPartion.h"
#include "WindowManager.h"
#include "Sprite.h"
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

void CObjectManager::CheckObjectCollision(CBaseObject* a_obj, TObjectListVector& listOfObjectToCheck,int startingIndex)
{
	CBaseObject* otherObject = nullptr;
	Vector3 OtherSize;
	for(int i = 0; i< listOfObjectToCheck.size();++i)
	{
		otherObject = listOfObjectToCheck[i];//paraphrasing
		if(otherObject!=a_obj)
		{
			OtherSize=otherObject->phys.size;
			if(a_obj->phys.TestCol(otherObject->pos,OtherSize))
			{
				otherObject->OnCollision(a_obj);
			}
		}
	}
}

void CObjectManager::UpdateCollision()
{
	short x = 0;
	short y = 0;
	CBaseObject* a_obj = nullptr;
	for(int i = 0 ; i < SP->cellList.size(); ++i )//loop through all cells
	{
		//get the index of the cells
		x = i % SP->numCellX;
		y = i / SP->numCellX;

		Cell& a_cell = SP->cellList[i];


		for(int j = 0 ; j< a_cell.objectList.size();++j)//loop through all object inside objectlist of a cell
		{
			a_obj = a_cell.objectList[j];
			if(a_obj->genericTag!="Character")
				continue;
			CheckObjectCollision(a_obj,a_cell.objectList, j + 1);//checking a object with a list of object,skipping self check.The List of object is only within it own grid at there
			//checkCollision with neighbouring cells.//the idea is to check only with the cells at a decided direction side
			//for example
			/*
			123
			456
			789
			if current cell is 5, the check will check 1,4,7,and 2. this is to cut down check by half,inside of looping through all neighbouring cell,which could be redudant
			imagne cell 5 check with 1,2,3,4,6,7,8,9 and then the immediate next check 6th cell will check with 3,2,5,8,6,there will be repeated check of 5 with 6 and then 6 with 5 later on.
			
			in coutesy of the source of code from MakingGamesWithBen,youtuber.Thank you.
			*/
			//if(x >0)//nested left cell check
			//{
			//	if(y>0)
			//	{
			//		//top left grid check
			//		CheckObjectCollision(a_obj,SP->GetCell( x-1 , y-1 )->objectList,0);
			//	}
			//	if(y<SP->numCellY-1)
			//	{
			//		//bottom left
			//		CheckObjectCollision(a_obj,SP->GetCell( x-1 , y+1 )->objectList,0);
			//	}
			//}
			////upper check
			//if(y>0)
			//{
			//	CheckObjectCollision(a_obj,SP->GetCell( x , y-1 )->objectList,0);
			//}
		}
	}
}

bool CObjectManager::Update()
{
	//for(TObjectListVector::iterator it = objectList.begin(); it!=objectList.end(); ++it)
	//{
	//	if( (*it)->active == true)
	//	{
	//		(*it)->Update();
	//	
	//		//(*it)->Render();
	//	}else
	//	{
	//		inactiveObjectList.push_back((*it));
	//		//objectList.erase(it);
	//		//using swapping method to delete element.
	//		((*it)) = objectList.back();
	//		objectList.pop_back();
	//	}
	//}
	UpdateCollision();
	for(unsigned short it = 0; it < objectList.size(); ++it)
	{
		if( objectList[it]->active == true)
		{
			objectList[it]->Update();
			SP->UpdateObjectOwnerCell(objectList[it]);
			//(*it)->Render();
		}else
		{
			inactiveObjectList.push_back(objectList[it]);
			//objectList.erase(it);
			//using swapping method to delete element.
			objectList[it] = objectList.back();
			objectList.pop_back();
		}
	}
	
	
	return true;
}

bool CObjectManager::Init()
{
	name = "objectmanager";
	manufacturer = CManufactureManager::GetInstance();
	SP = new CSpatialPartion(CWindowManager::GetInstance()->GetOriginalWindowWidth(),CWindowManager::GetInstance()->GetOriginalWindowHeight(),800,600);
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

	for(TObjectListVector::iterator it2 = inactiveObjectList.begin(); it2!=inactiveObjectList.end(); ++it2)
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
	
	if(SP != nullptr)
	{
		SP->NotifyAllObjectsAlreadyDeletedOutside();
		delete SP;
		SP = nullptr;
	}
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
		//inactiveObjectList.erase(inactiveObjectList.begin());//pop front
		inactiveObjectList.front() = inactiveObjectList.back();//swap to the front and pop back.
		inactiveObjectList.pop_back();
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

		for(unsigned short i = 0 ; i<inactiveObjectList.size();++i)
		{		
			if( inactiveObjectList[i]->name == compare )
			{
				a_obj = inactiveObjectList[i];
				inactiveObjectList[i] = inactiveObjectList.back();
				inactiveObjectList.pop_back();
			}
		}
		//for(TObjectListVector::iterator it = inactiveObjectList.begin(); it!=inactiveObjectList.end(); ++it)
		//{
		//	if( (*it)->name == compare )
		//	{
		//		a_obj = (*it);
		//		//inactiveObjectList.pop_front();
		//		
		//	}
		//}
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

		for(unsigned short i = 0 ; i<inactiveObjectList.size();++i)
		{		
			if( inactiveObjectList[i]->tag == compare )
			{
				a_obj = inactiveObjectList[i];
				inactiveObjectList[i] = inactiveObjectList.back();
				inactiveObjectList.pop_back();
			}
		}

		//for(TObjectListQueue::iterator it = inactiveObjectList.begin(); it!=inactiveObjectList.end(); ++it)
		//{
		//	if( (*it)->tag == compare )
		//	{
		//		a_obj = (*it);
		//		inactiveObjectList.pop_front();
		//	}
		//}
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

			for(unsigned short i = 0 ; i<inactiveObjectList.size();++i)
		{		
			if( inactiveObjectList[i]->genericTag == compare )
			{
				a_obj = inactiveObjectList[i];
				inactiveObjectList[i] = inactiveObjectList.back();
				inactiveObjectList.pop_back();
			}
		}

		//for(TObjectListQueue::iterator it = inactiveObjectList.begin(); it!=inactiveObjectList.end(); ++it)
		//{
		//	if( (*it)->genericTag == compare )//change to generic tag later
		//	{
		//		a_obj = (*it);
		//		inactiveObjectList.pop_front();
		//	}
		//}
	}else
	{
		std::cout<<"<FATAL ERROR> Cannot Find inactive gameobject to recycle"<<std::endl;
	}
	return a_obj;
}
void CObjectManager::PrintDebugAllActiveObjects()
{
	for(TObjectListVector::iterator it = objectList.begin(); it!=objectList.end(); ++it)
	{
		(*it)->PrintDebugInformation();
	}
}

void CObjectManager::PrintDebugAllInActiveObjects()
{
	for(TObjectListVector::iterator it = inactiveObjectList.begin(); it!=inactiveObjectList.end(); ++it)
	{
		(*it)->PrintDebugInformation();
	}
}

void CObjectManager::PrintDebugInformation()
{
	CEntity::PrintDebugInformation();
	std::cout<<"Active object List size"<<objectList.size()<<std::endl;
	std::cout<<"InActive object List size"<<inactiveObjectList.size()<<std::endl;
	SP->PrintDebugInformation();
}
