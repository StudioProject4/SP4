#include "ChineseMob.h"

CChineseMob::CChineseMob()
{
	Init();
}
CChineseMob::~CChineseMob()
{
	if(theSprite != NULL)
	{
		delete theSprite;
		theSprite = NULL;
	}
}
bool CChineseMob :: Update()
{
	dir = AI.GetDir();
	pos = AI.Update();
	return true;
}
bool CChineseMob :: Init()
{
	AI.Init();

	name = "ChineseMob";
	tag = "ChineseMob";
	genericTag = "Enemy";

	theSprite = new CSprite(1,1,0);
	theSprite->LoadTGA("sonia2.tga");

	return true;
}
bool CChineseMob :: Reset()
{
	Init();
	return true;
}
bool CChineseMob :: CleanUp()
{
	return true;
}
bool CChineseMob :: Render()
{
	glPushMatrix();
	glTranslatef(pos.x,pos.y,pos.z);
	theSprite->Render();
	glPopMatrix();

	return true;
}

bool CChineseMob :: OnCollision(CBaseObject* a_obj)
{
	return true;
}