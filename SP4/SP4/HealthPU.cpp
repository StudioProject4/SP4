#include "HealthPU.h"


CHealthPU::CHealthPU(void)
{
}


CHealthPU::~CHealthPU(void)
{
}

bool CHealthPU::Render()
{
	theSprite->Render();
	return true;
}

bool CHealthPU::Init()
{
	name = "HealthAdd";
	tag = "HpAdd";
	genericTag = "PowerUp"; 
	
	theSprite = new CSprite(1,1,0);
	theSprite->LoadTGA("HealthCross.tga");

	return true;
}

bool CHealthPU::Update()
{
	return true;
}

bool CHealthPU::OnCollision(CBaseObject* a_obj)
{

	if(a_obj->genericTag = "Character")
	{
		if(a_obj->name = "GenericChineseKid")
		{
			if(this->active == true)
			{
				CCharacter* temp=(CCharacter*)a_obj;
				temp->hp.RecoverHealth();
				this->active = false;
				std::cout << "HEALTH ADDED" << std::endl;
			}else
			if(this->active == false)
			{
				std::cout << "taken" << std::endl;
			}

		}
		else
		if(a_obj->name = "GenericMalayKid")
		{
			if(this->active == true)
			{
				CCharacter* temp=(CCharacter*)a_obj;
				temp->hp.RecoverHealth();
				this->active = false;
				std::cout << "HEALTH ADDED" << std::endl;
			}else
			if(this->active == false)
			{
				std::cout << "taken" << std::endl;
			}
		}
	}

	return true;
}