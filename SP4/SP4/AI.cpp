#include "AI.h"

CAILogic :: CAILogic()
{
	Init();
}

CAILogic :: ~CAILogic()
{
	
}

void CAILogic :: ChangeState(AIState state)
{
	this->state = state;
}

void CAILogic ::  StateCheck ()
{
	//check for change of states requirements
	if(state == AI_IDLE || state == AI_WANDER)
		IdleWanderRandomizer();
	DetectionCheck();
}

void CAILogic :: DetectionCheck ()
{
	//check for walls
	if((enemyPos.x <= (pos.x + detectionRange)) && (enemyPos.x >= (pos.x - detectionRange)))
	{
		//if(enemyPos.y == pos.y)
		{
			targetPosition = enemyPos;
			ChangeState(AI_PURSUE);
		}
	}
	else if(pos.x == targetPosition.x && state == AI_PURSUE)
	{
		ChangeState(AI_IDLE);
	}
	
}

void CAILogic :: FindPath ()
{
	
}

void CAILogic :: IdleWanderRandomizer ()
{
	if(clock() - idleWanderTimer > 5000)
	{
		int tempint = rand() % 2 + 1;
		idleWanderTimer = clock();

		if(tempint == 1)
		{
			ChangeState(AI_IDLE);
		}
		else if (tempint == 2)
		{
			ChangeState(AI_WANDER);
		}
	}
}

Vector3 CAILogic :: Update()
{
	StateCheck();

	if(state == AI_PURSUE)
	{
		if(targetPosition.x > pos.x)
		{
			dir.x = 1;
			pos.x += 2;
		}
		else if(targetPosition.x < pos.x)
		{
			dir.x = -1;
			pos.x -= 2;	
		}
		else
		{
			dir.x = 0;
		}
	}
	if(state == AI_WANDER)
	{
		static int tempint;
		if(clock() - wanderTimer > 5000)
		{
			wanderTimer = clock(); 
			tempint = rand() % 2 + 1;
		}

		if(tempint == 1)
		{
			dir.x = 1;
			pos.x = pos.x + 2;
		}
		else if (tempint == 2)
		{
			dir.x = -1;
			pos.x = pos.x - 2;
		}
		else
		{
			dir.x = 0;
		}
	}
	return pos;
}

bool CAILogic :: Init()
{
	pos = Vector3(0,-28.008003,0);
	dir = Vector3(0,0,0);

	wanderTimer = clock();
	idleWanderTimer = clock();
	state = AI_IDLE;
	detectionRange = 100;
	
	return true;
}

void CAILogic :: SetEnemyPos(Vector3 & enemyPos)
{
	this->enemyPos = enemyPos;
}

Vector3 CAILogic :: GetDir()
{
	return dir;
}