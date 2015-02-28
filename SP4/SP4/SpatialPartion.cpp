#include "SpatialPartion.h"
#include "BaseObject.h"
#include <iostream>
//using namespace std;
#include <GL\glut.h>
#include "Sprite.h"



//#define DEBUG_CODE

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

	//short cellx = 0;
	//short celly = 0;
	//cellx = (((short)((a_obj)->TopLeft.x/this->cellSizeX)));
	//celly = (((short)((a_obj)->TopLeft.y/this->cellSizeY)));

	//(a_obj)->TopLeftCellIndex.Set(cellx,celly);

	//cellx = (((short)((a_obj)->BottomRight.x/this->cellSizeX)));
	//celly = (((short)((a_obj)->BottomRight.y/this->cellSizeY)));
	//(a_obj)->BottomRightCellIndex.Set(cellx,celly);

	//std::vector<Vector3> celltomodify;
	
	

#ifdef DEBUG_CODE
	bool stopLeft = false;
	bool stopRight = false;

	Vector3 topLimit;
	Vector3 botLimit;

	Vector3 topLeft;
	Vector3 botRight;

	topLeft.Set(a_obj->pos.x + a_obj->phys.size.x *0.5,a_obj->pos.y + a_obj->phys.size.y*0.5);
	botRight.Set(a_obj->pos.x - a_obj->phys.size.x *0.5,a_obj->pos.y - a_obj->phys.size.y*0.5);

	for(int i=0;i<numCellX&&!(stopLeft&&stopRight);i++)//goes through the grids from small to big
	{//note that i*gridsize is on the left side of the grid
		if(!stopLeft)//should be the biggest possible
		{
			if(topLeft.x<a_obj->pos.x+(i+1)*cellSizeX)
			{
				topLimit.x=i;
				stopLeft=true;
			}
		}
		if(!stopRight)//as small as possible
		{
			if(botRight.x>a_obj->pos.x+(i+1)*cellSizeX)//+1 cause i am testing if its larger then the next square
			{
				botLimit.x=i;
				stopRight=true;
			}
		}
	}
	stopRight=false;
	stopLeft=false;
	for(int i=0;i<numCellY&&!(stopLeft&&stopRight);i++)
	{
		if(!stopLeft)//should be the largest possible
		{
			if(topLeft.y<a_obj->pos.y+(i+1)*cellSizeY)
			{
				topLimit.y=i;
				stopLeft=true;
			}
		}
		if(!stopRight)//should be the smallest possible
		{
			if(botRight.y>a_obj->pos.y+(i+1)*cellSizeY)
			{
				botLimit.y=i;
				stopRight=true;
			}
		}
	}
	for(int i=botLimit.x;i<=topLimit.x;++i)
	{
		for(int j=botLimit.y;j<=topLimit.y;++j)
		{
			cellList[i*numCellY+j].objectList.push_back(a_obj);
		}
	}

#endif

}

//add object into a calculated cell;

void CSpatialPartion::AddObject(CBaseObject* a_obj)
{
	Cell* a_cell = GetCell(a_obj->pos.x,a_obj->pos.y);
	AddObject(a_obj,a_cell);
	//a_cell->objectList.push_back(a_obj);
	//a_obj->ownerCell = a_cell;
	//a_obj->cellvectorindex = a_cell->objectList.size()-1;

	//bool stopLeft = false;
	//bool stopRight = false;

	//Vector3 topLimit;
	//Vector3 botLimit;

	//Vector3 topLeft;
	//Vector3 botRight;

	//topLeft.Set(a_obj->pos.x + a_obj->phys.size.x *0.5,a_obj->pos.y + a_obj->phys.size.y*0.5);
	//botRight.Set(a_obj->pos.x - a_obj->phys.size.x *0.5,a_obj->pos.y - a_obj->phys.size.y*0.5);

	//for(int i=0;i<numCellX&&!(stopLeft&&stopRight);i++)//goes through the grids from small to big
	//{//note that i*gridsize is on the left side of the grid
	//	if(!stopLeft)//should be the biggest possible
	//	{
	//		if(topLeft.x<a_obj->pos.x+(i+1)*cellSizeX)
	//		{
	//			topLimit.x=i;
	//			stopLeft=true;
	//		}
	//	}
	//	if(!stopRight)//as small as possible
	//	{
	//		if(botRight.x>a_obj->pos.x+(i+1)*cellSizeX)//+1 cause i am testing if its larger then the next square
	//		{
	//			botLimit.x=i;
	//			stopRight=true;
	//		}
	//	}
	//}
	//stopRight=false;
	//stopLeft=false;
	//for(int i=0;i<numCellY&&!(stopLeft&&stopRight);i++)
	//{
	//	if(!stopLeft)//should be the largest possible
	//	{
	//		if(topLeft.y<a_obj->pos.y+(i+1)*cellSizeY)
	//		{
	//			topLimit.y=i;
	//			stopLeft=true;
	//		}
	//	}
	//	if(!stopRight)//should be the smallest possible
	//	{
	//		if(botRight.y>a_obj->pos.y+(i+1)*cellSizeY)
	//		{
	//			botLimit.y=i;
	//			stopRight=true;
	//		}
	//	}
	//}
	//for(int i=botLimit.x;i<=topLimit.x;++i)
	//{
	//	for(int j=botLimit.y;j<=topLimit.y;++j)
	//	{
	//		cellList[i*numCellY+j].objectList.push_back(a_obj);
	//	}
	//}
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
std::vector<Cell*> CSpatialPartion::GetObjectStretchedCells(CBaseObject* a_obj)
{
	std::vector<Cell*> CellStretchedAcrossed;

	for(int y = a_obj->TopLeftCellIndex.y; y <=a_obj->BottomRightCellIndex.y;   ++y)//because the screen is flipped so it is revesed/
	{
		//cout<<"Looping through"<<y<<std::endl;
		for(int x = a_obj->TopLeftCellIndex.x; x <=a_obj->BottomRightCellIndex.x;++x)
		{
			//std::cout<<"Index X:"<<x<<" Index Y: "<<y<<std::endl;
			CellStretchedAcrossed.push_back(GetCell(x,y));
			//std::cout<<"Adding "<<temp<<std::endl;
			//indexOfCellStretchedAcrossed.push_back(temp);
		
		}
	}
	return CellStretchedAcrossed;
	//std::cout<<std::endl;
	//std::cout<<std::endl;
	//for(unsigned short i = 0 ; i<indexOfCellStretchedAcrossed.size();++i)
	//{
	//	std::cout<<indexOfCellStretchedAcrossed[i]<<std::endl;
	//}
	//a_obj->celltomodify.clear();
	//a_obj->celltomodify = celltomodify;
}
void CSpatialPartion::UpdateObjectTopLeftAndBottomRightCell(CBaseObject* a_obj)
{
	short cellx = 0;
	short celly = 0;
	cellx = (((short)((a_obj)->TopLeft.x/this->cellSizeX)));
	celly = (((short)((a_obj)->TopLeft.y/this->cellSizeY)));

	(a_obj)->TopLeftCellIndex.Set(cellx,celly);

	cellx = (((short)((a_obj)->BottomRight.x/this->cellSizeX)));
	celly = (((short)((a_obj)->BottomRight.y/this->cellSizeY)));
	(a_obj)->BottomRightCellIndex.Set(cellx,celly);
}

void CSpatialPartion::AddObjectNeo(CBaseObject* a_obj,Cell* theCell,bool duplicateCheck)
{
	if(duplicateCheck)
	{
		for(unsigned short i = 0 ; theCell->objectListNeo.size();++i)
		{
			if(theCell->objectListNeo[i] == a_obj)
			{
				return;
			}
		}
	}

	theCell->objectListNeo.push_back(a_obj);
}

void CSpatialPartion::RemoveObjectNeo(CBaseObject* a_obj,Cell* theCell)
{
	for(unsigned short i = 0 ; theCell->objectListNeo.size();++i)
	{
		if(theCell->objectListNeo[i] == a_obj)
		{
			theCell->objectListNeo[i] = theCell->objectListNeo.back();
			theCell->objectListNeo.pop_back();
			break;
		}
	}
}

void CSpatialPartion::UpdateOwnerCellNeo(CBaseObject* a_obj,Cell* theCell)
{
	
}

void CSpatialPartion::UpdateObjectStretchedCells(CBaseObject* a_obj)
{
	std::vector<Cell*>& newCells =GetObjectStretchedCells(a_obj);

	if(a_obj->ownerCellNeo != newCells)
	{

		for(unsigned short i = 0 ; i<a_obj->ownerCellNeo.size();++i)//remove old links
		{
			RemoveObjectNeo(a_obj,a_obj->ownerCellNeo[i]);
		}

		a_obj->ownerCellNeo = newCells;//swap to new ones.

		for(unsigned short j = 0 ; j<a_obj->ownerCellNeo.size();++j)//add new links
		{
			AddObjectNeo(a_obj,a_obj->ownerCellNeo[j],false);
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
				UpdateObjectStretchedCells(*it2);
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

