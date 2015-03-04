#pragma once
#include "Vector3.h"
#include "Sprite.h"

class CMouse;

class CUIButton
{
protected:
	float ratio;
public:
	bool active;
	Vector3 position;
	//one button could have multiple kind of trigger for example is mute and unmute botton.
	unsigned short triggermode;
	CSprite ownTexture;
	char* name;

	bool onHover;
	bool down;
public:
	CUIButton(void);
	~CUIButton(void);
	
	virtual bool Update() = 0;
	virtual bool Render() = 0;
	virtual bool ColisionCheck(CMouse* theMouse) = 0;

	virtual void ChangeTexture(CSprite * newSprite)
	{
		ownTexture = *newSprite;
	};
	virtual void ChangeTexture(TextureImage * newTexture)
	{
		ownTexture.OverrideTGATexture(newTexture);
	};
	virtual void SetSize(Vector3& Size)
	{
		this->ownTexture.SetImageSize(Size.x,Size.y);
	};
	
	void rescale(float ratio);

	virtual void SetSize(float x = 0.f,float y = 0.f)
	{
		this->ownTexture.SetImageSize(x,y);
	};
	virtual void SetPosition(Vector3& Position)
	{
		this->position = Position;
	};
	virtual void SetPosition(float x = 0.f,float y = 0.f)
	{
		this->position.Set(x,y);
	};
	virtual unsigned short CheckTriggerMode()
	{
		return this->triggermode;
	};
	virtual void PrintDebugInformation()
	{
		std::cout<<"Active: "<<active<<std::endl;
		std::cout<<"Position: "<<position<<std::endl;
	};
};

