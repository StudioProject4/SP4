#include "MalayHpReduce.h"


CMalayHpReduce::CMalayHpReduce(void)
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
				this->active = false;
				//std::cout << "Malay Points" << tempMF->pts.GetPoints() << std::endl;
			}else
			if(a_obj->tag == "ChineseMale")
			{
				//tempCM->pts.PointsReceive(-10);
				this->active = false;
				//std::cout << "Chinese Points" << tempCM->pts.GetPoints() << std::endl;
			}
		}
	}
	return true;
}