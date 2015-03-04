#include "MalayHpReduce.h"


CMalayHpReduce::CMalayHpReduce(void)
	: ChHpTaken(false)
	, MlHpTaken(false)
{
}


CMalayHpReduce::~CMalayHpReduce(void)
{
	if(theSprite != NULL)
	{
		delete theSprite;
		theSprite = NULL;
	}
}

bool CMalayHpReduce::Init(Vector3 pos, Vector3 size)
{
	genericTag = "Targeted Obstacles";
	tag = "MHp";
	name = "MalayHp";

	theSprite = new CSprite(1,1,0);
	theSprite->LoadTGA("MalayVillage.tga");

	phys.Init(pos, Vector3(theSprite->GetImageSizeX(), theSprite->GetImageSizeY()));

	return true;
}

bool CMalayHpReduce::Render()
{
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	theSprite->Render();
	glPopMatrix();

	return true;
}
	
bool CMalayHpReduce::Update()
{
	return true;
}
	
bool CMalayHpReduce::OnCollision2(CBaseObject* a_obj,bool again)
{
	CChineseMale* tempCM = (CChineseMale*)a_obj;
	CMalayFemale* tempMF = (CMalayFemale*)a_obj;

	if(a_obj->genericTag == "Character")
	{
		if(this->active == true)
		{
			if(a_obj->tag == "MalayFemale")
			{
				//tempMF->pts.PointsReceive(10);
				//this->active = false;
				//std::cout << "Malay Points" << tempMF->pts.GetPoints() << std::endl;
				if(this->active == true)
				{
					
					if(MlHpTaken == false)
					{
						tempMF->hp.RecoverHealth();
						////this->active = false;
						std::cout << "Malay Health: " << tempMF->hp.GetHealth() << std::endl;
						std::cout << "Malay Health Added" << std::endl;
						std::cout << "MalayAdd: " << tempMF->hp.GetHealth() << std::endl;
						MlHpTaken = true;
					}else
					if(MlHpTaken == true)
					{
					}
				}else
				{
					//taken
				}
			}else
			if(a_obj->tag == "ChineseMale")
			{
				//tempCM->pts.PointsReceive(-10);
				//this->active = false;
				//std::cout << "Chinese Points" << tempCM->pts.GetPoints() << std::endl;
				if(this->active == true)
				{
					tempCM->hp.TakeDMG();
					//this->active = false;
					//std::cout << "Chinese Health: " << tempCM->hp.GetHealth() << std::endl;
					//std::cout << "Chinese Take DMG" << std::endl;
					//std::cout << "ChineseMinus: " << tempCM->hp.GetHealth() << std::endl;
					//ChPtsTaken = true;
				}else
				{
					//taken
				}
			}
		}
	}
	return true;
}
