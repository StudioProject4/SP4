#include "ChineseHpReduce.h"


CChineseHpReduce::CChineseHpReduce(void)
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
	theSprite->LoadTGA("HalalSign.tga");

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
	
bool CChineseHpReduce::OnCollision2(CBaseObject* a_obj)
{

	CChineseMale* tempCM = (CChineseMale*)a_obj;
	CMalayFemale* tempMF = (CMalayFemale*)a_obj;

	if(a_obj->genericTag == "Character")
	{
		if(this->active == true)
		{
			if(a_obj->tag == "ChineseMale")
			{

			}else
			if(a_obj->tag == "MalayFemale")
			{

			}
		}
	}

	return true;
}
