#include "Map.h"
#include "ObjectManager.h"
#include "ManufactureManager.h"
#include <stdlib.h>

#include "HealthPU.h"
#include "PointsAddPU.h"
#include "SpeedPU.h"
#include "JumpPU.h"
#include "InvinciblePU.h"
#include "ChinesePoints.h"
#include "MalayPoints.h"

#include <iostream>
CMap::CMap(CObjectManager* theObjectManager)

: theScreen_Height(0)
, theScreen_Width(0)
, theMap_Height(0)
, theMap_Width(0)
, theNumOfTiles_ScreenHeight(0)
, theNumOfTiles_ScreenWidth(0)
, theNumOfTiles_MapHeight(0)
, theNumOfTiles_MapWidth(0)
, theTileSize(0)
, Level(1)
, LevelCount(0)
, mapOffset_x(0)
, mapOffset_y(0)
, OM(theObjectManager)
{
	theScreenMap.clear();

}

CMap::~CMap(void)
{
	theScreenMap.clear();
}

void CMap::Init(const int theScreen_Height, const int theScreen_Width, 
				const int theMap_Height, const int theMap_Width, 
				const int theTileSize)
{
	this->theScreen_Height = theScreen_Height;
	this->theScreen_Width = theScreen_Width;
	this->theMap_Height = theMap_Height;
	this->theMap_Width = theMap_Width;
	this->theTileSize = theTileSize;

	theNumOfTiles_ScreenHeight = (int) (theScreen_Height / theTileSize);
	theNumOfTiles_ScreenWidth = (int) (theScreen_Width / theTileSize);
	theNumOfTiles_MapHeight = (int) (theMap_Height / theTileSize);
	theNumOfTiles_MapWidth = (int) (theMap_Width / theTileSize);

	theScreenMap.resize(theNumOfTiles_MapHeight);
	for (int i = 0; i < theNumOfTiles_MapHeight; ++i)
		theScreenMap[i].resize(theNumOfTiles_MapWidth);

	//resetMapMatrix();
	initMapMatrix();
	
	
}
void CMap::initMapMatrix()
{
	for (short y = 0; y < MAP_HEIGHT; ++y)
	{
		for (short x = 0; x < MAP_WIDTH; ++x)
		{
			mapMatrix[x][y].Set((x + 0.5f) * TILE_SIZE, (y + 0.5f) * TILE_SIZE, 0);
		}
	}
}
void CMap::resetMapMatrix()
{
	
	for (short y = 0; y < MAP_HEIGHT; ++y)
	{
		for (short x = 0; x < MAP_WIDTH; ++x)
		{
			mapMatrix[x][y].SetZero();
		}
	}
}
void CMap::printMapMatrix(short mode)
{
	switch (mode)
	{
	
		case 0:
		default:
			for (short y = 0; y < MAP_HEIGHT; ++y)
			{
				for (short x = 0; x < MAP_WIDTH; ++x)
				{
					std::cout << "<" << y << ">" << "<" << x << ">" << mapMatrix[x][y] << " ";
				}
				std::cout << std::endl;
			}
			break;
		case 1:
			for (short y = 0; y < MAP_HEIGHT; ++y)
			{
				for (short x = 0; x < MAP_WIDTH; ++x)
				{
					std::cout << " |" << mapMatrix[x][y] << "| ";
				}
				std::cout << std::endl;
			}
			break;
		case 2:
			for (short y = 0; y < MAP_HEIGHT; ++y)
			{
				for (short x = 0; x < MAP_WIDTH; ++x)
				{
					std::cout << "|" << mapMatrix[x][y] << "|";
				}
				std::cout << std::endl;
			}
			break;
		case 3:
			for (short y = 0; y < MAP_HEIGHT; ++y)
			{
				std::cout<<"Row "<<y<<": " << std::endl;
				for (short x = 0; x < MAP_WIDTH; ++x)
				{
					std::cout << mapMatrix[x][y];
				}
				std::cout << std::endl;
			}
			break;
	}
}

bool CMap::LoadMap(const string mapName)
{
	if (LoadFile(mapName) == true)
	{
		printf("Map (%s) has been successfully loaded!\n", mapName.c_str());
		return true;
	}

	return false;
}
searchResult CMap::lookupPosition(Vector3 currentPosition,bool strict)
{
	bool xfound = false;
	bool yfound = false;
	searchResult result;
	short minX = (currentPosition.x / TILE_SIZE) -1;
	short minY = (currentPosition.y / TILE_SIZE) -1;
	short maxX = minX + 2;
	short maxY = minY + 2;
	//cout <<"minX: "<< minX << endl;
	//cout <<"minY: " << minY << endl;

	//if not found
	if (!strict)
	{
		for (short y = minY; y < maxY; ++y)
		{
			for (short x = minX; x < maxX; ++x)
			{
				if (mapMatrix[x][y].x == currentPosition.x && xfound == false)
				{
					result.xIndex = x;
					xfound = true;
				}
				if (mapMatrix[x][y].y == currentPosition.y && yfound == false)
				{
					result.yIndex = y;
					yfound = true;
				}
			}

		}
		if (xfound == false)//safety net,in case the object is not centered in the cell
		{
			result.xIndex = result.xFloat = currentPosition.x / TILE_SIZE;
		}
		if (yfound == false)
		{
			result.yIndex = result.yFloat = currentPosition.y / TILE_SIZE;
		}
	}
	else
	{
		for (short y = minY; y < maxY; ++y)
		{
			for (short x = minX; x < maxX; ++x)
			{
				if (mapMatrix[x][y].IsEqual(currentPosition.x,currentPosition.y))
				{
					result.xIndex = x;
					result.yIndex = y;
					xfound = yfound = true;
				}
			}

		}
	}
	return result;
}

searchResult CMap::lookPositionText(Vector3 currentPosition, bool strict)
{
	bool xfound = false;
	bool yfound = false;
	searchResult result;
	short minX = (currentPosition.x / TILE_SIZE) -1;
	short minY = (currentPosition.y / TILE_SIZE) -1;
	short maxX = minX + 2;
	short maxY = minY + 2;
	//cout <<"minX: "<< minX << endl;
	//cout <<"minY: " << minY << endl;

	//if not found
	if (!strict)
	{
		for (short y = minY; y < maxY; ++y)
		{
			for (short x = minX; x < maxX; ++x)
			{
				if (mapMatrix[x][y].x == currentPosition.x && xfound == false)
				{
					result.xIndex = x;
					xfound = true;
				}
				if (mapMatrix[x][y].y == currentPosition.y && yfound == false)
				{
					result.yIndex = y;
					yfound = true;
				}
			}

		}
		if (xfound == false)//safety net,in case the object is not centered in the cell
		{
			result.xIndex = result.xFloat = currentPosition.x / TILE_SIZE;
		}
		if (yfound == false)
		{
			result.yIndex = result.yFloat = currentPosition.y / TILE_SIZE;
		}
	}
	else
	{
		for (short y = minY; y < maxY; ++y)
		{
			for (short x = minX; x < maxX; ++x)
			{
				if (mapMatrix[x][y].IsEqual(currentPosition.x,currentPosition.y))
				{
					result.xIndex = x;
					result.yIndex = y;
					xfound = yfound = true;				
				}
			}

		}
	}
	
	
		ScreenNum = theScreenMap[result.yIndex][result.xIndex];
	//	std::cout << ScreenNum << std::endl;
		
		return result;
	
}

Vector3 CMap::lookupIndex(short x, short y)
{
	Vector3 result;
	if ((x > 0 && x < MAP_WIDTH) && (y > 0 && y < MAP_HEIGHT))
	{
		result = Vector3(mapMatrix[x][y].x, mapMatrix[x][y].y);
	}
	//cout << result.x << result.y << endl;
	return result;
}
searchResult CMap::lookupPosition(float x, float y, float z,bool strict)
{
	bool xfound = false;
	bool yfound = false;
	searchResult result;
	short minX = (x / TILE_SIZE) - 1;
	short minY = (y / TILE_SIZE) - 1;
	short maxX = minX + 2;
	short maxY = minY + 2;
	//cout <<"minX: "<< minX << endl;
	//cout <<"minY: " << minY << endl;

	//if not found
	if (!strict)
	{
		for (short y = minY; y < maxY; ++y)
		{
			for (short x = minX; x < maxX; ++x)
			{
				if (mapMatrix[x][y].x == x && xfound == false)
				{
					result.xIndex = x;
					xfound = true;
				}
				if (mapMatrix[x][y].y == y && yfound == false)
				{
					result.yIndex = y;
					yfound = true;
				}
			}

		}
		if (xfound == false)//safety net,in case the object is not centered in the cell
		{
			result.xIndex = result.xFloat = x / TILE_SIZE;
		}
		if (yfound == false)
		{
			result.yIndex = result.yFloat = y / TILE_SIZE;
		}
	}
	else
	{
		for (short y = minY; y < maxY; ++y)
		{
			for (short x = minX; x < maxX; ++x)
			{
				if (mapMatrix[x][y].x == x && mapMatrix[x][y].y == y)
				{
					result.xIndex = x;
					result.yIndex = y;
					xfound = yfound = true;
				}
			}

		}
	}


	return result;
}

bool CMap::LoadFile(const string mapName)
{
	int theLineCounter = 0;
	int theMaxNumOfColumns = 0;

	ifstream file(mapName.c_str());
	if(file.is_open())
	{
		int i = 0, k = 0;
		while(file.good())
		{
			string aLineOfText = "";
			getline(file, aLineOfText);

			// If this line is not a comment line, then process it
			if(!(aLineOfText.find("//") == NULL) && aLineOfText != "")
			{
				if (theLineCounter == 0)
				{
					// This is the first line of the map data file
					string token;
					istringstream iss(aLineOfText);
					while(getline(iss, token, ','))
					{
						// Count the number of columns
						theMaxNumOfColumns = atoi(token.c_str());
					}
				}
				else
				{
					int theColumnCounter = 0;

					string token;
					istringstream iss(aLineOfText);
					CHealthPU* temph = nullptr;
					CPointsAddPU* tempPT = nullptr;
					CSpeedPU* tempSpd = nullptr;
					CInvinciblePU* tempIn = nullptr;
					CJumpPU* tempJp = nullptr;
					CChinesePoints* tempCpt = nullptr;
					CMalayPoints* tempMpt = nullptr;

					while(getline(iss, token, ','))
					{
						int temp = atoi(token.c_str());
						switch(temp)
						{

						case 3:			//health
							theScreenMap[theLineCounter][theColumnCounter++] = 1;
							//call factory to create a power up at this pos
							temph = CManufactureManager::GetInstance()->CreatePowerUpRecovery();
							temph->pos = this->lookupIndex(theColumnCounter-1,theLineCounter);
							temph->Init();
							OM->AddObject(temph);					

							break;
						case 4:			//speed
							theScreenMap[theLineCounter][theColumnCounter++] = 1;
							//call factory to create a power up at this pos
							tempSpd = CManufactureManager::GetInstance()->CreatePowerUpSpeedUp();
							tempSpd->pos = this->lookupIndex(theColumnCounter-1, theLineCounter);
							tempSpd->Init();
							OM->AddObject(tempSpd);
							
							break;
						case 5:			//invincible
							theScreenMap[theLineCounter][theColumnCounter++] = 1;
							//call factory to create a power up at this pos
							tempIn = CManufactureManager::GetInstance()->CreatePowerUpInvincible();
							tempIn->pos = this->lookupIndex(theColumnCounter-1, theLineCounter);
							tempIn->Init();
							OM->AddObject(tempIn);

							break;
						case 6:			//points add
							theScreenMap[theLineCounter][theColumnCounter++] = 1;
							//call factory to create a power up at this pos
							tempPT = CManufactureManager::GetInstance()->CreatePowerUpPoints();
							tempPT->pos = this->lookupIndex(theColumnCounter-1, theLineCounter);
							tempPT->Init();
							OM->AddObject(tempPT);

							break;
						case 7:			//jump
							theScreenMap[theLineCounter][theColumnCounter++] = 1;
							//call factory to create a power up at this pos
							tempJp = CManufactureManager::GetInstance()->CreatePowerUpJumpHigh();
							tempJp->pos = this->lookupIndex(theColumnCounter-1, theLineCounter);
							tempJp->Init();
							OM->AddObject(tempJp);	

							break;
						case 8:		//Chinese Sign
							theScreenMap[theLineCounter][theColumnCounter++] = 1;
							//call factory to create a power up at this pos
							tempCpt = CManufactureManager::GetInstance()->CreateChinesePoints();
							tempCpt->pos = this->lookupIndex(theColumnCounter-1, theLineCounter);
							tempCpt->Init(tempCpt->pos, tempCpt->phys.size);
							OM->AddObject(tempCpt);	

							break;
						case 9:		//Halal Sign
							theScreenMap[theLineCounter][theColumnCounter++] = 1;
							//call factory to create a power up at this pos
							tempMpt = CManufactureManager::GetInstance()->CreateMalayPoints();
							tempMpt->pos = this->lookupIndex(theColumnCounter-1, theLineCounter);
							tempMpt->Init(tempMpt->pos, tempMpt->phys.size);
							OM->AddObject(tempMpt);	

							break;
						default:
							theScreenMap[theLineCounter][theColumnCounter++] = atoi(token.c_str());
							break;
						}
					}
				}
			}

			theLineCounter++;
		}
	}
	return true;
}

// Get the number of tiles for height of the screen
int CMap::getNumOfTiles_ScreenHeight(void)
{
	return theNumOfTiles_ScreenHeight;
}

// Get the number of tiles for width of the screen
int CMap::getNumOfTiles_ScreenWidth(void)
{
	return theNumOfTiles_ScreenWidth;
}

// Get the number of tiles for height of the map
int CMap::getNumOfTiles_MapHeight(void)
{
	return theNumOfTiles_MapHeight;
}

// Get the number of tiles for width of the map
int CMap::getNumOfTiles_MapWidth(void)
{
	return theNumOfTiles_MapWidth;
}
std::vector<SContainer2D> CMap::FindValidNearbyGrid(SContainer2D centre)
{
	std::vector<SContainer2D> neighbour;
	SContainer2D tempcontainer;
	short left = centre.x - 1;
	short right = centre.x + 1;
	short up = centre.y - 1;
	short down = centre.y + 1;

	if(left >=0 && left <MAP_WIDTH)
	{
		//cout<<"Left element accepted"<<endl;
		//cout<<"left element "<<graph[left][index.y]->id<<"accepted"<<endl;
		tempcontainer.x = left;
		tempcontainer.y = centre.y;
		neighbour.push_back(tempcontainer);
	}
	if(right >=0 && right <MAP_WIDTH)
	{
		//cout<<"right element accepted"<<endl;
		//cout<<"right element "<<graph[right][index.y]->id<<"accepted"<<endl;
		tempcontainer.x = right;
		tempcontainer.y = centre.y;
		neighbour.push_back(tempcontainer);
	}
	if(up >=0 && up <MAP_HEIGHT)
	{
		//cout<<"up element accepted"<<endl;
		//cout<<"Up element "<<graph[index.x][up]->id<<"accepted"<<endl;
		tempcontainer.x = centre.x;
		tempcontainer.y = up;
		neighbour.push_back(tempcontainer);
	}
	if(down >=0 && down <MAP_HEIGHT)
	{
		//cout<<"down element accepted"<<endl;
		//cout<<"Down element "<<graph[index.x][down]->id<<"accepted"<<endl;
		tempcontainer.x = centre.x;
		tempcontainer.y = down;
		neighbour.push_back(tempcontainer);

	}
	for(unsigned short i = 0 ; i<neighbour.size();++i)
	{
		std::cout<<neighbour[i]<<std::endl;
	}
	return neighbour;
}
std::vector<SContainer2D> CMap::FindValidNearbyGrid(Vector3 centreposition)
{

	std::vector<SContainer2D> neighbour;
	searchResult centretemp = lookupPosition(centreposition);
	SContainer2D centre(centretemp.xIndex,centretemp.yIndex);
	SContainer2D tempcontainer;
	short left = centre.x - 1;
	short right = centre.x + 1;
	short up = centre.y - 1;
	short down = centre.y + 1;

	if(left >=0 && left <MAP_WIDTH)
	{
		//cout<<"Left element accepted"<<endl;
		//cout<<"left element "<<graph[left][index.y]->id<<"accepted"<<endl;
		tempcontainer.x = left;
		tempcontainer.y = centre.y;
		neighbour.push_back(tempcontainer);
	}
	if(right >=0 && right <MAP_WIDTH)
	{
		//cout<<"right element accepted"<<endl;
		//cout<<"right element "<<graph[right][index.y]->id<<"accepted"<<endl;
		tempcontainer.x = right;
		tempcontainer.y = centre.y;
		neighbour.push_back(tempcontainer);
	}
	if(up >=1 && up <MAP_HEIGHT-1)//the minus 1 and at least 1 in this case is special triming for the current program
	{
		//cout<<"up element accepted"<<endl;
		//cout<<"Up element "<<graph[index.x][up]->id<<"accepted"<<endl;
		tempcontainer.x = centre.x;
		tempcontainer.y = up;
		neighbour.push_back(tempcontainer);
	}
	if(down >=1 && down <MAP_HEIGHT-1)
	{
		//cout<<"down element accepted"<<endl;
		//cout<<"Down element "<<graph[index.x][down]->id<<"accepted"<<endl;
		tempcontainer.x = centre.x;
		tempcontainer.y = down;
		neighbour.push_back(tempcontainer);

	}
	//for(unsigned short i = 0 ; i<neighbour.size();++i)
	//{
	//	std::cout<<neighbour[i]<<std::endl;
	//}
	return neighbour;
}

void CMap::RunMap()
{
	//load map
	if(Level != LevelCount)
	{
		char* templv=new char[16];
		sprintf(templv,"Level1_%d.csv",Level);
		LevelCount=Level;
		LoadMap(templv);
	}
}