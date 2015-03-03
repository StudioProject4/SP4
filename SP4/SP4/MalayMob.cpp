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
	//pos.x = 
	pos = AI.Update(pos,phys);
	/*if(AI.state == AI_WANDER)
	{
		pos.x = phys.Update(pos).x;
	}*/
	return true;
}
bool CMalayMob :: Init()
{
	name = "MalayMob";
	tag = "MalayMob";
	genericTag = "Enemy";

	theSprite = new CSprite(1,1,0);
	theSprite->LoadTGA("rockyground.tga");
	
	phys.Init(pos,Vector3(theSprite->GetImageSizeX(),theSprite->GetImageSizeY(),1));
	this->UpdateObjectTopLeftAndBottomRightPoint(false);

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

bool CMalayMob :: OnCollision2(CBaseObject* a_obj)
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

void CMalayMob :: SetUpMap(CMap theMap)
{
	AI.pathFinding.SetUpGraph(theMap);
}