#include "AI.h"

CAStarPathFinding :: CAStarPathFinding()
{
	//for(int i = 0 ; i < 10 ; i++)
	//{
	//	for(int j = 0 ; j < 10 ; j++)
	//	{
	//		//setup graph

	//		//temp setup till i get the map
	//		tempMap[i][j].x = j * 10;
	//		tempMap[i][j].y = i * 10;
	//		tempMap[i][j].tileCost = 1;
	//		tempMap[i][j].isWall = false;
	//		tempMap[i][j].index = ((i * 10) + j);
	//	}
	//}
}

CAStarPathFinding :: ~CAStarPathFinding()
{
	for(int i = 0 ; i < maxHorizontalTile ; ++i)
	{
		delete [] tempMap[i];
	}
	delete [] tempMap;
}

void CAStarPathFinding ::SetUpGraph(CMap theMap)
{
	this->maxHorizontalTile = MAP_WIDTH;
	this->maxVerticalTile = MAP_HEIGHT;

	tempMap = new node*[maxVerticalTile];
	for(int i = 0 ; i < maxVerticalTile ; ++i)
	{
		tempMap[i] = new node[maxHorizontalTile];
	}

	for(int i = 0 ; i < this->maxVerticalTile ; i++)
	{
		for(int j = 0 ; j < this->maxHorizontalTile ; j++)
		{
			//setup graph

			//temp setup till i get the map
			tempMap[i][j].x = j * TILE_SIZE;
			tempMap[i][j].y = i * TILE_SIZE;
			tempMap[i][j].tileCost = 1;
			tempMap[i][j].isWall = theMap.theScreenMap[i][j];
			tempMap[i][j].index = ((i * 10) + j);
		}
	}
}

void CAStarPathFinding :: SetUpPath(Vector3 startPosition,Vector3 endPosition)
{
	
	for(int i = 0 ; i < this->maxVerticalTile ; i++)
	{
		for(int j = 0 ; j < this->maxHorizontalTile ; j++)
		{
			if(startPosition.x > (tempMap[i][j].x - TILE_SIZE) && startPosition.x < (tempMap[i][j].x + TILE_SIZE) && startPosition.y > (tempMap[i][j].y - TILE_SIZE) && startPosition.y < (tempMap[i][j].y + TILE_SIZE))
			{
				start = tempMap[i][j];
			}
			if(endPosition.x >  (tempMap[i][j].x - TILE_SIZE) && endPosition.x < (tempMap[i][j].x + TILE_SIZE) && endPosition.y > (tempMap[i][j].y - TILE_SIZE) && endPosition.y < (tempMap[i][j].y + TILE_SIZE))
			{
				end = tempMap[i][j];
			}
		}
	}

	//node start,node end
	//this->start = start;
	//this->end = end;
	this->currentNode = start;

	closeList.push_back(start);
}

void CAStarPathFinding :: SearchForPath()
{
	for(int i = 0 ; i < this->maxVerticalTile ; i++)
	{
		for(int j = 0 ; j < this->maxHorizontalTile ; j++)
		{
			if(tempMap[i][j].x == currentNode.x && tempMap[i][j].y == currentNode.y) // if currentnode is found
			{
				node tempNode;
				//if(tempMap[i-1][j].isWall == true) //not in air
				{
					if(tempMap[i][j-1].isWall == false) //look left
					{
						tempNode = tempMap[i][j-1];
						openList.push_back(tempNode);
					}
					if(tempMap[i][j+1].isWall == false) //look right
					{
						tempNode = tempMap[i][j+1];
						openList.push_back(tempNode);
					}
					if(tempMap[i][j].isWall == false) //look top
					{
						tempNode = tempMap[i][j-1];
						openList.push_back(tempNode);
					}
					if(tempMap[i][j].isWall == false) //look bottom
					{
						tempNode = tempMap[i][j+1];
						openList.push_back(tempNode);
					}
					if(tempMap[i+1][j-1].isWall == true) //look topleft
					{
						if(tempMap[i+2][j-1].isWall == false) //look above topleft
						{
							if(tempMap[i+1][j].isWall == false) //look top
							{
								if(tempMap[i+2][j].isWall == false) //look above top
								{
									//can jump topleft
									//set can jump?
									//tempNode = tempMap[i+2][j-1];
									//openList.push_back(tempNode);
								}
							}
						}
					}
					if(tempMap[i+1][j+1].isWall == true) //look topright
					{
						if(tempMap[i+2][j+1].isWall == false) //look above topright
						{
						
							if(tempMap[i+1][j].isWall == false) //look top
							{
								if(tempMap[i+2][j].isWall == false) //look above top
								{
									//can jump topright
									//tempNode = tempMap[i+2][j+1];
									//openList.push_back(tempNode);
								}
							}
								
						}
					}
					if(tempMap[i-1][j+1].isWall == false) //look bottomright
					{
						if(tempMap[i][j+1].isWall == false) //look right
						{
							//can drop bottomright
							tempNode = tempMap[i+2][j-1];
							openList.push_back(tempNode);
						}
					}
					if(tempMap[i-1][j-1].isWall == false)//look bottomleft
					{
						if(tempMap[i][j-1].isWall == false) //look left
						{
							//can drop bottomleft
						}
					}
					//start = currentNode;
					//closeList.push_back(start);
					//ChooseAPath();
					//if(start.x != end.x && start.y != end.y)
					//{
						//add in when completed to prevent infinite loop
						//SearchForPath(start);
					//}
				}
			}
		}
	}
}

float CAStarPathFinding :: DistanceToEnd(node checkingNode)
{
	return ( abs(end.x - checkingNode.x) + abs(end.y - checkingNode.y) );
}

void CAStarPathFinding :: FindPath()
{


	bool search = false;
	//SetUpGraph(10,10,tempMap[0][1],tempMap[0][8]);
	//add in when completed to prevent infinite loop
	while(!search)
	{
		SearchForPath();
		ChooseAPath();
		if(currentNode.index == end.index)
		{
			search = true;		
		}
	}
	
}

void CAStarPathFinding :: ChooseAPath()
{
	std :: vector<node> ::iterator it;
	//node bestNode;
	//bestNode.tileCost = 1000;
	float cost = 1000;
	int nodeIndex;
	
	for(it = openList.begin(); it!= openList.end();++it)
	{
		if(cost > it->tileCost + DistanceToEnd(*it))
		//bestNode = openList.at(it);
		{
			cost = it->tileCost + DistanceToEnd(*it);
			nodeIndex = it->index;
		}
	}

	for(it = openList.begin(); it!= openList.end();++it)
	{
		if(it->index == nodeIndex)
		{
			closeList.push_back(*it);
			currentNode = *it;
			it=openList.erase(it);
			break;
		}
	}

}