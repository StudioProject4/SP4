#include "Door.h"
#include "Sprite.h"
#include "TriggerBase.h"


CDoor::CDoor(void):
sprite(NULL)
{
}


CDoor::~CDoor(void)
{
}

bool CDoor::Init(Vector3 pos,Vector3 size)
{
	this->pos=pos;
	sprite=new CSprite(1);
	this->phys.size=Vector3(sprite->GetImageSizeX(),sprite->GetImageSizeY());
	
	triggered=false;

	return true;
}

bool CDoor::Render()
{
	if(active)
	{
		glPushMatrix();
		glTranslatef(pos.x,pos.y,pos.z);
		sprite->Render();
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
		active=false;
	}
	else
	{
		active=true;
	}
}

bool CDoor::Update()
{
	return true;
}

bool CDoor::OnCollision(CBaseObject* obj)
{
	return false;
}