#include "MalayMob.h"

CMalayMob :: CMalayMob()
{
	Init();
}
CMalayMob :: ~CMalayMob()
{
	if(theSprite != NULL)
	{
		delete theSprite;
		theSprite = NULL;
	}
}
bool CMalayMob :: Update()
{
	dir = AI.GetDir();
	pos = AI.Update();
	return true;
}
bool CMalayMob :: Init()
{
	AI.Init();

	name = "MalayMob";
	tag = "MalayMob";
	genericTag = "Enemy";

	theSprite = new CSprite(1,1,0);
	theSprite->LoadTGA("sonia2.tga");

	return true;
}	
bool CMalayMob :: Reset()
{
	Init();
	return true;
}
bool CMalayMob :: CleanUp()
{
	return true;
}
bool CMalayMob :: Render()
{
	glPushMatrix();
	glTranslatef(pos.x,pos.y,pos.z);
	theSprite->Render();
	glPopMatrix();

	return true;
}

bool CMalayMob :: OnCollision(CBaseObject* a_obj)
{
	return true;
}