#include "PowerUp.h"
#include <iostream>
using namespace std;

CPowerUp::CPowerUp()
/*	: InvincibleOn(false)
	, HpAvail(true)
	, InvinAvail(true)
	, PtAvail(true)
	, JumpAvail(true)
	, SpdAvail(true)*/
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

	name = "Powerup";
	tag = "PU";
	genericTag = "CPowerUp";

	return true;
}
