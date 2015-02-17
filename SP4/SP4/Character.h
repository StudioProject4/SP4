#pragma once
#include "BaseObject.h"

class CCharacter : public CBaseObject
{
	public:
		CCharacter()	
		{
			pos = (0,0,0);
			dir = (0,0,0);
		};
		virtual ~CCharacter(){};
		virtual void Jump() = 0 ;
		virtual void MoveLeft() = 0 ;
		virtual void MoveRight() = 0 ;
	private:
		int PlayerID;
};