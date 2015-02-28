#include "TestBallObject.h"

#include <GL/glut.h>
//#include <GL/freeglut.h>
//#include <GL/glext.h>

#include <iostream>
using namespace std;

#include "MyMath.h"

CTestBallObject::CTestBallObject(void)
	:radius(10.f)
	,posX(0.f)
	,posY(0.f)
	,delta_theta(0.1f)
	,colour_red(1.f)
	,colour_blue(0.5f)
	,colour_green(0.5f)
	,velocityX(0.f)
	,velocityY(0.f)
	,ownerCell(nullptr)
	,cellvectorindex(-1)
	,timecalled(0)
{
	name = "test balls";
	genericTag = "Character";
	phys.Init(Vector3(posX,posY),Vector3(radius,radius));

}


CTestBallObject::~CTestBallObject(void)
{
	std::cout<<"test ball destory"<<std::endl;
}

bool CTestBallObject::Render()
{
	glPushMatrix();
	glTranslatef(pos.x,pos.y,0);
	glColor3f(colour_red,colour_green,colour_blue);
	glBegin( GL_POLYGON ); // OR GL_LINE_LOOP
		for( float angle = 0; angle < 2*Math::PI; angle += delta_theta )
		glVertex3f( radius*cos(angle), radius*sin(angle), 0 );
	glEnd();
	glPopMatrix();
	//phys.Update(pos);


	//glPushMatrix();
	//glBegin(GL_LINE_STRIP);
	//glVertex2f((pos.x - (radius)),(pos.y + (radius)));//top left
	//glVertex2f((pos.x + (radius)),(pos.y + (radius)));//top right
	//glVertex2f((pos.x + (radius)),(pos.y - (radius)));//bottom right
	//glVertex2f((pos.x - (radius)),(pos.y - (radius))); //bottom left
	//glVertex2f((pos.x - (radius)),(pos.y + (radius)));//top left
	//
	//glEnd();
	//glPopMatrix();

	glPushMatrix();
	glColor3f(1,1,1);
	glBegin(GL_LINE_STRIP);
	glVertex2f(TopLeft.x,TopLeft.y);//top left
	glVertex2f(BottomRight.x,TopLeft.y);//top right
	glVertex2f(BottomRight.x,BottomRight.y);//bottom right
	glVertex2f(TopLeft.x,BottomRight.y); //bottom left
	glVertex2f(TopLeft.x,TopLeft.y);//top left
	
	glEnd();
	glPopMatrix();


	return true;
}
void CTestBallObject::SetVelocity(float x,float y)
{
	this->velocityX = x;
	this->velocityY = y;
}

void CTestBallObject::Move(float posx,float posy)
{
	this->pos.x += posx;

	if(posy != -1)this->pos.y += posy;
}

bool CTestBallObject::Update()
{
	phys.size.Set(radius,radius);
	this->UpdateObjectTopLeftAndBottomRightPoint(true);
	//TopLeft.Set(pos.x - phys.size.x,pos.y - phys.size.y);
	//BottomRight.Set(pos.x + phys.size.x,pos.y + phys.size.y);

	this->pos.x += this->velocityX;
	this->pos.y += this->velocityY;
	return true;
};

void CTestBallObject::SetPosition(float x,float y)
{
	this->pos.x = x;
	this->pos.y = y;
}

void CTestBallObject::SetColour(float red,float green,float blue)
{
	this->colour_red = red;

	if(green != -1)this->colour_green = green;

	if(blue != -1)this->colour_blue = blue;
}

void CTestBallObject::PrintDebugInformation()
{
	std::cout<<" pos"<<pos<<std::endl;
	std::cout<<" Top Left Point"<<TopLeft<<std::endl;
	std::cout<<" Bottom Right Point"<<BottomRight<<std::endl;
	std::cout<<" Top Left Cell Index"<<TopLeftCellIndex<<std::endl;
	std::cout<<" Bottom Right Cell Index"<<BottomRightCellIndex<<std::endl;
}
