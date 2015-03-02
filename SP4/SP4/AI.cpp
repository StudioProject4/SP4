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
			//foundPath = false;
			
		}
	}
	else if(pos.x == targetPosition.x && state == AI_PURSUE)
	{
		ChangeState(AI_IDLE);
		foundPath = false;
	}
	//else
	//{
	//	ChangeState(AI_IDLE);
	//}
	
}

void CAILogic :: FindPath ()
{
	std :: vector<node> ::iterator it;


	pathFinding.SetUpPath(pos,targetPosition);
	if(pathFinding.start.index != pathFinding.end.index)
	{
		pathFinding.FindPath();
		foundPath = true;
		for(it = pathFinding.closeList.begin(); it < pathFinding.closeList.end(); ++it)
			{
				cout << it->index << endl;
			}
	}
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

Vector3 CAILogic :: Update(Vector3 pos,CPhysics & thePhysics)
{
	this->pos = pos;

	StateCheck();

	if(state == AI_PURSUE)
	{
		if(foundPath == false)
		{
			pathFinding.closeList.clear();
			pathFinding.openList.clear();
			pathFinding.notCorrectPath.clear();
			FindPath();
		}
		else if(foundPath == true)
		{
			//pathMovementCounter = pathFinding.closeList.size();
			//pathFinding.closeList.at(pathMovementCounter);
			if(pos.x < pathFinding.closeList.at(pathMovementCounter).x)
			{
				//thePhysics.MoveSide(true);
				this->pos.x += 1;
			}
			if(pos.x > pathFinding.closeList.at(pathMovementCounter).x)
			{
				//thePhysics.MoveSide(false);
				this->pos.x -= 1;
			}
			if(pos.y < pathFinding.closeList.at(pathMovementCounter).y)
			{
				this->pos.y += 1;
			}
			if(pos.y > pathFinding.closeList.at(pathMovementCounter).y)
			{
				this->pos.y -= 1;
			}
			if(pos == Vector3(pathFinding.closeList.at(pathMovementCounter).x,pathFinding.closeList.at(pathMovementCounter).y,0))
			{
				pathMovementCounter++;
				if(pathMovementCounter >= pathFinding.closeList.size())
				{
					foundPath = false;
					pathMovementCounter = 0;
				}
			}
		}
		/*if(targetPosition.x > pos.x)
		{
			this->dir.x = 1;
			this->pos.x += 2;
		}
		else if(targetPosition.x < pos.x)
		{
			this->dir.x = -1;
			this->pos.x -= 2;	
		}
		else
		{
			this->dir.x = 0;
		}*/
		//FindPath();
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
			this->dir.x = 1;
			thePhysics.MoveSide(false);
		}
		else if (tempint == 2)
		{
			this->dir.x = -1;
			thePhysics.MoveSide(true);
		}
		else
		{
			this->dir.x = 0;
		}
	}
	return this->pos;
}

bool CAILogic :: Init()
{
	//FindPath();

	foundPath = false;
	pathMovementCounter = 0;

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