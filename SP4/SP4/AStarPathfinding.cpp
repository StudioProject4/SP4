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
	//		tempMap[i][j].isNotWall = false;
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
			if(theMap.theScreenMap[i][j] == 0)
			{
				tempMap[i][j].isNotWall = false; // a wall
			}
			else
			{
				tempMap[i][j].isNotWall = true; // not a wall
			}
			tempMap[i][j].index = ((i * maxHorizontalTile) + j);
		}
	}
}

void CAStarPathFinding :: SetUpPath(Vector3 startPosition,Vector3 endPosition)
{
		for(int i = 0 ; i < this->maxVerticalTile ; i++)
		{
			for(int j = 0 ; j < this->maxHorizontalTile ; j++)
			{
				if((startPosition.x > (tempMap[i][j].x - TILE_SIZE)) && (startPosition.x < (tempMap[i][j].x + TILE_SIZE)) && (startPosition.y > (tempMap[i][j].y - TILE_SIZE)) && (startPosition.y < (tempMap[i][j].y + TILE_SIZE)))
				{
					start = tempMap[i][j];
				}
				if((endPosition.x >  (tempMap[i][j].x - TILE_SIZE)) && (endPosition.x < (tempMap[i][j].x + TILE_SIZE)) && (endPosition.y > (tempMap[i][j].y - TILE_SIZE)) && (endPosition.y < (tempMap[i][j].y + TILE_SIZE)))
				{
					end = tempMap[i][j];
				}
			}
		}
		//if(start.isNotWall == false)
		//{
		//node start,node end
		//this->start = start;
		//this->end = end;
			this->currentNode = start;

			closeList.push_back(start);
		//}
}

void CAStarPathFinding :: SearchForPath()
{
		std :: vector<node> ::iterator it;
		
	for(int i = 0 ; i < this->maxVerticalTile ; i++)
	{
		for(int j = 0 ; j < this->maxHorizontalTile ; j++)
		{

			if(tempMap[i][j].x == currentNode.x && tempMap[i][j].y == currentNode.y) // if currentnode is found
			{
				/*bool inOpenList = false;
				for(it = openList.begin(); it!= openList.end();++it)
						{
							if(it->index == tempNode.index)
							{
								inOpenList = true;
							}
						}
						if(inOpenList = true;)
						{	}*/
				node tempNode;
				//if(tempMap[i-1][j].isNotWall == true) //not in air
				{
					if(tempMap[i][j-1].isNotWall == true) //look left
					{
						tempNode = tempMap[i][j-1];
						openList.push_back(tempNode);
					}
					if(tempMap[i][j+1].isNotWall == true) //look right
					{
						tempNode = tempMap[i][j+1];
						openList.push_back(tempNode);
					}
					if(tempMap[i-1][j].isNotWall == true) //look top
					{
						tempNode = tempMap[i-1][j];
						openList.push_back(tempNode);
					}
					if(tempMap[i+1][j].isNotWall == true) //look bottom
					{
						tempNode = tempMap[i+1][j];
						openList.push_back(tempNode);
					}
					if(tempMap[i-1][j-1].isNotWall == false) //look topleft
					{
						if(tempMap[i-2][j-1].isNotWall == true) //look above topleft
						{
							if(tempMap[i-1][j].isNotWall == true) //look top
							{
								if(tempMap[i-2][j].isNotWall == true) //look above top
								{
									//can jump topleft
									//set can jump?
									//tempNode = tempMap[i+2][j-1];
									//openList.push_back(tempNode);
								}
							}
						}
					}
					if(tempMap[i-1][j+1].isNotWall == false) //look topright
					{
						if(tempMap[i-2][j+1].isNotWall == true) //look above topright
						{
						
							if(tempMap[i-1][j].isNotWall == true) //look top
							{
								if(tempMap[i-2][j].isNotWall == true) //look above top
								{
									//can jump topright
									//tempNode = tempMap[i+2][j+1];
									//openList.push_back(tempNode);
								}
							}
								
						}
					}
					if(tempMap[i+1][j+1].isNotWall == true) //look bottomright
					{
						if(tempMap[i][j+1].isNotWall == true) //look right
						{
							//can drop bottomright
							//tempNode = tempMap[i+2][j-1];
							//openList.push_back(tempNode);
						}
					}
					if(tempMap[i+1][j-1].isNotWall == true)//look bottomleft
					{
						if(tempMap[i][j-1].isNotWall == true) //look left
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
	std :: vector<node> ::iterator it;
	int searchCounter = 0;
	int searchAttempts = 0;
	bool search = false;
	cost_so_far = 0;
	//SetUpGraph(10,10,tempMap[0][1],tempMap[0][8]);
	//add in when completed to prevent infinite loop
	while(!search )
	{
		searchCounter++;
		SearchForPath();
		ChooseAPath();
		if(currentNode.index == end.index || searchCounter > 299)
		{
			if(currentNode.index != end.index && searchAttempts < 2)
			{
				notCorrectPath = closeList;
				/*for(it = closeList.begin(); it!= closeList.end();++it)
				{
					if(it->index != start.index)
					closeList.erase(it);
				}*/
				closeList.clear();
				searchAttempts ++;
				searchCounter = 0;
				currentNode = start;
			}
			else
			search = true;		
		}
	}
	
}

void CAStarPathFinding :: ChooseAPath()
{
	std :: vector<node> ::iterator it;
	std :: vector<node> ::iterator it2;
	std :: vector<node> ::iterator it3;

	cost = 1000;
	int nodeIndex;
	//node bestNode;
	//bestNode.tileCost = 1000;
	
	nodeIndex = CheckForPath();

	for(it = openList.begin(); it!= openList.end();++it)
	{
		if(it->index == nodeIndex)
		{
			bool inCloseList = false;
			bool inWrongList = false;
			for(it2 = closeList.begin(); it2!= closeList.end();++it2)
			{
				if(it2->index == nodeIndex)
				{
					inCloseList = true;
				}
				
			}
			for(it3 = notCorrectPath.begin(); it3!= notCorrectPath.end();++it3)
			{
				if(it3->index == nodeIndex)
				{
					inWrongList = true;
				}
			}
			if(inCloseList == false && inWrongList == false)
			{
				AddInPath(nodeIndex);
				break;
			}
			else
			{
				it = openList.erase(it);
				ChooseAPath();
				break;
			}
		}
	}

}

void CAStarPathFinding :: AddInPath(int index)
{
	std :: vector<node> ::iterator it;
	for(it = openList.begin(); it!= openList.end();++it)
	{
		if(it->index == index)
		{
			closeList.push_back(*it);
			currentNode = *it;
			it=openList.erase(it);
			break;
		}
	}
}

int CAStarPathFinding :: CheckForPath()
{
	std :: vector<node> ::iterator it;

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

	return nodeIndex;
}