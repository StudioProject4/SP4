#include "ChineseHpReduce.h"


CChineseHpReduce::CChineseHpReduce(void)
	: ChHpTaken(false)
	, MlHpTaken(false)
{
}


CChineseHpReduce::~CChineseHpReduce(void)
{
	if(theSprite != NULL)
	{
		delete theSprite;
		theSprite = NULL;
	}
}

bool CChineseHpReduce::Init(Vector3 pos, Vector3 size)
{
	genericTag = "Targeted Obstacles";
	tag = "CHp";
	name = "ChineseHp";
	
	theSprite = new CSprite(1,1,0);
	theSprite->LoadTGA("Jump.tga");

	phys.Init(pos, Vector3(theSprite->GetImageSizeX(), theSprite->GetImageSizeY()));

	return true;
}
	
bool CChineseHpReduce::Render()
{
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	theSprite->Render();
	glPopMatrix();

	return true;
}
	
bool CChineseHpReduce::Update()
{
	return true;
}
	
bool CChineseHpReduce::OnCollision2(CBaseObject* a_obj,bool again)
{

	CChineseMale* tempCM = (CChineseMale*)a_obj;
	CMalayFemale* tempMF = (CMalayFemale*)a_obj;

	if(a_obj->genericTag == "Character")
	{
		if(a_obj->tag == "ChineseMale")
		{
			if(this->active == true)
			{			
				if(ChHpTaken == false)
				{
					tempCM->hp.TakeDMG();
					this->active = false;
					std::cout << "Chinese Health: " << tempCM->hp.GetHealth() << std::endl;
					ChHpTaken = true;
				}else
				if(ChHpTaken == true)
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
				//MlHpTaken = true;
		
			}
		}
		
    	
	}
	return true;

}