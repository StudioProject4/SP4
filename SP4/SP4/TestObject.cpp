#include "TestObject.h"


CTestObject::CTestObject(void)
{
}


CTestObject::~CTestObject(void)
{
}

bool CTestObject::Render()
{
	glPushMatrix();
	glColor3f(1,1,1);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glTranslatef(pos.x,pos.y,0);
		glScalef(this->phys.size.x,this->phys.size.y,0);
		//glBindTexture(GL_TEXTURE_2D,this->testimage.texID);
		glBegin (GL_TRIANGLE_STRIP);
			glNormal3f(0,0,1);
			glTexCoord2f(0,0);
			glVertex3f(-0.5, 0.5, 0);
		
			glTexCoord2f(0,1.0);
			glVertex3f(-0.5,-0.5,0);

			glTexCoord2f(1.0,0.0);
			glVertex3f(0.5,0.5,0);

			glTexCoord2f(1.0,1.0);
			glVertex3f(0.5,-0.5,0);
		glEnd();
	//glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	return true;
}