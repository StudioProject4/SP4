#pragma once

#include "BaseObject.h"
#include "Map.h"
#include "Character.h"
#include "Sprite.h"

class CPowerUp : public CBaseObject
{

private:

/*
	//hp count, points count, speed, incvincible, jumpheight
	//check how many items are taken
	int HpItemCount, PtsItemCount, 
		SpeedItemCount, InvinItemCount, JumpHeiCount;	
	
	//check if item is there
	bool HpAvail, InvinAvail, PtAvail, JumpAvail, SpdAvail;

	bool InvincibleOn;		//check if invincible is on
	*/

public:

	CPowerUp();
	~CPowerUp();

	virtual bool Update()=0;
	virtual bool Render()=0;

	bool Init();

	//void InvinItem();			//take in invincible

	//CSprite * theSprite;
	

	// Are you going to have derived power up class from this class ,or are you going to use this class for all type of power up ?

	//added the following temporary function to let your class be instantitable. 
	//If you are going to use this class for every type of power up then, implement the below function as per you wanted,
	//else if there will be more derived class, then make the below functions virtual,or can just remove them.
	bool OnCollision2(CBaseObject* a_obj,bool again=false)=0;
	//bool Render(){return true;};
	bool Reset(){return true;};
	bool CleanUp(){return true;};


};