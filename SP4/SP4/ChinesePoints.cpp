#include "ChinesePoints.h"

CChinesePoints::CChinesePoints(void)
	: ChPtsTaken(false)
	, MlPtsTaken(false)
{
}

CChinesePoints::~CChinesePoints(void)
{
	if(theSprite != NULL)
	{
		delete theSprite;
		theSprite = NULL;
	}
}

bool CChinesePoints::Render()
{
	glPushMatrix();
	glTranslatef(pos.x,pos.y,0);
	theSprite->Render();
	glPopMatrix();

	return true;

}

bool CChinesePoints::Init(Vector3 pos,Vector3 size)
{
	name = "ChineseSign";
	tag = "CHINAS";
	genericTag = "Targeted Obstacles"; 
		
	theSprite = new CSprite(1,1,0);
	theSprite->LoadTGA("ChineseSign.tga");

	phys.Init(pos, Vector3(theSprite->GetImageSizeX(), theSprite->GetImageSizeY()));
	pts = CPointSystem::GetInstance();
	
	return true;
}
	
bool CChinesePoints::Update()
{

	return true;
}
	
bool CChinesePoints::OnCollision2(CBaseObject* a_obj,bool again)
{

	CChineseMale* tempCM = (CChineseMale*)a_obj;
	CMalayFemale* tempMF = (CMalayFemale*)a_obj;
	CCharacter* tempC = (CCharacter*)a_obj;

	if(a_obj->genericTag == "Character")
	{
		
			if(a_obj->tag == "ChineseMale")
			{		
				if(this->active == true)
				{			
					if(ChPtsTaken == false)
					{
						pts->PointsReceive(30);
						this->active = false;
						std::cout << "Chinese Points: " << pts->GetPoints() << std::endl;
						std::cout << "Chinese Points Added" << std::endl;
						std::cout << "Chinese Addpts: " << pts->GetPoints() << std::endl;
						ChPtsTaken = true;
					}else
					if(ChPtsTaken == true)
					{
						//
					}
				}
			}else 
			if(a_obj->tag == "MalayFemale")
			{
				if(this->active == true)
				{
					
					//not valid	
					//tempMF->hp.TakeDMG();
					//this->active = false;
					//std::cout << "Malay Health: " << tempMF->hp.GetHealth() << std::endl;
					//std::cout << "Malay Health Minus" << std::endl;
					//std::cout << "MalayMinus: " << tempMF->hp.GetHealth() << std::endl;	
				}
			}
		//}else
		//{
		//	//taken
		//}
	}
	return true;
}