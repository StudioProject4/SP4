#include "WinCondition.h"

CWinCondition::CWinCondition(void)
	: ChineseMaleIn(false)
	, MalayFemaleIn(false)
	, lvC(NULL)
{
	
}
	
CWinCondition::~CWinCondition(void)
{
	if(theSprite != NULL)
	{
		delete theSprite;
		theSprite = NULL;
	}
}

bool CWinCondition::Render()
{
	return true;
}
	
bool CWinCondition::Update()
{
	return true;
}
	
bool CWinCondition::Init()
{
	theSprite = new CSprite(1,1,0);
	theSprite->LoadTGA("MalayVillage.tga");

	phys.Init(pos, Vector3(theSprite->GetImageSizeX(), theSprite->GetImageSizeY()));

	return true;
}
	
bool CWinCondition::OnCollision2(CBaseObject* a_obj)
{
	if(this->active == true)
	{
		if(ChineseMaleIn == false && MalayFemaleIn == false)
		{
			if(a_obj->name == "ChineseMale")
			{
				ChineseMaleIn = true;
				std::cout << "Chinese In" << std::endl;
			}
			if(a_obj->name == "MalayFemale")
			{
				MalayFemaleIn = true;
				std::cout << "Malay In" << std::endl;
			}
		}
		if(ChineseMaleIn == true && MalayFemaleIn == true)
		{
			lvC.Level += 1;
			std::cout << "Level plus: " << lvC.Level << std::endl;
		}
	}

	return true;
}
	
void CWinCondition::LevelChange()
{
	/*if(ChineseMaleIn == true && MalayFemaleIn == true)
	{
		lvC.Level += 1;
	}*/
}