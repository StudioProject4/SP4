#pragma once
#include "BaseObject.h"
#include "Physics.h"
#include "HealthSystem.h"
#include "PointSystem.h"
#include <time.h>
#include "MVCtime.h"

class CCharacter : public CBaseObject
{
	public:
		CCharacter()	
		{
			pos = (0,0,0);
			dir = (0,0,0);
			isInvulnerable == false;
			invultimer = clock();
		};
		virtual ~CCharacter(){};
		void Jump();
		void MoveLeft();
		void MoveRight();
		void SetPlayerID(int theID);
		bool GetIsInvulnerable();
		void SetIsInvulnerable(bool set);

		CHealthSystem hp;
		clock_t invultimer;

		MVCTime * invulTimer;
	private:
		int playerID;	
		bool isInvulnerable;
};