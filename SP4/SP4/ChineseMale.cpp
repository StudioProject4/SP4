#include "ChineseMale.h"

CChineseMale :: CChineseMale()
{
	Init();
}

CChineseMale :: ~CChineseMale()
{
	if(theSprite != NULL)
	{
		delete theSprite;
		theSprite = NULL;
	}
}

bool CChineseMale :: Init(Vector3 newPos,Vector3 newDir,int entityID)
{
	pos = newPos;
	dir = newDir;
	id = entityID;
	
	return true;
}

bool CChineseMale :: Update()
{
	return true;
}

bool CChineseMale :: Init()
{
	glEnable(GL_TEXTURE_2D);
	name = "GenericChineseKid";
	tag = "ChineseMale";
	genericTag = "Character";
	theSprite = new CSprite(1,1,0);
	theSprite->LoadTGA("sonia2.tga");

	return true;
}

bool CChineseMale :: Reset()
{
	return Init();
}

bool CChineseMale :: CleanUp()
{
	return true;
}
bool CChineseMale :: OnCollision(CBaseObject* a_obj)
{
	return true;
}
bool CChineseMale :: Render()
{
	glPushMatrix();
	glTranslatef(pos.x,pos.y,pos.z);
	theSprite->Render();
	glPopMatrix();

	return true;
}

void CChineseMale :: Jump()
{
	Vector3 temppos = pos;
	pos = (temppos.x, temppos.y + 5, temppos.z);
}
void CChineseMale :: MoveLeft()
{
	Vector3 temppos = pos;
	temppos.x = temppos.x - 100;
	pos.x = temppos.x;
}
void CChineseMale :: MoveRight()
{
	Vector3 temppos = pos;
	temppos.x = temppos.x + 100;
	pos.x = temppos.x;
}