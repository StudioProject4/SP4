#pragma once
#include "BaseObject.h"
#include "Physics.h"

class CCharacter : public CBaseObject
{
	public:
		CCharacter()	
		{
			pos = (0,0,0);
			dir = (0,0,0);
		};
		virtual ~CCharacter(){};
		void Jump();
		void MoveLeft();
		void MoveRight();
		void SetPlayerID(int theID);

		CPhysics thePhysics;
	private:
		int playerID;
};