#pragma once
#include "BaseObject.h"

#include <vector>


class Cell;

class CTestBallObject:public CBaseObject
{
private:
	
	 bool Init(){return true;};
	 bool Reset(){return true;};
	 bool CleanUp(){return true;};
public:
	int timecalled;
	float radius;
	float colour_red;
	float colour_blue;
	float colour_green;
	float posX;
	float posY;
	float velocityX;
	float velocityY;
	float delta_theta ;
	Cell* ownerCell;
	
	unsigned short cellvectorindex;

	//testing for the new Big object in multple cell algo.//old way will be left untouched until this is stable.
	

public:
	CTestBallObject(void);
	~CTestBallObject(void);
	bool Update();
	bool Render();
	void SetVelocity(float x,float y);
	void SetPosition(float x,float y = -1);
	void SetColour(float red,float green = -1,float blue = -1);
	void Move(float posx = 0,float posy = 0);

	void UpdateCollision(std::vector<CBaseObject*>& listofball,short startingIndex)
	{
		for(unsigned short i = startingIndex ; i< listofball.size();++i)
		{
			if(listofball[i] == this)
				continue;

			TestCollision(dynamic_cast<CTestBallObject*>(listofball[i]));
		}
	};
	bool TestCollision(CTestBallObject* a_obj)
	{
		//timecalled++;
		std::cout<<"Collision checking "<<this->name<<" "<<this->id<<" with"<<a_obj->name<<" "<<a_obj->id<<" time called"<<timecalled<<std::endl;
		if( (this->pos - a_obj->pos).Length() < (this->radius + a_obj->radius))
		{
			return OnCollision(a_obj);
		}
		return false;
	}
	bool OnCollision2(CBaseObject* a_obj,bool again=false)
	{
		std::cout<<"Collided with"<<a_obj->name<<" "<<a_obj->id<<std::endl;
		return true;
	};
	void PrintDebugInformation();

	//

};
typedef CTestBallObject ball;


