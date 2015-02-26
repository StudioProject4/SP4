#include "PointsAddPU.h"


CPointsAddPU::CPointsAddPU(void)
{
}


CPointsAddPU::~CPointsAddPU(void)
{
}

bool CPointsAddPU::Update()
{

	return true;
}
	
bool CPointsAddPU::Render()
{
	
	theSprite->Render();
	return true;
}

bool CPointsAddPU::Init()
{
	name = "PointsAdd";
	tag = "PtAdd";
	genericTag = "PowerUp"; 

	theSprite = new CSprite(1,1,0);
	theSprite->LoadTGA("PointsAdd.tga");

	//points::getinstance()->addpoints
	return true;
}

bool CPointsAddPU::OnCollision(CBaseObject* a_obj)
{
	if(a_obj->genericTag = "Character")
	{
		if(this->active == true)
		{
			CCharacter* temp=(CCharacter*)a_obj;
			//temp->points.PointsReceive(50);
			
			this->active = false;
			std::cout << "POINTS ADDEDD" << std::endl;
		}else
		if(this->active == false)
		{
			std::cout << "Ptsfalse" << std::endl;
		}
	}

	return true;

}