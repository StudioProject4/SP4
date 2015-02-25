#pragma once
#include "Vector3.h"
#include <stdlib.h>
#include <time.h>
#include <vector>

struct node
{
	float x;
	float y;
	int tileCost;
	bool isWall;
};

class CBFS
{
	public:

		CBFS();
		~CBFS();

		node tempmap[10][10];
		std :: vector<node> locations; // vectors of positions
		std :: vector<node> badPath;
		std :: vector<node> path;

		void SetUpGraph();
		void SearchNeighbours(node theNode); // search for poistions it links to 
		void SearchForPath(node start,node end); // search for a path from start to end
};

class CA_Star
{
	public:
		CA_Star();
		~CA_Star();
		CBFS search;

		std :: vector<node>bestPath; 

		float DistanceToEnd(node start,node end);
		void SearchBestPath(node start,node end,vector<node>locationList);
};

class CAStarPathFinding
{
	public:
	CAStarPathFinding();
	~CAStarPathFinding();

	node tempMap[10][10]; // a temp map

	node tempParentNode;// use to keep track of previous node
	node start;
	node end;

	int maxHorizontalTile;
	int maxVerticalTile;

	void SetUpGraph(int maxHorizontalTile, int maxVerticalTile,node start,node end); // instantiate the map for pathfinding
	void SearchForPath(node currentNode); // Find neighbouring nodes
	void ChooseAPath();
	float DistanceToEnd(); //heuristic
	void FindPath(); // find the best path, the "main"

	typedef std :: vector<node> TNodeVector;
	std :: vector<node> closeList; // tile to not consider
	std :: vector<node> openList; // tile to consider
	std :: vector<node> correctPath; // comfirmed path
};

class CAILogic
{
	enum AIState
	{
		AI_IDLE,
		AI_WANDER,
		AI_PURSUE
	};

	public:
		CAILogic();
		~CAILogic();
		void ChangeState(AIState state);
		void StateCheck();
		void DetectionCheck();
		void FindPath();
		void IdleWanderRandomizer();
		void SetEnemyPos(Vector3 & enemyPos);
		Vector3 GetDir();

		Vector3 Update(Vector3 pos);
		bool Init();

		//CA_Star pathfinding;
	private:
		Vector3 pos;
		Vector3 dir;
		AIState state;
		Vector3 targetPosition;
		Vector3 enemyPos;
		float detectionRange;
		float movementSpeed;
		clock_t idleWanderTimer;
		clock_t wanderTimer;
};