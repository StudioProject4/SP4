#pragma once
#include "Character.h"
#include "RenderUntilty.h"
#include <stdio.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <GL/glext.h>

class CMalayFemale : public CCharacter
{
	public:
		CMalayFemale();
		~CMalayFemale();
		bool Init(Vector3 newPos,Vector3 newDir,int entityID);
		bool Update();
		bool Render();
	private:
		TextureImage Texture;
};