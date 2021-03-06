#include "Character.h"

void CCharacter :: Jump()
{
	phys.Jump();
	//Vector3 temppos = pos;
	//pos = (temppos.x, temppos.y + 5, temppos.z);
}
void CCharacter :: MoveLeft()
{
	//Vector3 temppos = pos;
	//temppos.x = temppos.x - 10;
	//pos.x = temppos.x;
	phys.MoveSide(false);
	dir.x = -1;
}
void CCharacter :: MoveRight()
{
	//Vector3 temppos = pos;
	//temppos.x = temppos.x + 10;
	//pos.x = temppos.x;
	phys.MoveSide(true);
	dir.x = 1;
}

void CCharacter :: SetPlayerID(int theID)
{
	playerID = theID;
}

void CCharacter :: SetIsInvulnerable(bool set)
{
	isInvulnerable = set;
	if(set==true)
	{
		MVCTime::GetInstance()->ResetTime(refTime);
	}
}

bool CCharacter :: GetIsInvulnerable()
{
	return isInvulnerable;
}