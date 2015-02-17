#pragma once
#include "BaseObject.h"

class CCharacter : public CBaseObject
{
	public:
		CCharacter();
		~CCharacter();
		void Jump();
		void Moveleft(float DeltaTime ,float speed);
		void Moveright(float DeltaTime ,float speed);
	private:
		int PlayerID;
};