#pragma once
#include "Vector3.h"
#include "BaseObject.h"
#include "Sprite.h"
#include <stdlib.h>
#include <time.h>

class CAILogic : public CBaseObject
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

		bool Update();
		bool Init();
		bool Reset();
		bool CleanUp();
		bool Render();

		bool OnCollision(CBaseObject* a_obj);

	private:
		AIState state;
		Vector3 targetPosition;
		Vector3 enemyPos;
		float detectionRange;
		float movementSpeed;
		CSprite * theSprite;
		clock_t idleWanderTimer;
		clock_t wanderTimer;
};