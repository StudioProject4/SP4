#include "JumpPU.h"
#include "Physics.h"
CJumpPU::CJumpPU(void)
{
	Init();
}


CJumpPU::~CJumpPU(void)
{
}

bool CJumpPU::Update()
{

	return true;
}
	
bool CJumpPU::Render()
{
	glPushMatrix();
	glTranslatef(pos.x, pos.y, 0);
	theSprite->Render();
	glPopMatrix();

	return true;
}

bool CJumpPU::Init()
{
	name = "JumpUp";
	tag = "JpUp";
	genericTag = "PowerUp"; 

	theSprite = new CSprite(1,1,0);
	theSprite->LoadTGA("Jump.tga");

	phys.Init(pos,Vector3(theSprite->GetImageSizeX(),theSprite->GetImageSizeY()));
	this->UpdateObjectTopLeftAndBottomRightPoint(false);
	return true;
}

bool CJumpPU::OnCollision2(CBaseObject* a_obj)
{
	if(a_obj->genericTag = "Character")
	{
		if(a_obj->name = "GenericChineseKid")
		{
			//jump height
			if(this->active == true)
			{
				this->active = false;
			}else
			{
				//std::cout << "taken" << std::endl;
			}

		}
		else
		if(a_obj->name = "GenericMalayKid")
		{
			
		}
	}

	return true;
}