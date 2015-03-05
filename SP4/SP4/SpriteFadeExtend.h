#pragma once
#include "sprite.h"
class CSpriteFadeExtend :
	public CSprite
{
public:
	bool active;
	bool stopeffect;
	float fadespeed;
	bool fademode;
	CSprite* originalObject;
protected:
	void Render(void);
public:

	CSpriteFadeExtend(CSprite* originalObject);
	~CSpriteFadeExtend(void);

	void FadeIn(float dt = 1.f);
	void FadeOut(float dt = 1.f);
	void LiveOn(float dt = 1);
	void Render(float dt);

	inline void SetFadingSpeed(float speed = 1.f)
	{
		fadespeed = speed;
	};
	inline void SetFadeInMode(float startingAlpha = 0.0f)
	{
		stopeffect = false;
		originalObject->SetAlpha(startingAlpha);
		fademode = false;
	}
	inline void SetFadeOutMode(float startingAlpha = 1.0f)
	{
		stopeffect = false;
		originalObject->SetAlpha(startingAlpha);
		fademode = true;
	}
	bool CheckIfFadingOut()
	{
		return fademode;
	}
	bool CheckIfFadingIn()
	{
		return !fademode;
	}
	void SetAnimationLayer(ushort newlayer);
	void SetFrameSpeed(float newframespeed);
	void SetFrameInterval(float newframeinterval);
	void SetImageSize(float x,float y);
	void SetColour4f(float red= 1.f,float green= 1.f,float blue= 1.f,float alpha = 1.f);
	void SetVitalInformation(ushort maxframe,ushort numberoflayer);
	float GetAlpha();
	void SetAlpha(float newAlpha = 1.f);
	void OverrideTGATexture(TextureImage* newTexture);
	short GetCurrentFrameIndex();
	float GetImageSizeX();
	float GetImageSizeY();

};

