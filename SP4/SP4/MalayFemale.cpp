#include "MalayFemale.h"

CMalayFemale :: CMalayFemale()
{
	Init();
}

CMalayFemale :: ~CMalayFemale()
{
	if(theSprite != NULL)
	{
		delete theSprite;
		theSprite = NULL;
	}
}

bool CMalayFemale :: Init(Vector3 newPos,Vector3 newDir,int entityID)
{
	pos = newPos;
	dir = newDir;
	id = entityID;
	
	return true;
}

bool CMalayFemale :: Update()
{
	return true;
}

bool CMalayFemale :: Init()
{
	glEnable(GL_TEXTURE_2D);
	name = "GenericMalayKid";
	tag = "MalayFemale";
	genericTag = "Character";
	theSprite = new CSprite(1,1,0);
	theSprite->LoadTGA("sonia2.tga");
	
	return true;
}

bool CMalayFemale :: Reset()
{
	return Init();
}

bool CMalayFemale :: CleanUp()
{
	return true;
}

bool CMalayFemale :: OnCollision(CBaseObject* a_obj)
{
	return true;
}

bool CMalayFemale :: Render()
{
	glPushMatrix();
	glTranslatef(pos.x,pos.y,pos.z);
	theSprite->Render();
	glPopMatrix();

	return true;
}

void CMalayFemale :: Jump()
{
	Vector3 temppos = pos;
	pos = (temppos.x, temppos.y + 5, temppos.z);
}
void CMalayFemale :: MoveLeft()
{
	Vector3 temppos = pos;
	temppos.x = temppos.x - 100;
	pos.x = temppos.x;
}
void CMalayFemale :: MoveRight()
{
	Vector3 temppos = pos;
	temppos.x = temppos.x + 100;
	pos.x = temppos.x;
}