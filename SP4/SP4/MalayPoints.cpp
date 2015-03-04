#include "MalayPoints.h"

CMalayPoints::CMalayPoints()
	: ChPtsTaken(false)
	, MlPtsTaken(false)
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

bool CMalayPoints::OnCollision2(CBaseObject* a_obj,bool again)
{
	
	CMalayFemale* tempMF = (CMalayFemale*)a_obj;
	CChineseMale* tempCM = (CChineseMale*) a_obj;

	/*std::cout << "Malay Health: " << tempMF->hp.GetHealth() << std::endl;
	std::cout << "Chinese Health: " << tempCM->hp.GetHealth() << std::endl;
*/

	if(a_obj->genericTag = "Character")
	{
			
		/*if(this->active == true)
		{*/
			if(a_obj->tag == "MalayFemale")
			{
				if(this->active == true)
				{			
					if(MlPtsTaken == false)
					{
						pts->PointsReceive(30);
						this->active = false;
						std::cout << "Malay Points: " << pts->GetPoints() << std::endl;
						std::cout << "Malay Points Added" << std::endl;
						std::cout << "Malay Addpts: " << pts->GetPoints() << std::endl;
						MlPtsTaken = true;
					}else
					if(MlPtsTaken == true)
					{
						//
					}
				}
			}else 
			if(a_obj->tag == "ChineseMale")
			{
				if(this->active == true)
				{
					//tempCM->hp.TakeDMG();
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

	return true;
}