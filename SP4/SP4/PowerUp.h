#pragma once

#include "Map.h"

class CPowerUp
{

private:

	//hp count, points count, speed, incvincible, jumpheight
	//check how many items are taken
	int HpItemCount, PtsItemCount, 
		SpeedItemCount, InvinItemCount, JumpHeiCount;		

	bool InvincibleOn;		//check if invincible is on

public:

	CPowerUp();
	~CPowerUp();

	bool Update();
	bool Init();

	void InvinItem();			//take in invincible

};