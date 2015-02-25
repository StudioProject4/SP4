#include "PowerUp.h"
#include <iostream>
using namespace std;

CPowerUp::CPowerUp()
	: InvincibleOn(false)
	, HpAvail(true)
	, InvinAvail(true)
	, PtAvail(true)
	, JumpAvail(true)
	, SpdAvail(true)
{
}

CPowerUp::~CPowerUp()
{
}

bool CPowerUp::Init()
{
	/*things needed
	speed up
	point modifier
	recovery
	invinceible
	jump height
	*/

	//if(HpAvail == true)
	//{
	//	name = "HpAdd";
	//	tag = "HP";
	//	genericTag = "PowerUp";
	//}	
	//if(InvinAvail == true)
	//{
	//	name = "Invincible";
	//	tag = "Invin";
	//	genericTag = "PowerUp";
	//}
	//if(PtAvail == true)
	//{
	//	name = "PtAdd";
	//	tag = "Pt";
	//	genericTag = "PowerUp";
	//}
	//if(JumpAvail == true)
	//{
	//	name = "JumpHt";
	//	tag = "JpHt";
	//	genericTag = "PowerUp";
	//}
	//if(SpdAvail == true)
	//{
	//	name = "SpdAdd";
	//	tag = "Spd";
	//	genericTag = "PowerUp";
	//}

	HpItem();
	SpdItem();
	//InvinItem();
	PtsItem();
	JpItem();


	return true;
}



void CPowerUp::HpItem()
{
		name = "HpAdd";
		tag = "HP";
		genericTag = "PowerUp";
}

void CPowerUp::InvinItem()
{
		name = "Invincible";
		tag = "Invin";
		genericTag = "PowerUp";

	if(InvincibleOn == false)
	{
		InvinItemCount +=1;
		InvincibleOn = true;
	}
	if(InvincibleOn == true)
	{

	}

}

void CPowerUp::SpdItem()
{
	name = "SpdAdd";
	tag = "Spd";
	genericTag = "PowerUp";
}
	
void CPowerUp::JpItem()
{
	name = "JumpHt";
	tag = "JpHt";
	genericTag = "PowerUp";
}	

void CPowerUp::PtsItem()
{
	name = "PtAdd";
	tag = "Pt";
	genericTag = "PowerUp";
}


