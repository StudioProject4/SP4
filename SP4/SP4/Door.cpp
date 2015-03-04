#include "Door.h"
#include "Sprite.h"
#include "TriggerBase.h"

#include "ImageManager.h"


CDoor::CDoor(void)//:
//theSprite(NULL)
:color(1,1,1)
{
}


CDoor::~CDoor(void)
{
}

bool CDoor::Init(Vector3 pos,Vector3 size)
{
	tag= "CDoor";
	genericTag = "CObstacleBase";
	name = "door";

	this->pos=pos;
	theSprite=new CSprite(1);

	CImageManager::GetInstance()->RegisterTGA("blockage.tga");
	theSprite->OverrideTGATexture(CImageManager::GetInstance()->GetTGAImage("blockage.tga"));

	this->phys.size=Vector3(theSprite->GetImageSizeX(),theSprite->GetImageSizeY());
	this->UpdateObjectTopLeftAndBottomRightPoint(false);
	triggered=false;

	return true;
}

bool CDoor::Render()
{
	if(active&&!triggered)
	{
		glPushMatrix();
		glTranslatef(pos.x,pos.y,pos.z);
		theSprite->Render();
		glPopMatrix();
	}
	return true;
}

void CDoor::AddTrigger(CTriggerBase* nTrigger)
{
	if(nTrigger!=NULL)
		triggerList.push_back(nTrigger);
}

void CDoor::Trigger()
{
	for(vector<CTriggerBase*>::iterator it=triggerList.begin();it!=triggerList.end();++it)
	{
		(*it)->color=color;
		if(!(*it)->GetTriggered())
		{
			if(triggered=true)
			{
				triggered=false;
				TriggerEvent();
			}
			return;
		}
	}
	triggered=true;
	TriggerEvent();
}

void CDoor::TriggerEvent()
{
	if(triggered)
	{
		//active=false;
	}
	else
	{
		//active=true;
	}
}

bool CDoor::Update()
{
	return true;
}

bool CDoor::OnCollision2(CBaseObject* obj,bool again)
{
	if(active&&!triggered)
	{
		if(obj->phys.vel.Dot(obj->pos-pos)<0)
			obj->phys.vel.x=0;
	}
	return false;
}