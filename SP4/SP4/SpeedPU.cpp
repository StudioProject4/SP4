#include "SpeedPU.h"


CSpeedPU::CSpeedPU(void)
{
	Init();
}


CSpeedPU::~CSpeedPU(void)
{
}

bool CSpeedPU::Update()
{

	return true;
}
	
bool CSpeedPU::Render()
{
	glPushMatrix();

		glTranslatef(pos.x,pos.y,0);
		theSprite->Render();

	glPopMatrix();
	return true;
}

bool CSpeedPU::Init()
{
	name = "SpeedUp";
	tag = "SpdUp";
	genericTag = "PowerUp"; 
	
	theSprite = new CSprite(1,1,0);
	theSprite->LoadTGA("SpeedUp.tga");
	phys.Init(pos,Vector3(theSprite->GetImageSizeX(),theSprite->GetImageSizeY()));
	this->UpdateObjectTopLeftAndBottomRightPoint(false);
	return true;
}

bool CSpeedPU::OnCollision(CBaseObject* a_obj)
{

	if(a_obj->genericTag = "Character")
	{
		if(a_obj->name = "GenericChineseKid")
		{
			//speed up
		}
		else
		if(a_obj->name = "GenericMalayKid")
		{

		}
	}

	return true;
}