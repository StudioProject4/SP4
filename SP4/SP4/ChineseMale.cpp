#include "ChineseMale.h"
#include "Physics.h"

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
	pos = thePhysics.Update(pos);
	return true;
}

bool CChineseMale :: Init()
{
	name = "GenericChineseKid";
	tag = "ChineseMale";
	genericTag = "Character";

	theSprite = new CSprite(1,1,0);
	theSprite->LoadTGA("sonia2.tga");

	thePhysics.Init(pos,Vector3(theSprite->GetImageSizeX(),theSprite->GetImageSizeY(),1));

	SetPlayerID(1);

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