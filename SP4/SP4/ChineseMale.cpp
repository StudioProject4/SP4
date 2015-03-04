#include "ChineseMale.h"
#include "Physics.h"

#include "ImageManager.h"

CChineseMale :: CChineseMale()
{
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
	Init();
	return true;
}

bool CChineseMale :: Update()
{
	pos=phys.Update(pos);
	//std::cout<<phys.Update(pos)<<std::endl
	if(GetIsInvulnerable() == true)
	{
		if(invulTimer->TestTime(refTime))
		{
			SetIsInvulnerable(false);
			//invulTimer->SetActive(false,refTime);
		
		}
	}
	theSprite->LiveOn();
	return true;
}

bool CChineseMale :: Init()
{
	name = "GenericChineseKid";
	tag = "ChineseMale";
	genericTag = "Character";

	theSprite = new CSprite(10,4,0);
	theSprite->SetFrameSpeed(2);
	CImageManager::GetInstance()->RegisterTGA("male.tga");
	theSprite->OverrideTGATexture(CImageManager::GetInstance()->GetTGAImage("male.tga"));
	//theSprite->LoadTGA("sonia2.tga");
	
	SetIsInvulnerable(false);

	phys.Init(pos,Vector3(theSprite->GetImageSizeX(),theSprite->GetImageSizeY()));
	this->UpdateObjectTopLeftAndBottomRightPoint(false);
	SetPlayerID(1);

	invulTimer = MVCTime :: GetInstance();
	refTime = invulTimer->PushNewTime(5000);
	
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
bool CChineseMale :: OnCollision2(CBaseObject* a_obj,bool again)
{
	return true;
}
bool CChineseMale :: Render()
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
	if(phys.vel.x == 0)
	{
		if(dir.x >= 0)
			theSprite->SetAnimationLayer(1);
		else
			theSprite->SetAnimationLayer(2);
	}
	else if(phys.vel.x > 0)
	{
		theSprite->SetAnimationLayer(0);
	}
	else if(phys.vel.x < 0)
	{
		theSprite->SetAnimationLayer(3);
	}
	theSprite->Render();
	glPopMatrix();
	return true;
}