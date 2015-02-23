#pragma once
#include "Vector3.h"
#include <stdlib.h>
#include <time.h>

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

		Vector3 Update();
		bool Init();

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