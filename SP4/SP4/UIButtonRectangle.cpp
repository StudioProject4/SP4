#include "UIButtonRectangle.h"
#include "Mouse.h"

CUIButtonRectangle::CUIButtonRectangle(void)
{
	name = "rectangle button";
}

CUIButtonRectangle::~CUIButtonRectangle(void)
{
}
bool CUIButtonRectangle::Update()
{
	if(active)
	{
		ownTexture.LiveOn();
	}
	return true;
}

bool CUIButtonRectangle::Render()
{
	if(active)
	{
		glPushMatrix();
			glTranslatef(position.x,position.y,0);
				ownTexture.Render();
		glPopMatrix();
	}
	return true;
}

bool CUIButtonRectangle::ColisionCheck(CMouse* theMouse)
{
	return CollisionCheckColliderBox(Vector3(theMouse->lastX,theMouse->lastY));
}

bool CUIButtonRectangle::CollisionCheckColliderBox(Vector3& pos)
{
	if( (pos.x >= TopLeft.x && pos.x <= BottomRight.x) && (pos.y >= TopLeft.y && pos.y <= BottomRight.y) )
	{
		std::cout<<"rec"<<std::endl;
		return true;
	}
	return false;
}
void CUIButtonRectangle::CalculateTopLeftAndBottomRightPoint()
{
	TopLeft.Set(position.x - ownTexture.GetImageSizeX() *0.5,position.y - ownTexture.GetImageSizeY()*0.5);
	BottomRight.Set(position.x + ownTexture.GetImageSizeX()*0.5,position.y + ownTexture.GetImageSizeY()*0.5);
};

void CUIButtonRectangle::SetSize(Vector3& Size)
{
	//this->size = Size;
	this->ownTexture.SetImageSize(Size.x,Size.y);
	CalculateTopLeftAndBottomRightPoint();
};

void CUIButtonRectangle::SetSize(float x,float y)
{
	//this->size.Set(x,y);
	this->ownTexture.SetImageSize(x,y);
	CalculateTopLeftAndBottomRightPoint();
};

void CUIButtonRectangle::PrintDebugInformation()
{
	std::cout<<std::endl;
	std::cout<<"Active: "<<active<<std::endl;
	std::cout<<"Name: "<<name<<std::endl;
	std::cout<<"Image Size: X: "<<ownTexture.GetImageSizeX()<< " Y: "<<ownTexture.GetImageSizeY()<<std::endl;
	std::cout<<"Position: "<<position<<std::endl;
	std::cout<<"TopLeft Point: "<<TopLeft<<std::endl;
	std::cout<<"BottomRight Point: "<<BottomRight<<std::endl;
};