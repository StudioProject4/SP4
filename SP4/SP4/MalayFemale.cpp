#include "MalayFemale.h"
#include "ImageManager.h"

CMalayFemale :: CMalayFemale()
{
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
	Init();
	return true;
}

bool CMalayFemale :: Update()
{
	pos = phys.Update(pos);
	if(GetIsInvulnerable() == true)
	{
		if(invulTimer->TestTime(refTime))
		{
			SetIsInvulnerable(false);
			//invulTimer->SetActive(false,refTime);
		}
	}
	return true;
}

bool CMalayFemale :: Init()
{
	name = "GenericMalayKid";
	tag = "MalayFemale";
	genericTag = "Character";

	theSprite = new CSprite(1,1,0);
	theSprite->OverrideTGATexture(CImageManager::GetInstance()->GetTGAImage("sonia2.tga"));
	//theSprite->LoadTGA("sonia2.tga");

	phys.Init(pos,Vector3(theSprite->GetImageSizeX(),theSprite->GetImageSizeY()));
	this->UpdateObjectTopLeftAndBottomRightPoint(false);
	SetPlayerID(2);

	SetIsInvulnerable(false);

	invulTimer = MVCTime :: GetInstance();
	refTime = invulTimer->PushNewTime(5000);
	
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

bool CMalayFemale :: OnCollision2(CBaseObject* a_obj,bool again)
{
	return true;
}

bool CMalayFemale :: Render()
{
	
	glPushMatrix();

	glTranslatef(pos.x,pos.y,pos.z);
	if(GetIsInvulnerable() == true)
	{
		theSprite->SetAlpha(0.5f);
	}
	else
	{
		theSprite->SetAlpha(1.0f);
	}
	theSprite->Render();

	glPopMatrix();

	return true;
}