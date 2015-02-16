#include "Character.h"

CCharacter :: CCharacter()
{
	pos = (0,0,0);
	dir = (0,0,0);
}
CCharacter :: ~CCharacter()
{
	
}
void CCharacter :: Jump()
{
	Vector3 temppos = pos;
	pos = (temppos.x, temppos.y + 5, temppos.z);
}
void CCharacter :: Moveleft(float deltatime, float speed)
{
	Vector3 temppos = pos;
	pos = (temppos.x - (speed * deltatime), temppos.y, temppos.z);
}
void CCharacter :: Moveright(float deltatime, float speed)
{
	Vector3 temppos = pos;
	pos = (temppos.x + (speed * deltatime), temppos.y, temppos.z);
}
