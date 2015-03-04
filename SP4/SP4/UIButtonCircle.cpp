#include "UIButtonCircle.h"
#include "Mouse.h"

CUIButtonCircle::CUIButtonCircle(void)
	:radius(1.f)
{
	name = "circle button";
}


CUIButtonCircle::~CUIButtonCircle(void)
{

}

bool CUIButtonCircle::Update()
{	
	if(active)
	{
		ownTexture.LiveOn();
	}
	return true;
}

bool CUIButtonCircle::Render()
{
	if(active)
	{
		//glPushMatrix();
		//glTranslatef(position.x,position.y,0);
		//glColor3f(1,1,1);
		//
		//glBegin( GL_POLYGON ); // OR GL_LINE_LOOP
		//float delta_theta = 0.2f;
		//for( float angle = 0; angle < 2*Math::PI; angle += delta_theta )
		//	glVertex3f( radius*cos(angle), radius*sin(angle), 0 );
		//glEnd();
		//glPopMatrix();

			glPushMatrix();

			if(onHover)
			{
				ownTexture.SetColour4f(0.5f,0.5f,1.f);
				if(down)
				{
					ownTexture.SetColour4f(0.f,1.f,0.f);
				}
			}else
			{
				ownTexture.SetColour4f(1.f,1.f,1.f);
			}

			glTranslatef(position.x,position.y,0);
			//glScalef(1.8f,1.3f,1.f);
				ownTexture.Render();
		glPopMatrix();
	}
	return true;
}

bool CUIButtonCircle::ColisionCheck(CMouse* theMouse)
{
	bool result =  CollisionCheckColliderSphere(Vector3(theMouse->gameX,theMouse->gameY));
	if(result == true && theMouse->CheckLeftButtonDown())
	{
		down = true;
	}else
	{
		down = false;
	}
	return result;
	
}
void CUIButtonCircle::CalculateRadius()
{
	float x = this->ownTexture.GetImageSizeX();
	float y = this->ownTexture.GetImageSizeY();
	//std::cout<<"Size X: "<<x<<" y "<< y<<std::endl;
	this->radius = (x+y)*0.5f;

	//std::cout<<"Radius: "<<radius<<std::endl;
	this->ownTexture.SetImageSize(radius*1.8f,radius*1.8f);
}

bool CUIButtonCircle::CollisionCheckColliderSphere(Vector3& pos)
{
	if( (this->position - pos).Length() < this->radius)
	{
		onHover = true;
		return true;
	}
	onHover = false;
	return false;
}
void CUIButtonCircle::SetSize(Vector3& Size)
{
	this->ownTexture.SetImageSize(Size.x,Size.y);
	CalculateRadius();
};

void CUIButtonCircle::SetSize(float x,float y)
{
	this->ownTexture.SetImageSize(x,y);
	CalculateRadius();
};
void CUIButtonCircle::PrintDebugInformation()
{
	std::cout<<std::endl;
	std::cout<<"Active: "<<active<<std::endl;
	std::cout<<"Name: "<<name<<std::endl;
	std::cout<<"Image Size: X: "<<ownTexture.GetImageSizeX()<< " Y: "<<ownTexture.GetImageSizeY()<<std::endl;
	std::cout<<"Position: "<<position<<std::endl;
	std::cout<<"Radius: "<<radius<<std::endl;
};