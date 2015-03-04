#pragma once
#include "BaseObject.h"
#include "Physics.h"
#include "HealthSystem.h"
#include "PointSystem.h"
#include "MVCtime.h"
#include <time.h>

class CCharacter : public CBaseObject
{
	public:
		CCharacter()	
		{
			pos = (0.f,0.f,0.f);
			dir = (0.f,0.f,0.f);
			isInvulnerable = false;
			//invultimer = clock();
		};
		virtual ~CCharacter(){};
		void Jump();
		void MoveLeft();
		void MoveRight();
		void SetPlayerID(int theID);
		bool GetIsInvulnerable();
		void SetIsInvulnerable(bool set);
		int refTime;

		CHealthSystem hp;
		CPointSystem* pts;

		string al;			//alpha;
		//clock_t invultimer;

		MVCTime * invulTimer;

		void PrintDebugInformation()
		{
			std::cout<<" pos"<<pos<<std::endl;
			std::cout<<" Top Left Point"<<TopLeft<<std::endl;
			std::cout<<" Bottom Right Point"<<BottomRight<<std::endl;
			std::cout<<" Top Left Cell Index"<<TopLeftCellIndex<<std::endl;
			std::cout<<" Bottom Right Cell Index"<<BottomRightCellIndex<<std::endl;
		};
	private:
		int playerID;	
		bool isInvulnerable;
		
};