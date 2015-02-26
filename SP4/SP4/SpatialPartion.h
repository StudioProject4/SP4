#pragma once

#include "TestBallObject.h"

#include <vector>

typedef std::vector<ball*> TBallVector;

struct SCell
{
	TBallVector objectList;
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
	typedef std::vector<SCell> TCellVector;
	TCellVector cellList;

public:
	CSpatialPartion(short gridWidth,short gridHeight,short cellSizeX,short cellSizeY);

	~CSpatialPartion(void);

	//Get cell based on the position input
	SCell* GetCell(float posX,float posY);

	//Get cell based on grid index
	SCell* GetCell(short indexX,short indexY);

	//Remove object from a cell;
	void RemoveObject(ball* a_objToRemove);

	//add object into a known cell;
	void AddObject(ball* a_obj,SCell* knownCell);

	//add object into a calculated cell;
	void AddObject(ball* a_obj);
};

