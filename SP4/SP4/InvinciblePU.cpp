#include "InvinciblePU.h"


CInvinciblePU::CInvinciblePU(void)
	: InvinOnP1(false)
	, InvinOnP2(false)
{
}


CInvinciblePU::~CInvinciblePU(void)
{
}

bool CInvinciblePU::Update()
{

	return true;
}
	
bool CInvinciblePU::Render()
{
	theSprite->Render();
	return true;
}

bool CInvinciblePU::Init()
{
	name = "Invincible";
	tag = "Invin";
	genericTag = "PowerUp"; 

	theSprite = new CSprite(1,1,0);
	theSprite->LoadTGA("Invincible.tga");
	
	return true;
}

bool CInvinciblePU::OnCollision(CBaseObject* a_obj)
{

	if(a_obj->genericTag = "Character")
	{
		if(a_obj->name = "GenericChineseKid")
		{
			if(this->active == true)
			{
				CCharacter* Invintemp = (CCharacter*)a_obj;
				Invintemp->SetIsInvulnerable(true);
				this->active = false;
				std::cout << "INvulneravblee true " << std::endl;
			}else
			{
				std::cout << "Invulnerable TAKEN" << std::endl;
			}
		}
		else
		if(a_obj->name = "GenericMalayKid")
		{
		
			
		}
	}

	return true;
}