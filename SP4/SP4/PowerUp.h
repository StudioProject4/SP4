#pragma once

#include "Map.h"
#include "BaseObject.h"
#include "Character.h"

class CPowerUp : public CBaseObject
{

private:

	//hp count, points count, speed, incvincible, jumpheight
	//check how many items are taken
	int HpItemCount, PtsItemCount, 
		SpeedItemCount, InvinItemCount, JumpHeiCount;	
	
	//check if item is there
	bool HpAvail, InvinAvail, PtAvail, JumpAvail, SpdAvail;

	bool InvincibleOn;		//check if invincible is on

public:

	CPowerUp();
	~CPowerUp();

	virtual bool Update();
	virtual bool Render();
	virtual bool OnActivate();

	bool Init();

	void InvinItem();			//take in invincible
	void HpItem();
	void SpdItem();
	void JpItem();
	void PtsItem();

};