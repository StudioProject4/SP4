#pragma once
#include "Vector3.h"
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "Map.h"
#include "Physics.h"

struct node
{
	float x;
	float y;
	int tileCost;
	bool isNotWall;
	int index;
};

class CAStarPathFinding
{
	public:
	CAStarPathFinding();
	~CAStarPathFinding();

	//node tempMap[10][10]; // a temp map
	node ** tempMap;

	node currentNode;// use to keep track of current node
	node start;
	node end;

	float cost_so_far;
	float cost;

	int maxHorizontalTile;
	int maxVerticalTile;

	void SetUpGraph(CMap themap); // instantiate the map for pathfinding
	void SetUpPath(Vector3 startPosition,Vector3 endPosition);
	void SearchForPath(); // Find neighbouring nodes
	void ChooseAPath();
	float DistanceToEnd(node checkingNode); //heuristic
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

		Vector3 Update(Vector3 pos,CPhysics & thePhysics);
		bool Init();

		CAStarPathFinding pathFinding;
	private:
		bool foundPath;
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