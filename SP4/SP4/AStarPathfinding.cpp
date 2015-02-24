#include "AI.h"

CBFS :: CBFS()
{
	for(int i = 0 ; i < 10 ; i++)
		for(int j = 0 ; j < 10 ; j++)
		{
			tempmap[i][j].x = j;
			tempmap[i][j].y = i;
			tempmap[i][j].tileCost = 1;
			tempmap[i][j].isWall = false;
		}
}

CBFS :: ~CBFS()
{
	
}

void CBFS :: SetUpGraph()
{
	for(int i = 0 ; i < 10 ; i++)
	{
		for(int j = 0 ; j < 10 ; j++)
		{
			node tempnode;
			tempnode.x = tempmap[i][j].x;
			tempnode.y = tempmap[i][j].y;
			tempnode.tileCost = tempmap[i][j].tileCost;
			tempnode.isWall = tempmap[i][j].isWall;
			locations.push_back(tempnode);
		}
	}
}

void CBFS :: SearchNeighbours(node theNode)
{

}

void CBFS :: SearchForPath(node start,node end)
{
	
}

float CA_Star :: DistanceToEnd(node start,node end)
{
	return ( abs(end.x-start.x) + abs(end.y-end.y) );
}

void CA_Star :: SearchBestPath(node start,node end,vector<node>locationList)
{
	float cost;
	float newCost;
	search.SetUpGraph();
	//search.SearchNeighbours();
	//search.SearchForPath();
	for(int itr = 0 ; itr < search.path.size() ; itr++)
	{
		node tempnode = search.path[itr];
		
	}

}