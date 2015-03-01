#pragma once

#include "TestBallObject.h"

#include <vector>

#include "CodeDefination.h"

class CBaseObject;

typedef std::vector<CBaseObject*> TObjectVector;

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
	void PrintDebugInformation()
	{
		for(TObjectVector::iterator it = objectList.begin(); it!= objectList.end(); ++it)
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

#ifdef SP_V1
	//Remove object from a cell;
	void RemoveObject(CBaseObject* a_obj);

	//add object from a known cell;
	void AddObject(CBaseObject* a_obj,Cell* knownCell);

	//add object into a calculated cell;
	void AddObject(CBaseObject* a_obj);
#endif

	//void UpdateCell();
	void UpdateObjectOwnerCell(CBaseObject* a_obj);

	//can ignore these and call from outside
	void UpdateObjects();
	void RenderObjects();
	///////////////////////////////////////

	void NotifyAllObjectsAlreadyDeletedOutside()
	{
		objectAllDeletedOutside = true;
	}

#ifdef SP_V2
	void UpdateObjectTopLeftAndBottomRightCell(CBaseObject* a_obj);
	void UpdateObjectMultipleCells(CBaseObject* a_obj);
	std::vector<Cell*> GetObjectMultipleCells(CBaseObject* a_obj);
	void AddObjectNeo(CBaseObject* a_obj,Cell* theCell,bool duplicateCheck = true);
	void AddObjectNeo(CBaseObject* a_obj);
	void RemoveObjectNeo(CBaseObject* a_obj,Cell* theCell);
#endif

	//rendering for debug
	void RenderGrid();
	void RenderSquare(float posX,float posY, float sizeX,float sizeY,bool drawBoundery = true);
	//print information
	void PrintDebugInformation();
};

