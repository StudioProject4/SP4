#include "ObjectManager.h"
#include "MusicSystem\MusicSystem.h"
#include "Map.h"
#include "SpatialPartion.h"
#include "WindowManager.h"
#include "Sprite.h"
#include "TestBallObject.h"
#include "GameStateManager.h"
#include "Character.h"
#include "LeverDoor.h"
#include "Door.h"
#include "MalayMob.h"
#include "ChineseMob.h"

//CObjectManager* CObjectManager::instance = 0;

CObjectManager::CObjectManager(void)
	:SP(0)
	,numOfUniqueId(-1)
	,frame(false)
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
	SP->AddObject(a_obj);
#endif
#ifdef SP_V2
	SP->AddObjectNeo(a_obj);
#endif
	if(a_obj->id==0)
	{
		++numOfUniqueId;
		a_obj->id = numOfUniqueId;
	}
	else if(a_obj->id>numOfUniqueId)
	{
		numOfUniqueId=a_obj->id;
	}
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
	
		for(unsigned int i = startingIndex; i< listOfObjectToCheck.size();++i)
		{	
			otherObject = listOfObjectToCheck[i];//paraphrasing

			if(otherObject == a_obj)//avoid self check
				continue;

			string gen1=a_obj->genericTag;
			string gen2=otherObject->genericTag;
			string tag1=a_obj->tag;
			string tag2=otherObject->tag;
			if(gen1 == "Character" || gen2 == "Character")
			{
				if((charControl==1&&(tag1=="ChineseMale"||tag2=="ChineseMale"))
					||(charControl==2&&(tag1=="MalayFemale"||tag2=="MalayFemale"))
					||charControl==3)
				{
					OtherSize = otherObject->phys.size;
					//std::cout<<"Checking collision "<<a_obj->name <<" with "<< otherObject->name<<"!!!"<<std::endl;
					if(a_obj->phys.TestCol(otherObject->pos,OtherSize))
					{
						//++a_obj->numberOfTimeCollided;
						//++otherObject->numberOfTimeCollided;

						//std::cout<<"COLLISION RESPONE ACTIVATED "<<a_obj->name <<"with"<< otherObject->name<<std::endl;
						if(gen1=="Character")
							if(!otherObject->OnCollision(a_obj,frame))
								break;
						else 
							if(!a_obj->OnCollision(a_obj,frame))
								break;

						
					}/*else
					{
						a_obj->numberOfTimeCollided = 0;
						otherObject->numberOfTimeCollided = 0;
					}*/
				}
			}
		}
}
void CObjectManager::CheckObjectCollision(CBaseObject* a_obj, TObjectListVector& listOfObjectToCheck,int startingIndex)
{
	CBaseObject* otherObject = nullptr;
	Vector3 OtherSize;
	
	for(unsigned int i = startingIndex; i< listOfObjectToCheck.size();++i)
	{	

		otherObject = listOfObjectToCheck[i];//paraphrasing
		if(otherObject!=a_obj)
		{
			OtherSize = otherObject->phys.size;
			//std::cout<<"checking "<<a_obj->name <<"with"<< otherObject->name<<std::endl;
			if(a_obj->phys.TestCol(otherObject->pos,OtherSize))
			{
				//std::cout<<"collided "<<a_obj->name <<"with"<< otherObject->name<<std::endl;
				a_obj->OnCollision(otherObject,frame);
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
	//if(CGameStateManager::GetInstance()->currentState == CGameStateManager::STATE_MENU)
	//{
	//	this->UpdateGridTestBallCheckCall();
	//}
#endif
	frame=!frame;
}

bool CObjectManager::LoadingSetup()
{
	for(TObjectListVector::iterator it=objectList.begin();it!=objectList.end();)
	{
		if((*it)->genericTag!="Character")
		{
			(*it)->active=false;
			
			inactiveObjectList.push_back(*it);
			it=objectList.erase(it);
			continue;
		}
	++it;
	}
	SP->CleanUpAllObjectExceptCharacter();
	return true;
}

bool CObjectManager::Update()
{
	return Update(3);
}

bool CObjectManager::Update(int multiplayerMode)
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
	this->charControl=multiplayerMode;
	UpdateCollision();

	for(unsigned short it = 0; it < objectList.size(); ++it)
	{
		if( objectList[it]->active == true)
		{
			if(objectList[it]->genericTag == "Enemy")
			{
				if(objectList[it]->tag == "MalayMob")
				{
					CMalayMob * temp = (CMalayMob*)objectList[it];
					temp->charControl = charControl;
				}
				else if(objectList[it]->tag == "ChineseMob")
				{
					CChineseMob * temp = (CChineseMob*)objectList[it];
					temp->charControl = charControl;
				}
			}
			objectList[it]->Update();
			if(it<objectList.size())
			{
#ifdef SP_V1
			SP->UpdateObjectOwnerCell(objectList[it]);
#endif
#ifdef SP_V2
			objectList[it]->UpdateObjectTopLeftAndBottomRightPoint(false);
			SP->UpdateObjectTopLeftAndBottomRightCell(objectList[it]);
			SP->UpdateObjectMultipleCells(objectList[it]);
#endif	
			}

			//(*it)->Render();
			}else
		{
			inactiveObjectList.push_back(objectList[it]);
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
	SP = new CSpatialPartion(CWindowManager::GetInstance()->GetOriginalWindowWidth(),CWindowManager::GetInstance()->GetOriginalWindowHeight(),TILE_SIZE*5,TILE_SIZE*5);
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
	//const char* compare = objectName.c_str();

	for(TObjectListVector::iterator it = objectList.begin(); it!=objectList.end(); ++it)
	{
		if( (*it)->name == objectName )
		{
			return (*it);
		}
	}
	return 0;
}

CBaseObject* CObjectManager::FindObjectWithTag(std::string objectTag)
{
	//const char* compare = objectTag.c_str();

	for(TObjectListVector::iterator it = objectList.begin(); it!=objectList.end(); ++it)
	{
		if( (*it)->tag == objectTag )
		{
			return (*it);
		}
	}
	return 0;
}

CBaseObject* CObjectManager::FindObjectWithGenericTag(std::string objectTag)
{
	//const char* compare = objectTag.c_str();

	for(TObjectListVector::iterator it = objectList.begin(); it!=objectList.end(); ++it)
	{
		if( (*it)->genericTag == objectTag )
		{
			return (*it);
		}
	}
	return 0;
}


CObjectManager::TObjectListVector CObjectManager::FindObjectsWithTag(std::string objectTag)
{
	//const char* compare = objectTag.c_str();
	TObjectListVector resultlist;

	for(TObjectListVector::iterator it = objectList.begin(); it!=objectList.end(); ++it)
	{
		if( (*it)->genericTag == objectTag )
		{
			resultlist.push_back((*it));
		}
	}
	return resultlist;
}

CObjectManager::TObjectListVector CObjectManager::FindObjectsWithGenericTag(std::string objectTag)
{
	//const char* compare = objectTag.c_str();
	TObjectListVector resultlist;

	for(TObjectListVector::iterator it = objectList.begin(); it!=objectList.end(); ++it)
	{
		if( (*it)->genericTag == objectTag )
		{
			resultlist.push_back((*it));
		}
	}
	return resultlist;
}

//CBaseObject* CObjectManager::FetchObject()
//{
//	CBaseObject* a_obj = NULL;
//
//	if(!inactiveObjectList.empty())
//	{
//		a_obj =  inactiveObjectList.front();
//		//inactiveObjectList.erase(inactiveObjectList.begin());//pop front
//		inactiveObjectList.front() = inactiveObjectList.back();//swap to the front and pop back.
//		inactiveObjectList.pop_back();
//		AddToActiveList(a_obj);
//	}else
//	{
//		std::cout<<"<FATAL ERROR> Cannot Find inactive gameobject to recycle"<<std::endl;
//	}
//	return a_obj;
//}

CBaseObject* CObjectManager::FetchObjectWithName(std::string objectName)
{
	CBaseObject* a_obj = NULL;

	if(!inactiveObjectList.empty())
	{
		//const char* compare = objectName.c_str();

		for(unsigned short i = 0 ; i<inactiveObjectList.size();++i)
		{		
			if( inactiveObjectList[i]->name == objectName )
			{
				a_obj = inactiveObjectList[i];
				inactiveObjectList[i] = inactiveObjectList.back();
				inactiveObjectList.pop_back();
				AddToActiveList(a_obj);
				break;
			}
		}

	}else
	{
	}
	return a_obj;
}

CBaseObject* CObjectManager::FetchObjectWithTag(std::string objectTag)
{
	//std::cout<<"trying to recycle something"<<std::endl;
	CBaseObject* a_obj = NULL;
	if(!inactiveObjectList.empty())
	{
		//const char* compare = objectTag.c_str();
		
		for(unsigned short i = 0 ; i<inactiveObjectList.size();++i)
		{		//std::cout<<"loopinh"<<std::endl;

			if( inactiveObjectList[i]->tag == objectTag )
			{
				//std::cout<<"found something"<<std::endl;
				a_obj = inactiveObjectList[i];
				inactiveObjectList[i] = inactiveObjectList.back();
				inactiveObjectList.pop_back();
				AddToActiveList(a_obj);
				
				break;
			}
		}
	}else
	{
	}
	return a_obj;
}

CBaseObject* CObjectManager::FetchObjectWithGenericTag(std::string objectTag)
{
	CBaseObject* a_obj = NULL;

	if(!inactiveObjectList.empty())
	{
		//const char* compare = objectTag.c_str();

			for(unsigned short i = 0 ; i<inactiveObjectList.size();++i)
		{		
			if( inactiveObjectList[i]->genericTag == objectTag )
			{
				a_obj = inactiveObjectList[i];
				inactiveObjectList[i] = inactiveObjectList.back();
				inactiveObjectList.pop_back();
				AddToActiveList(a_obj);
				//std::cout<<"recycling something"<<std::endl;
				break;
			}
		}

	}else
	{
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
#ifdef NETWORK_CODE
void CObjectManager::WriteAllObjects(RakNet::BitStream &bs)
{
	bs.Write(objectList.size());
	for(TObjectListVector::iterator it=objectList.begin();it!=objectList.end();++it)
	{
		CBaseObject* temp=*it;
		//basic info
		bs.Write(temp->genericTag);
		bs.Write(temp->tag);
		bs.Write(temp->id);
		bs.Write(temp->pos.x);
		bs.Write(temp->pos.y);
		bs.Write(temp->pos.z);

		//more specific info
		if(temp->genericTag=="Character")
		{
			CCharacter* temp2=(CCharacter*)temp;
			bs.Write(temp2->hp.GetHealth());
		}
		else if(temp->genericTag=="PowerUp")
		{
		}
		else if(temp->tag=="CLeverDoor")
		{
			CLeverDoor* temp2=(CLeverDoor*)temp;
			bs.Write(temp2->curAngle);
			bs.Write(temp2->GetDoorID());
		}
		else if(temp->tag=="CDoor")
		{
			CDoor* temp2=(CDoor*)temp;
			vector<int> temp3=temp2->GetTriggerID();
		}
		else if(temp->genericTag=="Enemy")
		{

		}
		else if(temp->tag=="WC")
		{
			int i=0;
		}
	}
}
#endif
#ifdef SP_V2
void CObjectManager::UpdateGridCheckCall()
{
	//short currx = 0;//x index of a cell
	//short curry = 0;//y index of a cell
	CBaseObject* a_obj = nullptr;

	for(unsigned int i = 0 ; i < SP->cellList.size(); ++i )//loop through all cells
	{
		if(SP->cellList[i].objectList.empty())//skip empty cell
			continue;
		
		
		Cell& a_cell = SP->cellList[i];

		////get the index of the current cell
		//currx = i % SP->numCellX;
		//curry = i / SP->numCellX;
		//std::cout<<"currx "<<currx<<" curry" <<curry<<std::endl;
		for(unsigned int j = 0 ; j< a_cell.objectList.size();++j)//loop through all object inside objectlist of non empty cell
		{
			
			a_obj = a_cell.objectList[j];

			
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

				for(int ownY = (int)a_obj->TopLeftCellIndex.y; ownY <=(int)a_obj->BottomRightCellIndex.y;++ownY)//loop through all own occupied cells
				{
					for(int ownX = (int)a_obj->TopLeftCellIndex.x; ownX <=(int)a_obj->BottomRightCellIndex.x;++ownX)
					{
						//a_ball->UpdateCollision(SP->GetCell(ownX,ownY)->objectList,0);
						CheckCollisionCharacterWithObject(a_obj,SP->GetCell(ownX,ownY)->objectList,0);
					}
				}
				////call neighbouring cells.
				if( a_obj->TopLeftCellIndex.y-1 >= 0)//nested celling cells check
				{
					for(int topX = (int)a_obj->TopLeftCellIndex.x; topX<=(int)a_obj->BottomRightCellIndex.x;++topX )//loop through all top celling cells
					{	
						//a_ball->UpdateCollision( SP->GetCell(topX,((int)a_obj->TopLeftCellIndex.y-1))->objectList,0);
						CheckCollisionCharacterWithObject(a_obj,SP->GetCell(topX,((int)a_obj->TopLeftCellIndex.y-1))->objectList,0);
					}

					if(a_obj->TopLeftCellIndex.x-1 >= 0 )//celling,top left cell check
					{
						//std::cout<<"testing top left cells"<<std::endl;
						//a_ball->UpdateCollision( SP->GetCell(((int)a_obj->TopLeftCellIndex.x-1),((int)a_obj->TopLeftCellIndex.y-1))->objectList,0);
						CheckCollisionCharacterWithObject(a_obj,SP->GetCell(((int)a_obj->TopLeftCellIndex.x-1),((int)a_obj->TopLeftCellIndex.y-1))->objectList,0);
					}
				}

				if(a_obj->TopLeftCellIndex.x-1 >= 0 )///nested left border cells check
				{
					for(int leftY = (int)a_obj->TopLeftCellIndex.y; leftY <= (int)a_obj->BottomRightCellIndex.y; ++leftY)///loop through all left border cells
					{
						//std::cout<<"testing left cells"<<std::endl;
						//a_ball->UpdateCollision( SP->GetCell(((int)a_obj->TopLeftCellIndex.x-1),leftY)->objectList,0);
						CheckCollisionCharacterWithObject(a_obj,SP->GetCell(((int)a_obj->TopLeftCellIndex.x-1),leftY)->objectList,0);
					
					}

					if(a_obj->BottomRightCellIndex.y+1 < SP->numCellY )//check bottom left cell
					{
						//std::cout<<"testing bottom left cells"<<std::endl;
						//a_ball->UpdateCollision(SP->GetCell(((int)a_obj->TopLeftCellIndex.x-1),((int)a_obj->BottomRightCellIndex.y+1))->objectList,0);
						CheckCollisionCharacterWithObject(a_obj,SP->GetCell(((int)a_obj->TopLeftCellIndex.x-1),((int)a_obj->BottomRightCellIndex.y+1))->objectList,0);
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
	for(unsigned int i = 0 ; i < SP->cellList.size(); ++i )//loop through all cells
	{
		if(SP->cellList[i].objectList.empty())//skip empty cell
			continue;


		Cell& a_cell = SP->cellList[i];

		////get the index of the current cell
		//x = i % SP->numCellX;
		//y = i / SP->numCellX;

		for(unsigned int j = 0 ; j< a_cell.objectList.size();++j)//loop through all object inside objectlist of non empty cell
		{
			
			a_obj = a_cell.objectList[j];

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

				for(int ownY = (int)a_obj->TopLeftCellIndex.y; ownY <=(int)a_obj->BottomRightCellIndex.y;++ownY)//loop through all own occupied cells
				{
					for(int ownX = (int)a_obj->TopLeftCellIndex.x; ownX <=(int)a_obj->BottomRightCellIndex.x;++ownX)
					{
						a_ball->UpdateCollision(SP->GetCell(ownX,ownY)->objectList,0);
					}
				}
				//int nexttimecalled = a_ball->timecalled;
				//std::cout<<"time called diff"<<nexttimecalled-lasttimecalled<<std::endl;
				////call neighbouring cells.
				if( a_obj->TopLeftCellIndex.y-1 >= 0)//nested celling cells check
				{
					for(int topX = (int)a_obj->TopLeftCellIndex.x; topX<=(int)a_obj->BottomRightCellIndex.x;++topX )//loop through all top celling cells
					{	
						//std::cout<<"testing top cells"<<std::endl;
						a_ball->UpdateCollision( SP->GetCell(topX,((int)a_obj->TopLeftCellIndex.y-1))->objectList,0);
					}

					if(a_obj->TopLeftCellIndex.x-1 >= 0 )//celling,top left cell check
					{
						//std::cout<<"testing top left cells"<<std::endl;
						a_ball->UpdateCollision( SP->GetCell(((int)a_obj->TopLeftCellIndex.x-1),((int)a_obj->TopLeftCellIndex.y-1))->objectList,0);
					}
				}

				if(a_obj->TopLeftCellIndex.x-1 >= 0 )///nested left border cells check
				{
					for(int leftY = (int)a_obj->TopLeftCellIndex.y; leftY <= (int)a_obj->BottomRightCellIndex.y; ++leftY)///loop through all left border cells
					{
						//std::cout<<"testing left cells"<<std::endl;
						a_ball->UpdateCollision( SP->GetCell(((int)a_obj->TopLeftCellIndex.x-1),leftY)->objectList,0);
					}

					if(a_obj->BottomRightCellIndex.y+1 < SP->numCellY )//check bottom left cell
					{
						//std::cout<<"testing bottom left cells"<<std::endl;
						a_ball->UpdateCollision(SP->GetCell(((int)a_obj->TopLeftCellIndex.x-1),((int)a_obj->BottomRightCellIndex.y+1))->objectList,0);
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
