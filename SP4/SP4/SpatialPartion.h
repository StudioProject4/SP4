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
//#define SP_V2

//#define SP_V1

class Cell
{
public:
	TObjectVector objectList;
	TObjectVector objectListNeo;//for testing
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
	void PrintDebugInformation()
	{
		for(TObjectVector::iterator it = objectListNeo.begin(); it!= objectListNeo.end(); ++it)
		{
			(*it)->PrintDebugInformation();
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

struct SIndex2D
{
	short x;
	short y;
	SIndex2D()
		:x(-1)
		,y(-1)
	{};

	friend std::ostream& operator<<( std::ostream& os, SIndex2D& rhs)
	{
		os << "[ " << rhs.x << ", " << rhs.y << " ]";
		return os;
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

	//render the grid for debug
	void RenderGrid();
	void RenderSquare(float posX,float posY, float sizeX,float sizeY,bool drawBoundery = true);

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

	/////////////////////////////////////////
	//new function for big object in many grid
	void UpdateObjectTopLeftAndBottomRightCell(CBaseObject* a_obj);
	void UpdateObjectStretchedCells(CBaseObject* a_obj);
	std::vector<Cell*> GetObjectStretchedCells(CBaseObject* a_obj);
	void AddObjectNeo(CBaseObject* a_obj,Cell* theCell,bool duplicateCheck = true);
	void RemoveObjectNeo(CBaseObject* a_obj,Cell* theCell);
	void UpdateOwnerCellNeo(CBaseObject* a_obj,Cell* theCell);
	//////////////////////////////////////////
};

