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
		if(enemyPos.y == pos.y)
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

bool CAILogic :: Update()
{
	StateCheck();

	if(state == AI_PURSUE)
	{
		if(targetPosition.x > pos.x)
		{
			pos.x += 2;
		}
		if(targetPosition.x < pos.x)
		{
			pos.x -= 2;	
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
			pos.x = pos.x + 2;
		}
		else if (tempint == 2)
		{
			pos.x = pos.x - 2;
		}
	}
	return true;
}

bool CAILogic :: Init()
{
	wanderTimer = clock();
	idleWanderTimer = clock();
	state = AI_IDLE;
	detectionRange = 100;
	
	name = "GenericMalayKid";
	tag = "MalayFemale";
	genericTag = "Character";
	
	theSprite = new CSprite(1,1,0);
	theSprite->LoadTGA("sonia2.tga");
	
	return true;
}

bool CAILogic :: Reset()
{
	return Init();
}

bool CAILogic :: CleanUp()
{
	return true;
}

bool CAILogic :: OnCollision(CBaseObject* a_obj)
{
	return true;
}

bool CAILogic :: Render()
{
	glPushMatrix();
	glTranslatef(pos.x,pos.y,pos.z);
	theSprite->Render();
	glPopMatrix();

	return true;
}

void CAILogic :: SetEnemyPos(Vector3 & enemyPos)
{
	this->enemyPos = enemyPos;
}