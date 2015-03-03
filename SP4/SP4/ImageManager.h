#pragma once

#include <map>
#include <string>

#include "TextureImage.h"

class CSprite;

class CImageManager
{
public:
	std::map<std::string,TextureImage> TGAPool;
	//std::map<std::string,CSprite> SpritePool;
	static CImageManager* instance;
private:
	CImageManager(void);
	bool Init();
public:
	
	static CImageManager* GetInstance();
	~CImageManager(void);

	TextureImage* GetTGAImage(std::string RegisteredName);
	bool RegisterTGA(char* filename,std::string nametoberegister = "nil");
	//CSprite* GetSprite(std::string RegisteredName);
	//bool RegisterSprite(CSprite* newSprite,std::string nametoberegister = "nil");

	
	bool CleanUp();
	bool Release();
	bool Exit();

	void PrintDebugInformation();
};

