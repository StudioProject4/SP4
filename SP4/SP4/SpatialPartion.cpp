#include "SpatialPartion.h"


CSpatialPartion::CSpatialPartion(short gridWidth,short gridHeight,short cellSizeX,short cellSizeY)
		:gridWidth(gridWidth)
		,gridHeight(gridHeight)
		,cellSizeX(cellSizeX)
		,cellSizeY(cellSizeY)
		,numCellX(0)
		,numCellY(0)
{
	numCellX = ceil((float) gridWidth/cellSizeX);
	numCellY = ceil((float) gridHeight/cellSizeY);

	//allocate the cell list.
	cellList.resize(numCellX*numCellY);
}


CSpatialPartion::~CSpatialPartion(void)
{
}
//Get cell based on the position input
SCell* CSpatialPartion::GetCell(float posX,float posY)
{

}
//Get cell based on grid index
SCell* CSpatialPartion::GetCell(short indexX,short indexY)
{

}
//Remove object from a cell;
void CSpatialPartion::RemoveObject(ball* a_objToRemove)
{

}
//add object into a known cell;
void CSpatialPartion::AddObject(ball* a_obj,SCell* knownCell)
{

}
//add object into a calculated cell;
void CSpatialPartion::AddObject(ball* a_obj)
	{

}