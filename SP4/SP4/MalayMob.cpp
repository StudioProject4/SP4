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
	pos.y = phys.Update(pos).y;
	dir = AI.GetDir();
	pos.x = AI.Update(pos).x;
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
	
	phys.Init(pos,Vector3(theSprite->GetImageSizeX(),theSprite->GetImageSizeY(),1));

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
	//glScalef(10,10,1);
	theSprite->Render();
	glPopMatrix();

	return true;
}

bool CMalayMob :: OnCollision(CBaseObject* a_obj)
{
	if(a_obj->genericTag = "Character")
	{
		if(a_obj->tag = "ChineseMale")
		{
			a_obj->OnCollision(this);
		}
	}
	return true;
}

void CMalayMob :: SetPos(Vector3 newPos)
{
	this->pos = newPos;
}