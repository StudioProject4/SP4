#include "ChineseMale.h"

CChineseMale :: CChineseMale()
{
	name = "GenericChineseKid";
	tag = "ChineseMale";
	genericTag = "Character";
}

CChineseMale :: ~CChineseMale()
{
	
}

bool CChineseMale :: Init(Vector3 newPos,Vector3 newDir,int entityID)
{
	pos = newPos;
	dir = newDir;
	id = entityID;
	LoadTGA(&Texture,"sonia2.tga");
	return true;
}
bool CChineseMale :: Update()
{
	return true;
}
bool CChineseMale :: Render()
{
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, Texture.texID);
		glTranslatef(pos.x,pos.y,pos.z);
		glBegin(GL_QUADS);
			glVertex2f(-0.5f,0.5f);//topleft
			glVertex2f(0.5f,0.5f);//topright
			glVertex2f(0.5f,-0.5f);//bottomright
			glVertex2f(-0.5f,-0.5f);//bottomleft
		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	return true;
}