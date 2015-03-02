#include "BaseObject.h"
#include "SpatialPartion.h"
#include <iostream>
//using namespace std;
#include <GL\glut.h>
#include "Sprite.h"

static float myRoundFunc(float toRound)
{
  return std::ceil(toRound - 0.5);
}

CSpatialPartion::CSpatialPartion(short gridWidth,short gridHeight,short cellSizeX,short cellSizeY)
		:gridWidth(gridWidth)
		,gridHeight(gridHeight)
		,cellSizeX(cellSizeX)
		,cellSizeY(cellSizeY)
		,numCellX(0)
		,numCellY(0)
		,objectAllDeletedOutside(false)
{
	numCellX = ceil((float) gridWidth/cellSizeX);
	numCellY = ceil((float) gridHeight/cellSizeY);

	//allocate the cell list.
	cellList.resize(numCellX*numCellY);
}


CSpatialPartion::~CSpatialPartion(void)
{
	//std::cout<<objectAllDeletedOutside<<std::endl;
	if(objectAllDeletedOutside == false)
	{
		for(unsigned short i =0 ; i<cellList.size();++i)
		{
			cellList[i].deleteAllObjectUponDestruction = true;
		}
	}
}

//Get cell based on the position input

Cell* CSpatialPartion::GetCell(float posX,float posY)
{
	//short cellx = ((short)(posX/this->cellSizeX));
	//short celly = ((short)(posY/this->cellSizeY));
	return GetCell( ((int)(posX/this->cellSizeX)) , ((int)(posY/this->cellSizeY)) );

}

//Get cell based on grid index

Cell* CSpatialPartion::GetCell(int indexX,int indexY)
{

	// boundary check
	if(indexX < 0) indexX = 0;
	if(indexY < 0) indexY = 0;
	if(indexX >= numCellX) indexX = numCellX -1;
	if(indexY >= numCellY) indexY = numCellY -1;

	return &cellList[ (indexY*numCellX) + indexX ];

}

#ifdef SP_V1

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
	AddObject(a_obj,a_cell);
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

#endif
std::vector<Cell*> CSpatialPartion::GetObjectMultipleCells(CBaseObject* a_obj)
{
	std::vector<Cell*> CellMultipleAcrossed;

	for(int y = a_obj->TopLeftCellIndex.y; y <=a_obj->BottomRightCellIndex.y;   ++y)//because the screen is flipped so it is revesed/
	{
		//cout<<"Looping through"<<y<<std::endl;
		for(int x = a_obj->TopLeftCellIndex.x; x <=a_obj->BottomRightCellIndex.x;++x)
		{
			//std::cout<<"Index X:"<<x<<" Index Y: "<<y<<std::endl;
			CellMultipleAcrossed.push_back(GetCell(x,y));
			//std::cout<<"Adding "<<temp<<std::endl;
			//indexOfCellMultipleAcrossed.push_back(temp);
		
		}
	}
	return CellMultipleAcrossed;
}
void CSpatialPartion::UpdateObjectTopLeftAndBottomRightCell(CBaseObject* a_obj)
{
	//std::cout<<"Updateing Object "<<(a_obj)->TopLeft<<std::endl;
	short cellx = 0;
	short celly = 0;
	cellx = (((short)((a_obj)->TopLeft.x/this->cellSizeX)));
	celly = (((short)((a_obj)->TopLeft.y/this->cellSizeY)));

	(a_obj)->TopLeftCellIndex.Set(cellx,celly);

	cellx = (((short)((a_obj)->BottomRight.x/this->cellSizeX)));
	celly = (((short)((a_obj)->BottomRight.y/this->cellSizeY)));
	(a_obj)->BottomRightCellIndex.Set(cellx,celly);
}

void CSpatialPartion::AddObjectNeo(CBaseObject* a_obj)
{
	Cell* a_cell = GetCell(a_obj->pos.x,a_obj->pos.y);
	AddObjectNeo(a_obj,a_cell,true);
}

void CSpatialPartion::AddObjectNeo(CBaseObject* a_obj,Cell* theCell,bool duplicateCheck)
{
	if(duplicateCheck)
	{
		for(unsigned short i = 0 ; theCell->objectList.size();++i)
		{
			if(theCell->objectList[i] == a_obj)
			{
				return;
			}
		}
	}
	theCell->objectList.push_back(a_obj);
}

void CSpatialPartion::RemoveObjectNeo(CBaseObject* a_obj,Cell* theCell)
{
	for(unsigned short i = 0 ; theCell->objectList.size();++i)
	{
		if(theCell->objectList[i] == a_obj)
		{
			theCell->objectList[i] = theCell->objectList.back();
			theCell->objectList.pop_back();
			break;
		}
	}
}

void CSpatialPartion::UpdateObjectMultipleCells(CBaseObject* a_obj)
{
	std::vector<Cell*>& newCells =GetObjectMultipleCells(a_obj);

	if(a_obj->ownerCellList != newCells)
	{

		for(unsigned short i = 0 ; i<a_obj->ownerCellList.size();++i)//remove old links
		{
			RemoveObjectNeo(a_obj,a_obj->ownerCellList[i]);
		}

		a_obj->ownerCellList = newCells;//swap to new ones.

		for(unsigned short j = 0 ; j<a_obj->ownerCellList.size();++j)//add new links
		{
			AddObjectNeo(a_obj,a_obj->ownerCellList[j],false);
		}

	}

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

				UpdateObjectTopLeftAndBottomRightCell(*it2);		
				UpdateObjectMultipleCells(*it2);
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

//render one square for debug
void CSpatialPartion::RenderSquare(float posX,float posY, float sizeX,float sizeY,bool drawBoundery)
{
	glPushMatrix();

	glColor3f(1,0,0);

	//working
	//float left = (posX - (sizeX * 0.5));
	//float right = (left + sizeX);
	//float top = (posY + (sizeY*0.5));
	//float bottom = (top - sizeY);

	glBegin(GL_QUADS);


	//glVertex2f(left,top);//top left
	//glVertex2f(right,top);//top right
	//glVertex2f(right,bottom);//bottom right
	//glVertex2f(left,bottom); //bottom left

	glVertex2f((posX - (sizeX * 0.5)),(posY + (sizeY*0.5)));//top left
	glVertex2f((posX + (sizeX * 0.5)),(posY + (sizeY*0.5)));//top right
	glVertex2f((posX + (sizeX * 0.5)),(posY - (sizeY*0.5)));//bottom right
	glVertex2f((posX - (sizeX * 0.5)),(posY - (sizeY*0.5))); //bottom left
	glEnd();

	glColor3f(1,1,1);
	glBegin(GL_LINE_STRIP);
	glVertex2f((posX - (sizeX * 0.5)),(posY + (sizeY*0.5)));//top left
	glVertex2f((posX + (sizeX * 0.5)),(posY + (sizeY*0.5)));//top right
	glVertex2f((posX + (sizeX * 0.5)),(posY - (sizeY*0.5)));//bottom right
	glVertex2f((posX - (sizeX * 0.5)),(posY - (sizeY*0.5))); //bottom left
	glVertex2f((posX - (sizeX * 0.5)),(posY + (sizeY*0.5)));//top left
	glEnd();

	glPopMatrix();
}

//render the grid for debug
void CSpatialPartion::RenderGrid()
{
	glPushMatrix();
	int x = 0;
	int y = 0;

	//float subPosX = 0 ;
	//float subPosY = 0 ;

	for(unsigned short i =0 ; i<cellList.size();++i)
	{
		x = i % numCellX ;
		y = i / numCellX ;

		//works
		//subPosX = ((x+1)*cellSizeX - (cellSizeX*0.5));
		//subPosY = ((y+1)*cellSizeY - (cellSizeY*0.5));
		//std::cout<<subPosY<<std::endl;

		RenderSquare( ((x+1)*cellSizeX - (cellSizeX*0.5)),((y+1)*cellSizeY - (cellSizeY*0.5)),cellSizeX,cellSizeY);
	
		//RenderSquare( (( (x+1) *gridWidth) - (gridWidth*0.5)) *0.5,(( (y+1) *gridHeight) + (gridHeight*0.5)) *0.5,cellSizeX,cellSizeY);
	}
	//RenderSquare( 200, 150 ,400,300);
   // RenderSquare( 600, 150 ,400,300);
	//RenderSquare( 200, 450 ,400,300);
	//RenderSquare( 600, 450 ,400,300);
	glPopMatrix();
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
			cout<<"Cell Raw index: "<<i<<" Index X: "<<i % numCellX<<" Index Y: "<<i / numCellX<<" is size of "<< cellList[i].objectList.size() <<endl;
			//std::cout<<"Index X: "<<i % numCellX<<std::endl;
			//std::cout<<<<std::endl;
		}
	}
}

