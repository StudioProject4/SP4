#pragma once
#include "Character.h"
#include "RenderUntilty.h"
#include "Sprite.h"
#include "Physics.h"
#include <stdio.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#include <time.h>

class CChineseMale : public CCharacter
{
	public:
		CChineseMale();
		~CChineseMale();
		bool Init(Vector3 newPos,Vector3 newDir,int entityID);

		bool Update();
		bool Init();
		bool Reset();
		bool CleanUp();
		bool Render();

		bool OnCollision2(CBaseObject* a_obj);
	private:
		//CSprite * theSprite;
		//CPowerUp* thePowerUp;


};