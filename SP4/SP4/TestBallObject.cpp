#include "TestBallObject.h"

#include <GL/glut.h>
//#include <GL/freeglut.h>
//#include <GL/glext.h>

#include <iostream>
using namespace std;

#include "MyMath.h"

CTestBallObject::CTestBallObject(void)
	:radius(20.f)
	,posX(0.f)
	,posY(0.f)
	,delta_theta(0.1f)
	,colour_red(1.f)
	,colour_blue(0.5f)
	,colour_green(0.5f)
	,velocityX(0.f)
	,velocityY(0.f)
{
}


CTestBallObject::~CTestBallObject(void)
{
}

void CTestBallObject::Render()
{
	glPushMatrix();
	glTranslatef(posX,posY,0);
	glColor3f(colour_red,colour_green,colour_blue);
	glBegin( GL_POLYGON ); // OR GL_LINE_LOOP
		for( float angle = 0; angle < 2*Math::PI; angle += delta_theta )
		glVertex3f( radius*cos(angle), radius*sin(angle), 0 );
	glEnd();
	glPopMatrix();
}
void CTestBallObject::SetVelocity(float x,float y)
{
	this->velocityX = x;
	this->velocityY = y;
}

void CTestBallObject::Move(float posx,float posy)
{
	this->posX += posx;

	if(posy != -1)this->posY += posy;
}

void CTestBallObject::Update()
{
	this->posX += this->velocityX;
	this->posY += this->velocityY;
};

void CTestBallObject::SetPosition(float x,float y)
{
	this->posX = x;
	this->posY = y;
}

void CTestBallObject::SetColour(float red,float green,float blue)
{
	this->colour_red = red;

	if(green != -1)this->colour_green = green;

	if(blue != -1)this->colour_blue = blue;
}

void CTestBallObject::PrintDebugInformation()
{
	cout<<"PosX: "<<posX<<" PosY: "<<posY<<endl;
}
