#pragma once

#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
using namespace std;
#include "Vector3.h"
#include "SContainer2D.h"

//this old method needs to be upgraded with lua import variable method.
#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 1280
#define TILE_SIZE 32
#define LEFT_BORDER 0
#define BOTTOM_BORDER 0
#define MAX_TILE 17
#define MAP_WIDTH SCREEN_WIDTH/TILE_SIZE
#define MAP_HEIGHT SCREEN_HEIGHT/TILE_SIZE


struct searchResult
{
public:
	short xIndex;
	short yIndex;
	float xFloat;
	float yFloat;
public:
	searchResult()
	{ 
		xFloat = yFloat = xIndex = yIndex = 0;
	};
	~searchResult(){};

	bool CompareWithAnotherOfGridIndex(searchResult & rhs)
	{
		if(this->xIndex == rhs.xIndex &&  this->yIndex ==  rhs.yIndex)
		{
			return true;
		}else
		{
			return false;
		}
	}

	friend std::ostream& operator<<( std::ostream& os, searchResult& rhs) //print to ostream
	{

		os << "[ " << rhs.xIndex << ", " << rhs.yIndex << " ]";
		return os;
	}
};

class CObjectManager;

class CMap
{
public:
	CObjectManager* OM;
public:
	CMap(CObjectManager* theObjectManager);
	~CMap(void);

	void Init( int theScreen_Height, int theScreen_Width, 
		       const int theMap_Height, const int theMap_Width, 
		       const int theTileSize);
	bool LoadMap(const string mapName);
	int getNumOfTiles_ScreenHeight(void);	// Get the number of tiles for height of the screen
	int getNumOfTiles_ScreenWidth(void);	// Get the number of tiles for width of the screen
	int getNumOfTiles_MapHeight(void);		// Get the number of tiles for height of the map
	int getNumOfTiles_MapWidth(void);		// Get the number of tiles for width of the map

	vector<vector<int> > theScreenMap;

	Vector3 mapMatrix[MAP_WIDTH][MAP_HEIGHT];
	void printMapMatrix(short mode = 3);
	void resetMapMatrix();
	void initMapMatrix();
	searchResult lookupPosition(Vector3 currentPosition,bool strict = false);//convert distance to matrix index
	searchResult lookupPosition(float x,float y = 0,float z = 0,bool strict = false);
	searchResult lookPositionText(Vector3 currentPosition, bool strict = false);
	Vector3 lookupIndex(short x, short y);
	std::vector<SContainer2D> FindValidNearbyGrid(SContainer2D centre);
	std::vector<SContainer2D> FindValidNearbyGrid(Vector3 centreposition);
	void RunMap();
	
	//csv number
	int ScreenNum;

	float Level;
	int LevelCount;
	
	int checkPosition_X;// = (int) ceil((float)(mapOffset_x+theHero->GetPos_x()) / TILE_SIZE);
	int checkPosition_Y; // = (int) floor( ((float)theHero->GetPos_y()-theHero->GetJumpspeed()) / TILE_SIZE);*/

private:
	int theScreen_Height;
	int theScreen_Width;
	int theMap_Height;
	int theMap_Width;
	int theNumOfTiles_ScreenHeight;
	int theNumOfTiles_ScreenWidth;
	int theNumOfTiles_MapHeight;
	int theNumOfTiles_MapWidth;
	int theTileSize;
	
	int mapOffset_x;
	int mapOffset_y;

	bool LoadFile(const string mapName);


};
