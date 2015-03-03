#include "ImageManager.h"
#include "Sprite.h"
#include "RenderUntilty.h"

CImageManager* CImageManager::instance = 0;

CImageManager::CImageManager(void)
{
	Init();
}

CImageManager::~CImageManager(void)
{
	printf("image manager deleted");
}

CImageManager* CImageManager::GetInstance()
{
	if(instance == 0 )
	{
		instance = new CImageManager();
	}
	return instance;
}

TextureImage* CImageManager::GetTGAImage(std::string RegisteredName)
{
	return &TGAPool.find(RegisteredName)->second;
}

bool CImageManager::RegisterTGA(char* filename,std::string nametoberegister)
{
	TextureImage newImage;
	if(LoadTGA(&newImage,filename))
	{

		if(nametoberegister == "nil")
		{
			TGAPool.insert (std::make_pair(filename,newImage));
		}else
		{
			
			TGAPool.insert (std::make_pair(nametoberegister,newImage));
		}
		return true;
	}
	return false;
}

//CSprite* CImageManager::GetSprite(std::string RegisteredName)
//{
//	return &SpritePool.find(RegisteredName)->second;
//}
//
//bool CImageManager::RegisterSprite(CSprite* newSprite,std::string nametoberegister )
//{

//}
bool CImageManager::Init()
{
	return true;
}

bool CImageManager::CleanUp()
{
	return true;
}

bool CImageManager::Release()
{
	if(instance != 0)
	{
		delete this;
		instance = 0;
		return true;
	}
	return false;
}

bool CImageManager::Exit()
{
	if(instance)
	{
		if(CleanUp() && Release())
		{
			instance = nullptr;
			return true;
		}
	}else
	{
		return true;
	}
	return false;
}
void CImageManager::PrintDebugInformation()
{
	printf("\nTGA Pool Size %d",TGAPool.size());
}