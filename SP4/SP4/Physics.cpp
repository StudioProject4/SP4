#include "Physics.h"
#include "Map.h"
CPhysics::CPhysics()
	: map(NULL)
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
	searchResult * result = &map->lookupPosition(posX,posY); 
	Vector3 temp(result->xIndex,result->yIndex);
	delete result;
	return temp;
}

Vector3 CPhysics::getTileV(Vector3 thePos)					
{
	searchResult * result = &map->lookupPosition(thePos); 
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
		vel.y=-80;
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
	vel.y+=gravity*delta;
	maptilex=maptiley = getTile(pos+size*0.5+vel*delta);//middle
	if(vel.x>0)
	{
		if(TestColMap(pos,false,false,false,true,map))
		{
			vel.x=0;
			//pos.x=(float)(((int)(pos.x/TILE_SIZE))*TILE_SIZE)+TILE_SIZE*0.495;//casted to int to remove the remainder then back to float

		}
		//maptilex=temp;
	}
	else if(vel.x<0)
	{
		if(TestColMap(pos,false,false,true,false,map))
		{
			vel.x=0;
			//pos.x=(float)(((int)(pos.x/TILE_SIZE))*TILE_SIZE)+TILE_SIZE*0.495;//casted to int to remove the remainder then back to float
		}
	}
	if(vel.y>0)
	{
		if(TestColMap(pos,false,true,false,false,map))
		{
			int temp=getTile(pos+Vector3(0,size.y*0.5,0)+vel*delta);
			vel.y=0;
			inAir=false;
			//pos.y=(float)(((int)(pos.y/TILE_SIZE))*TILE_SIZE)+TILE_SIZE*0.495;//casted to int to remove the remainder then back to float
		}
		else
		{
			inAir=true;
		}
		//maptiley=temp;
	}
	else if(vel.y<0)
	{
		if(TestColMap(pos,true,false,false,false,map))
		{
			int temp=getTile(pos+Vector3(0,-size.y*0.5,0)+vel*delta);
			vel.y=0;
			//pos.y=(float)(((int)(pos.y/TILE_SIZE))*TILE_SIZE)+TILE_SIZE*0.4;//casted to int to remove the remainder then back to float

		}
		else
		{
			inAir=true;
		}
		//maptiley=temp;
	}


	//if(maptilex==1)
	//{
	//	vel.x=0;
	//}
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

//Check for collision of hero with obstacles in a certain position
bool CPhysics::TestColMap(Vector3 pos, 
								   bool m_bCheckUpwards, bool m_bCheckDownwards, 
								   bool m_bCheckLeft, bool m_bCheckRight, CMap* map,int x_offset,int y_offset)
{
	float delta=0.0166;
	//The pos.x and pos.y are the top left corner of the hero, so we find the tile which this position occupies.
	int tile_topleft_x = (int)floor((float)(x_offset+pos.x+vel.x*delta-TILE_SIZE*0.5) / TILE_SIZE);
	int tile_topleft_y = (int)floor((float)(y_offset+pos.y+vel.y*delta-TILE_SIZE*0.5)/ TILE_SIZE);
	int proceed=false;
	Vector3 reference[9];
	int j=0;
	if(tile_topleft_x<0||tile_topleft_x>map->getNumOfTiles_MapWidth()-2)
	{
		return true;
	}
	if(tile_topleft_y<0||tile_topleft_y>map->getNumOfTiles_MapHeight()-2)
	{
		return true;
	}
	if (m_bCheckLeft)
	{
		if((int)(pos.y-TILE_SIZE/2)%32>2)
			if (map->theScreenMap[tile_topleft_y+1][tile_topleft_x] == 0)
			{
				proceed=true;
				reference[j].Set((tile_topleft_x)*TILE_SIZE,(tile_topleft_y+1)*TILE_SIZE);
				j++;
			}
		if((int)(pos.y-TILE_SIZE/2)%32<30)
			if (map->theScreenMap[tile_topleft_y][tile_topleft_x] == 0)
			{
				proceed=true;
				reference[j].Set((tile_topleft_x)*TILE_SIZE,(tile_topleft_y)*TILE_SIZE);
				j++;
			
			}
	}

	if (m_bCheckRight)
	{
		if((int)(pos.y-TILE_SIZE/2)%32<30)
			if (map->theScreenMap[tile_topleft_y][tile_topleft_x+1] == 0)
			{
				proceed=true;
				reference[j].Set((tile_topleft_x+1)*TILE_SIZE,(tile_topleft_y)*TILE_SIZE);
				j++;
			}
		
		if((int)(pos.y-TILE_SIZE/2)%32>2)
			if (map->theScreenMap[tile_topleft_y+1][tile_topleft_x+1] == 0)
			{
				reference[j].Set((tile_topleft_x+1)*TILE_SIZE,(tile_topleft_y+1)*TILE_SIZE);
				proceed=true;
				j++;
			}
	}

	if (m_bCheckUpwards)
	{
		if((int)(pos.x-TILE_SIZE/2)%32<30)
			if (map->theScreenMap[tile_topleft_y][tile_topleft_x] == 0)
			{
				proceed=true;
				reference[j].Set((tile_topleft_x)*TILE_SIZE,(tile_topleft_y)*TILE_SIZE);
				j++;
			}
			
		if((int)(pos.x-TILE_SIZE/2)%32>2)
			if (map->theScreenMap[tile_topleft_y][tile_topleft_x+1] == 0)
			{
				proceed=true;
				reference[j].Set((tile_topleft_x+1)*TILE_SIZE,(tile_topleft_y)*TILE_SIZE);
				j++;
			}
	}

	if (m_bCheckDownwards)
	{
		if((int)(pos.x-TILE_SIZE/2)%32<30)
		if (map->theScreenMap[tile_topleft_y+1][tile_topleft_x] == 0)
		{
			proceed=true;
			reference[j].Set((tile_topleft_x)*TILE_SIZE,(tile_topleft_y+1)*TILE_SIZE);
			j++;
		}
		if((int)(pos.x-TILE_SIZE/2)%32>2)
		if (map->theScreenMap[tile_topleft_y+1][tile_topleft_x+1] == 0)
		{
			proceed=true;
			reference[j].Set((tile_topleft_x+1)*TILE_SIZE,(tile_topleft_y+1)*TILE_SIZE);
			j++;
		}
	}

	if(proceed)
	{
		for(int i=0;i<j;++i)
		{
			if(abs(reference[i].x-x_offset-pos.x)<TILE_SIZE*1.7f-6 && abs(reference[i].y-y_offset-pos.y)<TILE_SIZE*1.7-6)
			{
				return true;
			}
		}
	}
	return false;
}

void CPhysics::MoveSide(bool mode)
{
	
	if(mode)
	{
		vel.x=30;
	}
	else
	{
		vel.x=-30;
	}
}