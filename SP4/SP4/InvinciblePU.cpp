#include "InvinciblePU.h"


CInvinciblePU::CInvinciblePU(void)
{
	Init();
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
	glPushMatrix();
	glTranslatef(pos.x, pos.y, 0);
	theSprite->Render();
	glPopMatrix();
	return true;
}

bool CInvinciblePU::Init()
{
	name = "Invincible";
	tag = "Invin";
	genericTag = "PowerUp"; 

	theSprite = new CSprite(1,1,0);
	theSprite->LoadTGA("Invincible.tga");

	phys.Init(pos,Vector3(theSprite->GetImageSizeX(),theSprite->GetImageSizeY()));
	this->UpdateObjectTopLeftAndBottomRightPoint(false);
	return true;
}

bool CInvinciblePU::OnCollision2(CBaseObject* a_obj,bool again)
{

	if(a_obj->genericTag = "Character")
	{
		if(this->active == true)
		{
			CCharacter* Invintemp = (CCharacter*)a_obj;
			Invintemp->SetIsInvulnerable(true);
			Invintemp->invulTimer->SetActive(true, Invintemp->refTime);
			Invintemp->invulTimer->SetLimit(Invintemp->refTime, 5000);
			this->active = false;
			std::cout << "INvulneravblee true " << std::endl;
		}else
		if(this->active == false)
		{
			//std::cout << "Invulnerable TAKEN" << std::endl;
		}
	}

	return true;
}