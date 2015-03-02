#include "MalayPoints.h"

CMalayPoints::CMalayPoints()
{
}

CMalayPoints::~CMalayPoints()
{
	if(theSprite != NULL)
	{
		delete theSprite;
		theSprite = NULL;
	}
}

bool CMalayPoints::Render()
{
	glPushMatrix();
	glTranslatef(pos.x,pos.y,pos.z);
	theSprite->Render();
	glPopMatrix();

	return true;
}

bool CMalayPoints::Init(Vector3 pos,Vector3 size)
{
	name = "MalaySign";
	tag = "MALAYS";
	genericTag = "Targeted Obstacles";
	
	theSprite = new CSprite(1,1,0);
	theSprite->LoadTGA("HalalSign.tga");

	phys.Init(pos, Vector3(theSprite->GetImageSizeX(), theSprite->GetImageSizeY()));

	return true;
}

bool CMalayPoints::Update()
{

	return true;
}

bool CMalayPoints::OnCollision2(CBaseObject* a_obj)
{
	
	CMalayFemale* tempMF = (CMalayFemale*)a_obj;
	CChineseMale* tempCM = (CChineseMale*) a_obj;

	/*std::cout << "Malay Health: " << tempMF->hp.GetHealth() << std::endl;
	std::cout << "Chinese Health: " << tempCM->hp.GetHealth() << std::endl;
*/

	if(a_obj->genericTag = "Character")
	{
			
		if(this->active == true)
		{
			if(a_obj->tag == "MalayFemale")
			{
				//if(this->active == true)
				//{
					
					tempMF->hp.RecoverHealth();
					this->active = false;
					std::cout << "Malay Health: " << tempMF->hp.GetHealth() << std::endl;
					std::cout << "Malay Health Added" << std::endl;
					std::cout << "MalayAdd: " << tempMF->hp.GetHealth() << std::endl;
					
				//}else
				//{
					//taken
				//}
			}else 
			if(a_obj->tag == "ChineseMale")
			{
				//if(this->active == true)
				//{
					tempCM->hp.TakeDMG();
					this->active = false;
					std::cout << "Chinese Health: " << tempCM->hp.GetHealth() << std::endl;
					std::cout << "Chinese Take DMG" << std::endl;
					std::cout << "ChineseMinus: " << tempCM->hp.GetHealth() << std::endl;
				
				//}else
				//{
					//taken
				//}
			}
		}else
		{
			//taken
		}
	}

	return true;
}