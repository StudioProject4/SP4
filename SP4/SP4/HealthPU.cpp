#include "HealthPU.h"


CHealthPU::CHealthPU(void)
{
	Init();
}

CHealthPU::~CHealthPU(void)
{
	if(theSprite != NULL)
	{
		delete theSprite;
		theSprite = NULL;
	}
}

bool CHealthPU::Render()
{
	glPushMatrix();
	glTranslatef(pos.x,pos.y,pos.z);
	theSprite->Render();
	glPopMatrix();

	return true;
}

bool CHealthPU::Init()
{
	name = "HealthAdd";
	tag = "HpAdd";
	genericTag = "PowerUp"; 
	
	theSprite = new CSprite(1,1,0);
	theSprite->LoadTGA("HealthCross.tga");

	phys.Init(pos,Vector3(theSprite->GetImageSizeX(),theSprite->GetImageSizeY()));
	this->UpdateObjectTopLeftAndBottomRightPoint(false);

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
		if(this->active == true)
		{
			if(a_obj->tag = "ChineseMale")
			{
				/*if(this->active == true)
				{*/
					//CCharacter* temp = (CCharacter*)a_obj;
					CChineseMale* temp = (CChineseMale*)a_obj;
					temp->hp.RecoverHealth();
					this->active = false;
					std::cout << "HEALTH ADDED" << std::endl;
					std::cout << temp->hp.GetHealth() << std::endl;
				//}else
				//if(this->active == false)
				//{
				//	//std::cout << "taken" << std::endl;
				//}

			}
			else
			if(a_obj->tag = "MalayFemale")
			{
				/*if(this->active == true)
				{*/
					CCharacter* temp=(CCharacter*)a_obj;
					temp->hp.RecoverHealth();
					this->active = false;
					std::cout << "HEALTH ADDED" << std::endl;
				//}else
				//if(this->active == false)
				//{
				//	//std::cout << "taken" << std::endl;
				//}
			}
		}else
		{
			//taken
		}
	}

	return true;
}