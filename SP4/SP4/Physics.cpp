#include "Physics.h"

CPhysics::CPhysics()
	: Map(NULL)
{
	for(int i=0;i<10;++i)//map[x][y]
	{
		for(int j=1;j<9;++j)
		{
			tempMap[i][j]=0;
		}
		tempMap[i][0]=1;
		tempMap[i][9]=1;
	}
	for(int i=0;i<10;++i)
	{
		tempMap[0][i]=1;
	}
}

CPhysics::~CPhysics()
{

}

int CPhysics::getTile(Vector3 thePos)					//check for the position to each tile index, input the position, have to show the index of the tile
{
	//Map->lookupPosition(thePos.x, thePos.y, 0); //RunTime error here,most probably 

	return tempMap[(int)(thePos.x/20)][(int)(thePos.y/20)];
}

Vector3 CPhysics::getTileV(float posX,float posY)
{
	searchResult * result = &Map->lookupPosition(posX,posY); 
	Vector3 temp(result->xIndex,result->yIndex);
	delete result;
	return temp;
}

Vector3 CPhysics::getTileV(Vector3 thePos)					
{
	searchResult * result = &Map->lookupPosition(thePos); 
	Vector3 temp(result->xIndex,result->yIndex);
	delete result;
	return temp;
}
bool CPhysics::Init(Vector3 pos,Vector3 size)
{
	gravity = 20;
	vel.Set();
	this->size=size;
	this->pos=pos;
	return true;
}

bool CPhysics::TestCol(Vector3 pos2,Vector3 size2)
{
	if(abs(pos.x-pos2.x) > (size.x+size2.x)*0.5f)
		return false;

	if(abs(pos.y-pos2.y) > (size.y+size2.y)*0.5f)
		return false;
	return true;
}

void CPhysics::Jump()
{
	if(!inAir)
	{
		vel.y=80;
	}
}

Vector3 CPhysics::Update(Vector3 pos)
{
	float delta=0.06;
	int maptilex=0;
	int maptiley=0;
	//if (vel.y>0)//if moving upwards check on top not below
	//{//up is negative
	//	size.y=-size.y;
	//}
	//get the pos of where it will get to
	vel.y-=gravity*delta;
	maptilex=maptiley = getTile(pos+size*0.5+vel*delta);//middle
	if(vel.x>0)
	{
		int temp=getTile(pos+Vector3(size.x*0.5,0,0)+vel*delta);
		maptilex=temp;
	}
	else if(vel.x<0)
	{
		int temp=getTile(pos+Vector3(-size.x*0.5,0,0)+vel*delta);
		maptilex=temp;
	}
	if(vel.y>0)
	{
		int temp=getTile(pos+Vector3(0,size.y*0.5,0)+vel*delta);
		maptiley=temp;
	}
	else if(vel.y<0)
	{
		int temp=getTile(pos+Vector3(0,-size.y*0.5,0)+vel*delta);
		maptiley=temp;
	}

	if (maptiley == 0)//==air
	{
		inAir=true;
	}
	else if (maptiley == 1)//something solid
	{
		vel.y=0;
		inAir=false;
	}

	if(maptilex==1)
	{
		vel.x=0;
	}
	//else if maptile == slope
	//slopePhysics(dir)
	//else if(special tile)//such as levers etc
	// dont do anything;
	if(size.y<0)
		size.y=-size.y;//set it back to positive

	pos+=vel*delta;
	this->pos.Set(pos.x,pos.y,pos.z);
	//The pos.x and pos.y are the top left corner of the hero, so we find the tile which this position occupies.
	return this->pos;
}
