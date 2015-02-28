#include "ObjectManager.h"
#include "Map.h"
#include "SpatialPartion.h"
#include "WindowManager.h"
#include "Sprite.h"
#include "TestBallObject.h"
#include "GameStateManager.h"

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
#ifdef SP_V1
	
#endif
#ifdef SP_V2

#endif
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
void CObjectManager::CheckCollisionCharacterWithObject(CBaseObject* a_obj, TObjectListVector& listOfObjectToCheck,int startingIndex)
{

		CBaseObject* otherObject = nullptr;
		Vector3 OtherSize;
	
		for(int i = startingIndex; i< listOfObjectToCheck.size();++i)
		{	
			otherObject = listOfObjectToCheck[i];//paraphrasing

			if(otherObject == a_obj)//avoid self check
				continue;

			if(a_obj->genericTag == "Character" || otherObject->genericTag == "Character")
			{
					OtherSize = otherObject->phys.size;
					//std::cout<<"Checking collision "<<a_obj->name <<" with "<< otherObject->name<<"!!!"<<std::endl;
					if(a_obj->phys.TestCol(otherObject->pos,OtherSize))
					{
						//std::cout<<"COLLISION RESPONE ACTIVATED "<<a_obj->name <<"with"<< otherObject->name<<std::endl;
						a_obj->OnCollision(otherObject);
					}
			}
		}
}
void CObjectManager::CheckObjectCollision(CBaseObject* a_obj, TObjectListVector& listOfObjectToCheck,int startingIndex)
{
	CBaseObject* otherObject = nullptr;
	Vector3 OtherSize;
	
	for(int i = startingIndex; i< listOfObjectToCheck.size();++i)
	{	

		otherObject = listOfObjectToCheck[i];//paraphrasing
		if(otherObject!=a_obj)
		{
			OtherSize = otherObject->phys.size;
			//std::cout<<"checking "<<a_obj->name <<"with"<< otherObject->name<<std::endl;
			if(a_obj->phys.TestCol(otherObject->pos,OtherSize))
			{
				//std::cout<<"collided "<<a_obj->name <<"with"<< otherObject->name<<std::endl;
				a_obj->OnCollision(otherObject);
			}
		}
	}
}

void CObjectManager::UpdateCollision()
{
#ifdef SP_V1
	short x = 0;//x index of a cell
	short y = 0;//y index of a cell
	CBaseObject* a_obj = nullptr;
	for(int i = 0 ; i < SP->cellList.size(); ++i )//loop through all cells
	{
		if(SP->cellList[i].objectList.empty())//skip empty cell
			continue;


		Cell& a_cell = SP->cellList[i];

		//get the index of the current cell
		x = i % SP->numCellX;
		y = i / SP->numCellX;

		for(int j = 0 ; j< a_cell.objectList.size();++j)//loop through all object inside objectlist of non empty cell
		{
			a_obj = a_cell.objectList[j];
			//std::cout<<"Checking object "<<a_obj->name<<" at cell "<<x<<" , "<<y <<std::endl;
			CheckCollisionCharacterWithObject(a_obj,SP->GetCell( x , y )->objectList, 0);//checking a object with a list of object,skipping self check.The List of object is only within it own grid at there

			if(y < SP->numCellY-1)
			{
				CheckCollisionCharacterWithObject(a_obj,SP->GetCell( x , y+1)->objectList,0);//check top cell
			}

			if(x >0)//nested left cell check
			{
				CheckCollisionCharacterWithObject(a_obj,SP->GetCell( x-1 , y)->objectList,0);//check left cell

				if(y < SP->numCellY-1)
				{

					CheckCollisionCharacterWithObject(a_obj,SP->GetCell( x-1 , y+1)->objectList,0);//check top left cell
				}
				if(y>0)
				{
					CheckCollisionCharacterWithObject(a_obj,SP->GetCell( x-1 , y-1)->objectList,0);//bottom left cell
				}
			}

		}

	}
#endif

#ifdef SP_V2
	if(CGameStateManager::GetInstance()->currentState == CGameStateManager::STATE_MYAPPLICATION)
	{
		this->UpdateGridCheckCall();
		
	}
	if(CGameStateManager::GetInstance()->currentState == CGameStateManager::STATE_MENU)
	{
		this->UpdateGridTestBallCheckCall();
	}
#endif

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

#ifdef SP_V1
			SP->UpdateObjectOwnerCell(objectList[it]);
#endif

#ifdef SP_V2
			objectList[it]->UpdateObjectTopLeftAndBottomRightPoint(false);
			SP->UpdateObjectTopLeftAndBottomRightCell(objectList[it]);
			SP->UpdateObjectStretchedCells(objectList[it]);
#endif	

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
bool CObjectManager::ChangeSpatialParition(CSpatialPartion* newSP)
{
	if(this->SP != nullptr)
	{
		delete SP;
	}
	SP = newSP;
	return true;
}
bool CObjectManager::Init()
{
	name = "objectmanager";
	manufacturer = CManufactureManager::GetInstance();
	SP = new CSpatialPartion(CWindowManager::GetInstance()->GetOriginalWindowWidth(),CWindowManager::GetInstance()->GetOriginalWindowHeight(),TILE_SIZE,TILE_SIZE);
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
#ifdef SP_V2
void CObjectManager::UpdateGridCheckCall()
{
	//short currx = 0;//x index of a cell
	//short curry = 0;//y index of a cell
	CBaseObject* a_obj = nullptr;

	for(int i = 0 ; i < SP->cellList.size(); ++i )//loop through all cells
	{
		if(SP->cellList[i].objectListNeo.empty())//skip empty cell
			continue;
		
		
		Cell& a_cell = SP->cellList[i];

		////get the index of the current cell
		//currx = i % SP->numCellX;
		//curry = i / SP->numCellX;
		//std::cout<<"currx "<<currx<<" curry" <<curry<<std::endl;
		for(int j = 0 ; j< a_cell.objectListNeo.size();++j)//loop through all object inside objectlist of non empty cell
		{
			
			a_obj = a_cell.objectListNeo[j];

			
			//int lasttimecalled = a_ball->timecalled;

			//////Grid information
			/*
			grid index X goes from 0 to 'n' number from left to right
			grid index Y goes from 0 to 'n' number from top to bottom
			*/
			///////
			//if((a_obj->TopLeftCellIndex.x >= 0 &&  a_obj->TopLeftCellIndex.y >= 0))
			//{
			//	std::cout<<"top left OK"<<std::endl;
			//}else
			//{
			//	std::cout<<"top left NOO"<<std::endl;
			//}

			//if( ( a_obj->BottomRightCellIndex.x>=0 && a_obj->BottomRightCellIndex.x < SP->numCellX) &&( a_obj->BottomRightCellIndex.y >= 0 && a_obj->BottomRightCellIndex.y < SP->numCellY))
			//{
			//	std::cout<<"bottom right OK"<<std::endl;
			//}else
			//{
			//	std::cout<<"bottom right NOO"<<std::endl;
			//}

			if( (a_obj->TopLeftCellIndex.x >= 0 &&  a_obj->TopLeftCellIndex.y >= 0) && (a_obj->BottomRightCellIndex.x < SP->numCellX && a_obj->BottomRightCellIndex.y < SP->numCellY) )//if within whole Spatial partition
			{	

				for(int ownY = a_obj->TopLeftCellIndex.y; ownY <=a_obj->BottomRightCellIndex.y;++ownY)//loop through all own occupied cells
				{
					for(int ownX = a_obj->TopLeftCellIndex.x; ownX <=a_obj->BottomRightCellIndex.x;++ownX)
					{
						//a_ball->UpdateCollision(SP->GetCell(ownX,ownY)->objectListNeo,0);
						CheckCollisionCharacterWithObject(a_obj,SP->GetCell(ownX,ownY)->objectListNeo,0);
					}
				}
				//int nexttimecalled = a_ball->timecalled;
				//std::cout<<"time called diff"<<nexttimecalled-lasttimecalled<<std::endl;
				////call neighbouring cells.
				if( a_obj->TopLeftCellIndex.y-1 >= 0)//nested celling cells check
				{
					for(int topX = a_obj->TopLeftCellIndex.x; topX<=a_obj->BottomRightCellIndex.x;++topX )//loop through all top celling cells
					{	
						//std::cout<<"testing top cells"<<std::endl;
						//a_ball->UpdateCollision( SP->GetCell(topX,((int)a_obj->TopLeftCellIndex.y-1))->objectListNeo,0);
						CheckCollisionCharacterWithObject(a_obj,SP->GetCell(topX,((int)a_obj->TopLeftCellIndex.y-1))->objectListNeo,0);
					}

					if(a_obj->TopLeftCellIndex.x-1 >= 0 )//celling,top left cell check
					{
						//std::cout<<"testing top left cells"<<std::endl;
						//a_ball->UpdateCollision( SP->GetCell(((int)a_obj->TopLeftCellIndex.x-1),((int)a_obj->TopLeftCellIndex.y-1))->objectListNeo,0);
						CheckCollisionCharacterWithObject(a_obj,SP->GetCell(((int)a_obj->TopLeftCellIndex.x-1),((int)a_obj->TopLeftCellIndex.y-1))->objectListNeo,0);
					}
				}

				if(a_obj->TopLeftCellIndex.x-1 >= 0 )///nested left border cells check
				{
					for(int leftY = a_obj->TopLeftCellIndex.y; leftY <= a_obj->BottomRightCellIndex.y; ++leftY)///loop through all left border cells
					{
						//std::cout<<"testing left cells"<<std::endl;
						//a_ball->UpdateCollision( SP->GetCell(((int)a_obj->TopLeftCellIndex.x-1),leftY)->objectListNeo,0);
						CheckCollisionCharacterWithObject(a_obj,SP->GetCell(((int)a_obj->TopLeftCellIndex.x-1),leftY)->objectListNeo,0);
					
					}

					if(a_obj->BottomRightCellIndex.y+1 < SP->numCellY )//check bottom left cell
					{
						//std::cout<<"testing bottom left cells"<<std::endl;
						//a_ball->UpdateCollision(SP->GetCell(((int)a_obj->TopLeftCellIndex.x-1),((int)a_obj->BottomRightCellIndex.y+1))->objectListNeo,0);
						CheckCollisionCharacterWithObject(a_obj,SP->GetCell(((int)a_obj->TopLeftCellIndex.x-1),((int)a_obj->BottomRightCellIndex.y+1))->objectListNeo,0);
					}

				}

			}
			else
			{
				//std::cout<<"out of bound"<<std::endl;
			}
		}
	}
}
void CObjectManager::UpdateGridTestBallCheckCall()
{
	//short x = 0;//x index of a cell
	//short y = 0;//y index of a cell
	CBaseObject* a_obj = nullptr;
	CTestBallObject* a_ball = nullptr;
	for(int i = 0 ; i < SP->cellList.size(); ++i )//loop through all cells
	{
		if(SP->cellList[i].objectListNeo.empty())//skip empty cell
			continue;


		Cell& a_cell = SP->cellList[i];

		////get the index of the current cell
		//x = i % SP->numCellX;
		//y = i / SP->numCellX;

		for(int j = 0 ; j< a_cell.objectListNeo.size();++j)//loop through all object inside objectlist of non empty cell
		{
			
			a_obj = a_cell.objectListNeo[j];

			a_ball = dynamic_cast<CTestBallObject*>(a_obj);
			//int lasttimecalled = a_ball->timecalled;

			//////Grid information
			/*
			grid index X goes from 0 to 'n' number from left to right
			grid index Y goes from 0 to 'n' number from top to bottom
			*/
			///////
			//if((a_obj->TopLeftCellIndex.x >= 0 &&  a_obj->TopLeftCellIndex.y >= 0))
			//{
			//	std::cout<<"top left OK"<<std::endl;
			//}else
			//{
			//	std::cout<<"top left NOO"<<std::endl;
			//}

			//if( ( a_obj->BottomRightCellIndex.x>=0 && a_obj->BottomRightCellIndex.x < SP->numCellX) &&( a_obj->BottomRightCellIndex.y >= 0 && a_obj->BottomRightCellIndex.y < SP->numCellY))
			//{
			//	std::cout<<"bottom right OK"<<std::endl;
			//}else
			//{
			//	std::cout<<"bottom right NOO"<<std::endl;
			//}

			if( (a_obj->TopLeftCellIndex.x >= 0 &&  a_obj->TopLeftCellIndex.y >= 0) && (a_obj->BottomRightCellIndex.x < SP->numCellX && a_obj->BottomRightCellIndex.y < SP->numCellY) )//if within whole Spatial partition
			{	

				for(int ownY = a_obj->TopLeftCellIndex.y; ownY <=a_obj->BottomRightCellIndex.y;++ownY)//loop through all own occupied cells
				{
					for(int ownX = a_obj->TopLeftCellIndex.x; ownX <=a_obj->BottomRightCellIndex.x;++ownX)
					{
						a_ball->UpdateCollision(SP->GetCell(ownX,ownY)->objectListNeo,0);
					}
				}
				//int nexttimecalled = a_ball->timecalled;
				//std::cout<<"time called diff"<<nexttimecalled-lasttimecalled<<std::endl;
				////call neighbouring cells.
				if( a_obj->TopLeftCellIndex.y-1 >= 0)//nested celling cells check
				{
					for(int topX = a_obj->TopLeftCellIndex.x; topX<=a_obj->BottomRightCellIndex.x;++topX )//loop through all top celling cells
					{	
						//std::cout<<"testing top cells"<<std::endl;
						a_ball->UpdateCollision( SP->GetCell(topX,((int)a_obj->TopLeftCellIndex.y-1))->objectListNeo,0);
					}

					if(a_obj->TopLeftCellIndex.x-1 >= 0 )//celling,top left cell check
					{
						//std::cout<<"testing top left cells"<<std::endl;
						a_ball->UpdateCollision( SP->GetCell(((int)a_obj->TopLeftCellIndex.x-1),((int)a_obj->TopLeftCellIndex.y-1))->objectListNeo,0);
					}
				}

				if(a_obj->TopLeftCellIndex.x-1 >= 0 )///nested left border cells check
				{
					for(int leftY = a_obj->TopLeftCellIndex.y; leftY <= a_obj->BottomRightCellIndex.y; ++leftY)///loop through all left border cells
					{
						//std::cout<<"testing left cells"<<std::endl;
						a_ball->UpdateCollision( SP->GetCell(((int)a_obj->TopLeftCellIndex.x-1),leftY)->objectListNeo,0);
					}

					if(a_obj->BottomRightCellIndex.y+1 < SP->numCellY )//check bottom left cell
					{
						//std::cout<<"testing bottom left cells"<<std::endl;
						a_ball->UpdateCollision(SP->GetCell(((int)a_obj->TopLeftCellIndex.x-1),((int)a_obj->BottomRightCellIndex.y+1))->objectListNeo,0);
					}

				}

			}
			else
			{
				//std::cout<<"out of bound"<<std::endl;
			}
		}
	}
}
#endif
