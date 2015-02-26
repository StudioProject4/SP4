#include "SpatialPartion.h"
#include "BaseObject.h"
#include <iostream>
using namespace std;
#include <GL\glut.h>


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

Cell* CSpatialPartion::GetCell(float posX,float posY)
{
	//short cellx = ((short)(posX/this->cellSizeX));
	//short celly = ((short)(posY/this->cellSizeY));
	return GetCell( ((short)(posX/this->cellSizeX)) , ((short)(posY/this->cellSizeY)) );

}

//Get cell based on grid index

Cell* CSpatialPartion::GetCell(short indexX,short indexY)
{

	// boundary check
	if(indexX < 0) indexX = 0;
	if(indexY < 0) indexY = 0;
	if(indexX > numCellX) indexX = numCellX -1;
	if(indexY > numCellY) indexY = numCellY -1;

	return &cellList[ (indexY*numCellX) + indexX ];

}

//Remove object from a cell;

void CSpatialPartion::RemoveObject(CBaseObject* a_obj)
{
	unsigned short indexoftheobject = a_obj->cellvectorindex;//paraphrasing
	TObjectVector& cellofobject = a_obj->ownerCell->objectList;//store an address of the objectlist to shorten later calls.
	//if things fails,use this.
	//cellofobject.erase(cellofobject.begin()+indexoftheobject);

	//using swapping method to delete the obj from the objectlist;
	cellofobject[indexoftheobject] = cellofobject.back();//swaps the last element to replace the object to be remove
	cellofobject.pop_back();//destory the last element container,since it has been copied over.
	if(indexoftheobject < cellofobject.size())//since the size has changed,check if the index is still valid.This check is needed if the object is the last element which the size becomes 0.
	{
		//correct the swapped element to be the index of the object being swapped out.
		cellofobject[indexoftheobject]->cellvectorindex = a_obj->cellvectorindex;
	}
	
	////clean up the object
	//a_obj->ownerCell = nullptr;
	//a_obj->cellvectorindex = - 1;


	//vector<ball*>& cellballs= a_obj->ownerCell->objectList;
	//cellballs[a_obj->cellvectorindex] = cellballs.back();
	//cellballs.pop_back();
	//cout<<"removing obj vector index "<<a_obj->cellvectorindex<<endl;
	//cout<<"cellballs.size() "<<a_obj->ownerCell->objectList.size()<<endl;
	//if(a_obj->cellvectorindex < cellballs.size())
	//{
	//	cout<<"Swapping index: "<<cellballs[a_obj->cellvectorindex]->cellvectorindex<<"With "<< a_obj->cellvectorindex<<endl;
	//	cellballs[a_obj->cellvectorindex]->cellvectorindex = a_obj->cellvectorindex;
	//}else
	//{
	//	cout<< "invalid cell vector index "<<endl;
	//}
	//cout<< "passed through "<<endl;
	//a_obj->cellvectorindex = -1;
	//a_obj->ownerCell = nullptr;
}

//add object into a known cell;

void CSpatialPartion::AddObject(CBaseObject* a_obj,Cell* knownCell)
{
	knownCell->objectList.push_back(a_obj);
	a_obj->ownerCell = knownCell;
	a_obj->cellvectorindex = knownCell->objectList.size()-1;
}

//add object into a calculated cell;

void CSpatialPartion::AddObject(CBaseObject* a_obj)
{
	Cell* a_cell = GetCell(a_obj->pos.x,a_obj->pos.y);
	a_cell->objectList.push_back(a_obj);
	a_obj->ownerCell = a_cell;
	a_obj->cellvectorindex = a_cell->objectList.size()-1;
}

void CSpatialPartion::Update()
{
	//for(TCellVector::iterator it = cellList.begin(); it!= cellList.end();++it)
	//{
	//	if(!(*it).objectList.empty())//if the cell objectlist is not empty,meaning got object inside
	//	{
	//		for(TBallVector::iterator it2 = (*it).objectList.begin(); it2 !=(*it).objectList.end(); ++it2)
	//		{
	//			UpdateObjectCell( (*it2) );
	//		}
	//	}
	//}
}

void CSpatialPartion::UpdateObjects()
{
	for(TCellVector::iterator it = cellList.begin(); it!= cellList.end();++it)
	{
		if(!(*it).objectList.empty())//if the cell objectlist is not empty,meaning got object inside
		{
			for(TObjectVector::iterator it2 = (*it).objectList.begin(); it2 !=(*it).objectList.end(); ++it2)
			{
				(*it2)->Update();
			}
		}
	}
}

void CSpatialPartion::RenderObjects()
{
	for(TCellVector::iterator it = cellList.begin(); it!= cellList.end();++it)
	{
		if(!(*it).objectList.empty())//if the cell objectlist is not empty,meaning got object inside
		{
			for(TObjectVector::iterator it2 = (*it).objectList.begin(); it2 !=(*it).objectList.end(); ++it2)
			{
				(*it2)->Render();
			}
		}
	}
}

void CSpatialPartion::UpdateObjectOwnerCell(CBaseObject* a_obj)
{
	Cell* a_cell = GetCell(a_obj->pos.x,a_obj->pos.y);
	if(a_cell != a_obj->ownerCell)
	{
		RemoveObject(a_obj);
		AddObject(a_obj,a_cell);
	}
}

void CSpatialPartion::PrintDebugInformation()
{
	/*
	short cellSizeX;
	short cellSizeY;
	short gridWidth;
	short gridHeight;
	short numCellX;
	short numCellY;
	*/
	cout<<endl;
	cout<< "Cell List Size: "<<cellList.size()<<endl;
	cout<< "Cell Size X: "<<cellSizeX<<endl;
	cout<< "Cell Size Y: "<<cellSizeY<<endl;
	cout<< "Grid Width: "<<gridWidth<<endl;
	cout<< "Grid Height: "<<gridHeight<<endl;
	cout<< "Number of cell X: "<<numCellX<<endl;
	cout<< "Number of cell Y: "<<numCellY<<endl;

	for(unsigned short i =0 ; i<cellList.size();++i)
	{
		if(!cellList[i].objectList.empty())
		{
			cout<<"Cell index: "<<i<<" is size of"<< cellList[i].objectList.size() <<endl;
			//short indexX = 0;
			//short indexY = 0;

			//for(unsigned short j =0 ; j<cellList[i].objectList.size();++j)
			//{

			//}
		}
	}
}