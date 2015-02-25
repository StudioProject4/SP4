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

CAStarPathFinding :: CAStarPathFinding()
{
	
}

CAStarPathFinding :: ~CAStarPathFinding()
{
	
}

void CAStarPathFinding ::SetUpGraph(int maxHorizontalTile, int maxVerticalTile,node start,node end)
{
	this->start = start;
	this->end = end;
	this->tempParentNode = start;
	this->maxHorizontalTile = maxHorizontalTile;
	this->maxVerticalTile = maxVerticalTile;

	for(int i = 0 ; i < this->maxVerticalTile ; i++)
	{
		for(int j = 0 ; j < this->maxHorizontalTile ; j++)
		{
			//setup graph

			//temp setup till i get the map
			tempMap[i][j].x = j;
			tempMap[i][j].y = i;
			tempMap[i][j].tileCost = 1;
			tempMap[i][j].isWall = false;
		}
	}
}

void CAStarPathFinding :: SearchForPath(node currentNode)
{
	for(int i = 0 ; i < this->maxVerticalTile ; i++)
	{
		for(int j = 0 ; j < this->maxHorizontalTile ; j++)
		{
			if(tempMap[i][j].x == currentNode.x && tempMap[i][j].y == currentNode.y)
			{
				node tempNode;
				if(tempMap[i][j-1].isWall == false)
				{
					tempNode = tempMap[i][j-1];
					openList.push_back(tempNode);
				}
				else if(tempMap[i][j+1].isWall == false)
				{
					tempNode = tempMap[i][j+1];
					openList.push_back(tempNode);
				}
				start = currentNode;
				closeList.push_back(start);
				ChooseAPath();
				if(start.x != end.x && start.y != end.y)
				{
					//add in when completed to prevent infinite loop
					//SearchForPath(start);
				}
			}
		}
	}
}

float CAStarPathFinding :: DistanceToEnd()
{
	return ( abs(end.x - start.x) + abs(end.y - start.y) );
}

void CAStarPathFinding :: FindPath()
{
	//SetUpGraph();
	//SearchForPath();
	
}

void CAStarPathFinding :: ChooseAPath()
{
	std :: vector<node> ::iterator it;

	for(it = closeList.begin(); it!= closeList.end();++it)
	{
		
	}
	
}