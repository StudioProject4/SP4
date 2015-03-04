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

	theSprite = new CSprite(3,4,2);
	theSprite->SetFrameSpeed(2);
	CImageManager::GetInstance()->RegisterTGA("guy2.tga");
	theSprite->OverrideTGATexture(CImageManager::GetInstance()->GetTGAImage("guy2.tga"));
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
		theSprite->Render();
	glPopMatrix();
	return true;
}