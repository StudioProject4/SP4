#pragma once
#include "Vector3.h"
#include "Sprite.h"

class CMouse;

class CUIButton
{
public:
	bool active;
	Vector3 position;
	CSprite ownTexture;
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
	//bool CollisionCheckColliderBox();
	//bool CollisionCheckColliderSphere();
};

