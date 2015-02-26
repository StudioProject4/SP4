#pragma once
#include "BaseObject.h"
#include "Physics.h"
#include "HealthSystem.h"
#include "PointSystem.h"
#include <time.h>

class CCharacter : public CBaseObject
{
	public:
		CCharacter()	
		{
			pos = (0,0,0);
			dir = (0,0,0);
			invultimer = clock();
		};
		virtual ~CCharacter(){};
		void Jump();
		void MoveLeft();
		void MoveRight();
		void SetPlayerID(int theID);

		CHealthSystem hp;
		clock_t invultimer;
	private:
		int playerID;	
};