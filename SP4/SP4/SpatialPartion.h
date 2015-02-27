#pragma once

#include "TestBallObject.h"

#include <vector>

class CBaseObject;

typedef std::vector<CBaseObject*> TObjectVector;

//class CCell
//{
//public:
//	TBallVector objectList;
//public:
//	CCell(){};
//	~CCell(){};
//};
//struct container2D
//{
//	short x;
//	short y;
//};


class Cell
{
public:
	TObjectVector objectList;
	bool deleteAllObjectUponDestruction;
public:
	Cell()
		:deleteAllObjectUponDestruction(false)
	{};
	~Cell()
	{
		if(deleteAllObjectUponDestruction)
		{
			CleanUp();
		}
	};

	bool CleanUp()
	{
		for(TObjectVector::iterator it = objectList.begin(); it!= objectList.end(); ++it)
		{
			//std::cout<< (*it)<<std::endl;
			if( (*it) != nullptr )
			{
				(*it)->Release();
				(*it) = nullptr;
			}
		}
		objectList.clear();
		return true;
	};
};


class CSpatialPartion
{
public:
	short cellSizeX;
	short cellSizeY;
	short gridWidth;
	short gridHeight;
	short numCellX;
	short numCellY;
	typedef std::vector<Cell> TCellVector;
	TCellVector cellList;
private:
	bool objectAllDeletedOutside;
public:
	CSpatialPartion(short gridWidth,short gridHeight,short cellSizeX,short cellSizeY);

	~CSpatialPartion(void);

	//Get cell based on the position input
	Cell* GetCell(float posX,float posY);

	//Get cell based on grid index
	Cell* GetCell(int indexX,int indexY);

	////Calculate cell index
	//container2D& GetCellIndex(Cell* a_cell);

	//Remove object from a cell;
	void RemoveObject(CBaseObject* a_obj);

	//add object from a known cell;
	void AddObject(CBaseObject* a_obj,Cell* knownCell);

	//add object into a calculated cell;
	void AddObject(CBaseObject* a_obj);

	void Update();
	//void UpdateCell();
	void UpdateObjectOwnerCell(CBaseObject* a_obj);

	void UpdateObjects();
	void RenderObjects();

	void NotifyAllObjectsAlreadyDeletedOutside()
	{
		objectAllDeletedOutside = true;
	}
	//print information
	void PrintDebugInformation();
};

