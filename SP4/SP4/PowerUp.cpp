#include "PowerUp.h"
#include <iostream>
using namespace std;

CPowerUp::CPowerUp()
	: InvincibleOn(false)
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

	return true;
}

bool CPowerUp::Update()
{

	//speed up
	

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