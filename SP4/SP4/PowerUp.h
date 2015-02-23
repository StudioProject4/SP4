#pragma once

#include "Map.h"
#include "BaseObject.h"

class CPowerUp : public CBaseObject
{

private:

	//hp count, points count, speed, incvincible, jumpheight
	//check how many items are taken
	int HpItemCount, PtsItemCount, 
		SpeedItemCount, InvinItemCount, JumpHeiCount;	
	
	//check if item is there
	bool HpAvail, InvinAvail;

	bool InvincibleOn;		//check if invincible is on

public:

	CPowerUp();
	~CPowerUp();

	bool Update();
	bool Init();

	void InvinItem();			//take in invincible

};