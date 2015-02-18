#include "Character.h"

void CCharacter :: Jump()
{
	thePhysics.Jump();
	//Vector3 temppos = pos;
	//pos = (temppos.x, temppos.y + 5, temppos.z);
}
void CCharacter :: MoveLeft()
{
	Vector3 temppos = pos;
	temppos.x = temppos.x - 100;
	pos.x = temppos.x;
}
void CCharacter :: MoveRight()
{
	Vector3 temppos = pos;
	temppos.x = temppos.x + 100;
	pos.x = temppos.x;
}