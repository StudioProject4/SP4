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

bool CHealthPU::OnCollision2(CBaseObject* a_obj,bool again)
{

	if(a_obj->genericTag == "Character")
	{
		if(this->active == true)
		{
			if(a_obj->tag == "ChineseMale")
			{
				if(this->active == true)
				{
					//CCharacter* temp = (CCharacter*)a_obj;
					CChineseMale* tempCM = (CChineseMale*)a_obj;
					tempCM->hp.RecoverHealth();
					this->active = false;
				}else
				if(this->active == false)
				{
					//std::cout << "taken" << std::endl;
				}

			}
			else
			if(a_obj->tag == "MalayFemale")
			{
				if(this->active == true)
				{
					CMalayFemale* tempMF = (CMalayFemale*)a_obj;
					tempMF->hp.RecoverHealth();
					this->active = false;
				}else
				if(this->active == false)
				{
					//std::cout << "taken" << std::endl;
				}
			}
		}else
		{
			//taken
		}
	}

	return true;
}