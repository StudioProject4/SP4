#include "PowerUp.h"
#include <iostream>
using namespace std;

CPowerUp::CPowerUp()
	: InvincibleOn(false)
	, HpAvail(true)
	, InvinAvail(true)
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

	if(HpAvail == true)
	{
		name = "HpAdd";
		tag = "HP";
		genericTag = "PowerUp";
	}	
	if(InvinAvail == true)
	{
		name = "Invincible";
		tag = "Invin";
		genericTag = "PowerUp";
	}


	return true;
}

bool CPowerUp::Update()
{

	//speed up
	

	//point modifier


	//recovery


	//jumpheight

	
	//Invincible On
	InvinItem();
	
	return true;
}

void CPowerUp::InvinItem()
{

	if(InvincibleOn == false)
	{
		InvinItemCount +=1;
		InvincibleOn = true;
	}
	if(InvincibleOn == true)
	{

	}

}