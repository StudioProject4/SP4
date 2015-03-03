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
	//if(a_obj->genericTag = "Character")
	//{
	//	//nothing
	//}
	//if(a_obj->genericTag = "Enemy")
	//{
	//	if(a_obj->tag = "ChineseMob")
	//	{
	//		if(clock() - invultimer > 5000)
	//		{
	//			hp.TakeDMG();
	//			std :: cout << "MalayFemale's HP : " << hp.GetHealth() << std :: endl;
	//		}
	//	}
	//}
	//if(a_obj->genericTag = "Powerup")
	//{
	//	//to be continued when powerups are done
	//}
	//if(a_obj->genericTag = "Obstacle")
	//{
	//	//to be continued when powerups are done
	//}
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