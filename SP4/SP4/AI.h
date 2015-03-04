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
	bool canJump;
	bool canFall;
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
	void SetUpPath(Vector3 startPosition,Vector3 endPosition);// set start and end
	void SearchForPath(); // Find neighbouring nodes
	void ChooseAPath();// checking whether nodee exits in close list or wrong path list
	float DistanceToEnd(node checkingNode); //heuristic
	void FindPath(); // find the best path, the "main"
	void AddInPath(int index);// add into the close list
	int CheckForPath();// find for the best neightbouring nodes
	node GetCurrentNode(Vector3 myPosition,int choice);//set the current location as a node on the graph

	typedef std :: vector<node> TNodeVector;
	std :: vector<node> closeList; // tile to not consider / supposed correct path
	std :: vector<node> openList; // tile to consider
	std :: vector<node> notCorrectPath; // wrong path
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
		void OriginCheck();
		void FindPath();
		void IdleWanderRandomizer();
		void SetCharacterPos(Vector3 & enemyPos);
		void SetOriPos(Vector3 thePosition);
		Vector3 GetDir();
		void SetTag(string tag);
		void SetID(unsigned short id);

		Vector3 Update(Vector3 pos);//,CPhysics & thePhysics);
		bool Init();

		CAStarPathFinding pathFinding;
	private:
		bool outOfOrigin;
		bool foundPath;//to enemy
		bool foundOriPath;
		Vector3 pos;
		Vector3 dir;
		AIState state;
		Vector3 targetPosition;
		Vector3 enemyPos;
		float detectionRange;
		float movementSpeed;
		clock_t idleWanderTimer;
		clock_t wanderTimer;
		int pathMovementCounter;
		Vector3 oriPos;
		string tag;
		unsigned short id;

		//bool reachDest;
		//int wanderRefInt;
		//node wanderRefNode;
};