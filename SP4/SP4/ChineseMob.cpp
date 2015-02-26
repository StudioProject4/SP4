#include "ChineseMob.h"
#include "Character.h"

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
	pos.y = phys.Update(pos).y;
	dir = AI.GetDir();
	pos.x = AI.Update(pos).x;
	return true;
}
bool CChineseMob :: Init()
{
	//AI.Init();

	name = "ChineseMob";
	tag = "ChineseMob";
	genericTag = "Enemy";

	theSprite = new CSprite(1,1,0);
	theSprite->LoadTGA("sonia2.tga");

	phys.Init(pos,Vector3(theSprite->GetImageSizeX(),theSprite->GetImageSizeY(),1));

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
	if(a_obj->genericTag = "Character")
	{
		if(a_obj->tag = "MalayFemale")
		{
			CCharacter* temp=(CCharacter*)a_obj;
			temp->hp.TakeDMG();
		}
	}
	return true;
}

void CChineseMob :: SetPos(Vector3 newPos)
{
	this->pos = newPos;
}