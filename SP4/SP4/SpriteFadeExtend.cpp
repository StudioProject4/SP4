#include "SpriteFadeExtend.h"


CSpriteFadeExtend::CSpriteFadeExtend(CSprite* originalObject)
	:originalObject(originalObject)
	,fadespeed(0.1f)
	,fademode(true)
	,stopeffect(true)
	,active(true)
{
}


CSpriteFadeExtend::~CSpriteFadeExtend(void)
{
}

void CSpriteFadeExtend::FadeIn(float dt)
{
	if(originalObject->GetAlpha()<1.0f)
	{
		//printf("\nfadein");
		while(dt >1)
		{
			dt *= 0.1f;
		}
		//std::cout<<dt<<std::endl;
		originalObject->SetAlpha(originalObject->GetAlpha()+ fadespeed*dt);
	}
}

void CSpriteFadeExtend::FadeOut(float dt)
{
	if(originalObject->GetAlpha()>0.0f)
	{
		//printf("\nfadeout");
		while(dt >1)
		{
			dt *= 0.1f;
		}
		//std::cout<<dt<<std::endl;
		originalObject->SetAlpha(originalObject->GetAlpha()- fadespeed*dt);
	}
}
void CSpriteFadeExtend:: Render(float dt)
{
	if(active)
	{
	if(!stopeffect)
	{
		if(fademode == true)
		{
			FadeOut(dt);
		}else
		{
			FadeIn(dt);
		}
	}
	this->Render();
	}
}
void CSpriteFadeExtend::LiveOn(float dt)
{
	if(active)
	{
		originalObject->LiveOn(dt);
	}
}
void CSpriteFadeExtend::Render(void)
{

	originalObject->Render();
}

void CSpriteFadeExtend::SetAnimationLayer(ushort newlayer)
{
	originalObject->SetAnimationLayer(newlayer);
}
void CSpriteFadeExtend::SetFrameSpeed(float newframespeed)
{
	originalObject->SetFrameSpeed(newframespeed);
}
void CSpriteFadeExtend::SetFrameInterval(float newframeinterval)
{
	originalObject->SetFrameInterval(newframeinterval);
	
}
void CSpriteFadeExtend::SetImageSize(float x,float y)
{
	originalObject->SetImageSize(x,y);
}
void CSpriteFadeExtend::SetVitalInformation(ushort maxframe,ushort numberoflayer)
{
	originalObject->SetVitalInformation(maxframe,numberoflayer);
}

void CSpriteFadeExtend::SetColour4f(float red,float green,float blue,float alpha)
{
	originalObject->SetColour4f(red,green,blue,alpha);
}
float CSpriteFadeExtend::GetAlpha()
{
	return originalObject->GetAlpha();
}
void CSpriteFadeExtend::SetAlpha(float newAlpha )
{
	originalObject->SetAlpha(newAlpha);
}
void CSpriteFadeExtend::OverrideTGATexture(TextureImage* newTexture)
{
	originalObject->OverrideTGATexture(newTexture);
}
short CSpriteFadeExtend::GetCurrentFrameIndex()
{
	return originalObject->GetCurrentFrameIndex();
}

float CSpriteFadeExtend::GetImageSizeX()
{
	return originalObject->GetImageSizeX();
}
float CSpriteFadeExtend::GetImageSizeY()
{
	return originalObject->GetImageSizeY();
}