#include "ChinesePoints.h"

CChinesePoints::CChinesePoints(void)
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

	return true;
}
	
bool CChinesePoints::Update()
{

	return true;
}
	
bool CChinesePoints::OnCollision(CBaseObject* a_obj)
{

	CChineseMale* tempCM = (CChineseMale*)a_obj;
	CMalayFemale* tempMF = (CMalayFemale*)a_obj;

	//std::cout << "Malay Health: " << tempMF->hp.GetHealth() << std::endl;
	//std::cout << "Chinese Health: " << tempCM->hp.GetHealth() << std::endl;


	if(a_obj->genericTag == "Character")
	{
		if(this->active == true)
		{
			if(a_obj->tag == "ChineseMale")
			{
				/*if(this->active == true)
				{*/
					
					tempCM->hp.RecoverHealth();
					this->active = false;
					std::cout << "Chinese Health: " << tempCM->hp.GetHealth() << std::endl;
					std::cout << "Chinese HEAlth Added" << std::endl;
					std::cout << "Chinese Add: " << tempCM->hp.GetHealth() << std::endl;
				/*}else
				{
					//taken
				}*/
			}else 
			if(a_obj->tag == "MalayFemale")
			{
				/*if(this->active == true)
				{*/
					//not valid
					
					tempMF->hp.TakeDMG();
					this->active = false;
					std::cout << "Malay Health: " << tempMF->hp.GetHealth() << std::endl;
					std::cout << "Malay Health Minus" << std::endl;
					std::cout << "MalayMinus: " << tempMF->hp.GetHealth() << std::endl;

				/*}else
				{
					//not valid
				}*/
			}
		}else
		{
			//taken
		}
	}
	return true;
}