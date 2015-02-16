#pragma once
#include "DatatypeDefination.h"

#include "TextureImage.h" // for a texture struct and include GLlibrary

#include "SContainer2D.h"

class CSprite
{
protected:
	ushort maxframe;
	ushort numberoflayer;
	
	short currentframe;

	TextureImage owntexture;

	bool pause;
	float frameinterval;//delay between frames
	float framespeed;//speed of tranversing frames
	SContainer2D size;//size of entire image

	ushort currentlayer;//current layer that it is rendering
	float currenttimecounter;
	SContainer2D framesize; // the size of one frame in an animation strip

	bool lateralinvert;

public:
	CSprite(ushort maxframe, ushort numberoflayer = 1,ushort currentlayer = 0);
	~CSprite(void);

	
	bool LoadTGA(char *filename);
	virtual void Render(void);

	void CheckUp(void);
	void LiveOn(float dt = 1);
	void TogglePause(void);
	void ToggleLateralInvertRender(void);

	void SetAnimationLayer(ushort newlayer);
	void SetFrameSpeed(float newframespeed);
	void SetFrameInterval(float newframeinterval);
	void SetImageSize(float x,float y);

	void TranverseAnimationLayer(bool forward,bool warp = true);
	void TranverseAnimationFrame(bool forward,bool warp = true);

	void SetVitalInformation(ushort maxframe,ushort numberoflayer);

	inline short GetCurrentFrameIndex()
	{
		return currentframe;
	}

	inline float GetImageSizeX()
	{
		return size.x;
	}
	inline float GetImageSizeY()
	{
		return size.y;
	}
};

