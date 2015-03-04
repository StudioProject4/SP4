#include "CodeDefination.h"
#ifdef NETWORK_CODE
#include "RakNet\WindowsIncludes.h"
#include "RakNet\RakPeerInterface.h"
#include "RakNet\BitStream.h"
#include "MyMsgIDs.h"
#endif
#include "AI.h"
#include "MVCtime.h"

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
	//if(state == AI_IDLE || state == AI_WANDER)
	//	IdleWanderRandomizer();
	OriginCheck();
	DetectionCheck();
}

void CAILogic :: OriginCheck()
{
	if(state == AI_IDLE)
		if((this->pos.x < oriPos.x - detectionRange) || (this->pos.x > oriPos.x + detectionRange) || (this->pos.y < oriPos.y - detectionRange) || (this->pos.x > oriPos.y + detectionRange) )
		{
			outOfOrigin = true;
				if(clock() - wanderTimer > 10000)
				{
					state = AI_WANDER;
					wanderTimer = clock(); 
				}	
		}
	if((pos.x > oriPos.x-1)
				&& (pos.x < oriPos.x+1)
				&& (pos.y > oriPos.y-1)
				&& (pos.y < oriPos.y+1)
				&& state == AI_WANDER)
	{
		outOfOrigin = false;
	}
}

void CAILogic :: DetectionCheck ()
{
	//check for walls
	if((enemyPos.x <= (pos.x + detectionRange)) && (enemyPos.x >= (pos.x - detectionRange)))
	{
		if((enemyPos.y <= (pos.y + detectionRange)) && (enemyPos.y >= (pos.y - detectionRange)))
		{
			targetPosition = enemyPos;
			ChangeState(AI_PURSUE);
			//foundPath = false;		
		}
	}
	else if((pos.x > pathFinding.end.x-1)
				&& (pos.x < pathFinding.end.x+1)
				&& (pos.y > pathFinding.end.y-1)
				&& (pos.y < pathFinding.end.y+1)
				&& state == AI_PURSUE)
	{
		ChangeState(AI_IDLE);
		foundPath = false;
		//reachDest = true;
	}
	//else
	//{
	//	ChangeState(AI_IDLE);
	//}
	
}

void CAILogic :: FindPath ()
{
	std :: vector<node> ::iterator it;

	if(state == AI_PURSUE)
		pathFinding.SetUpPath(pos,targetPosition);
	else if(state == AI_WANDER)
		pathFinding.SetUpPath(pos,oriPos);
	if(pathFinding.start.index != pathFinding.end.index)
	{
		pathFinding.FindPath();
		if(state == AI_PURSUE)
			foundPath = true;
		else if(state == AI_WANDER)
			foundOriPath = true;
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

Vector3 CAILogic :: Update(Vector3 pos)//CPhysics & thePhysics)
{
	this->pos = pos;
	Vector3 tempPos=pos;
	StateCheck();

	float delta=MVCTime::GetInstance()->GetDelta();
	if(state == AI_IDLE && outOfOrigin == false)
	{
		wanderTimer = clock(); 
	}
	if(state == AI_PURSUE)
	{
		if(foundPath == false)
		{
			pathFinding.closeList.clear();
			pathFinding.openList.clear();
			pathFinding.notCorrectPath.clear();
			FindPath();
			pathMovementCounter = 0; 
		}
		else if(foundPath == true)
		{

			if(pos.x < pathFinding.closeList.at(pathMovementCounter).x)
			{
				this->pos.x += 60*delta;
			}
			if(pos.x > pathFinding.closeList.at(pathMovementCounter).x)
			{
				this->pos.x -= 60*delta;
			}
			if(pos.y < pathFinding.closeList.at(pathMovementCounter).y)
			{
				this->pos.y += 60*delta;
				//thePhysics.Jump();
			}
			if(pos.y > pathFinding.closeList.at(pathMovementCounter).y)
			{
				this->pos.y -= 60*delta;
			}
			if((pos.x > pathFinding.closeList.at(pathMovementCounter).x-1)
				&& (pos.x < pathFinding.closeList.at(pathMovementCounter).x+1)
				&& (pos.y > pathFinding.closeList.at(pathMovementCounter).y-1)
				&& (pos.y < pathFinding.closeList.at(pathMovementCounter).y+1) )
			{
				pathMovementCounter++;
				if(pathMovementCounter >= pathFinding.closeList.size())
				{
					foundPath = false;
					pathMovementCounter = 1;
				}
			}
		}
	}
	if(state == AI_WANDER)
	{
		if(foundOriPath == false)
		{
			pathFinding.closeList.clear();
			pathFinding.openList.clear();
			pathFinding.notCorrectPath.clear();
			FindPath();
			pathMovementCounter = 1;
		}
		else if(foundOriPath == true)
		{
			if(pos.x < pathFinding.closeList.at(pathMovementCounter).x)
			{
				this->pos.x += 60*delta;
			}
			if(pos.x > pathFinding.closeList.at(pathMovementCounter).x)
			{
				this->pos.x -= 60*delta;
			}
			if(pos.y < pathFinding.closeList.at(pathMovementCounter).y)
			{
				this->pos.y += 60*delta;
			}
			if(pos.y > pathFinding.closeList.at(pathMovementCounter).y)
			{
				this->pos.y -= 60*delta;
			}
			if((pos.x > pathFinding.closeList.at(pathMovementCounter).x-1)
				&& (pos.x < pathFinding.closeList.at(pathMovementCounter).x+1)
				&& (pos.y > pathFinding.closeList.at(pathMovementCounter).y-1)
				&& (pos.y < pathFinding.closeList.at(pathMovementCounter).y+1) )
			{
				pathMovementCounter++;
				if(pathMovementCounter >= pathFinding.closeList.size())
				{
					foundOriPath = false;
					pathMovementCounter = 1;
				}
			}
		}

	}
	return this->pos;
}

bool CAILogic :: Init()
{
	//FindPath();
	
	//reachDest = true;
	foundPath = false;
	pathMovementCounter = 1;
	//wanderRefInt = 0;

	//origin position checking variable init
	oriPos = Vector3(0,0,0);
	outOfOrigin = false;
	foundOriPath = false;

	pos = Vector3(0,0,0);
	dir = Vector3(0,0,0);

	wanderTimer = clock();
	idleWanderTimer = clock();
	state = AI_IDLE;
	detectionRange = 100;
	
	return true;
}

void CAILogic :: SetCharacterPos(Vector3 & enemyPos)
{
	this->enemyPos = enemyPos;
}

Vector3 CAILogic :: GetDir()
{
	return dir;
}

void CAILogic :: SetOriPos (Vector3 thePosition)
{
	oriPos = thePosition;
}

void CAILogic :: SetTag(string tag)
{
	this->tag = tag;
}

void CAILogic :: SetID(unsigned short id)
{
	this->id = id;
}