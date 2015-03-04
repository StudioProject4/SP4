#include "PointsAddPU.h"


CPointsAddPU::CPointsAddPU(void)
{
	Init();
}


CPointsAddPU::~CPointsAddPU(void)
{
	if(theSprite != NULL)
	{
		delete theSprite;
		theSprite = NULL;
	}
}

bool CPointsAddPU::Update()
{

	return true;
}
	
bool CPointsAddPU::Render()
{
	glPushMatrix();
	glTranslatef(pos.x,pos.y,0);
	theSprite->Render();
	glPopMatrix();

	return true;
}

bool CPointsAddPU::Init()
{
	name = "PointsAdd";
	tag = "PtAdd";
	genericTag = "PowerUp"; 
	
	
	theSprite = new CSprite(1,1,0);
	theSprite->LoadTGA("PointsAdd.tga");
	
	phys.Init(pos, Vector3(theSprite->GetImageSizeX(), theSprite->GetImageSizeY()));
	this->UpdateObjectTopLeftAndBottomRightPoint(false);
	pts = CPointSystem::GetInstance();

	return true;
}

bool CPointsAddPU::OnCollision2(CBaseObject* a_obj,bool again)
{
	if(a_obj->genericTag == "Character")
	{
		if(this->active == true)
		{
			CCharacter* temp=(CCharacter*)a_obj;
			pts->PointsReceive(10);
			this->active = false;
			std::cout << pts->GetPoints() << "as " << std::endl;
		}else
		if(this->active == false)
		{
		}
	}
	//phys.Init(pos,Vector3(theSprite->GetImageSizeX(),theSprite->GetImageSizeY()));
	return true;

}