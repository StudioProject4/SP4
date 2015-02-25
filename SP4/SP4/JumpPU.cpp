#include "JumpPU.h"
#include "Physics.h"
CJumpPU::CJumpPU(void)
{
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

	return true;
}

bool CJumpPU::Init()
{
	name = "JumpUp";
	tag = "JpUp";
	genericTag = "PowerUp"; 

	theSprite = new CSprite(1,1,0);
	theSprite->LoadTGA("Jump.tga");

	return true;
}

bool CJumpPU::OnCollision(CBaseObject* a_obj)
{
	if(a_obj->genericTag = "Character")
	{
		if(a_obj->name = "GenericChineseKid")
		{
			//jump height
		}
		else
		if(a_obj->name = "GenericMalayKid")
		{
			
		}
	}

	return true;
}