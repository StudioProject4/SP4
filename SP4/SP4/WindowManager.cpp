#include "WindowManager.h"
#include <iostream>
CWindowManager* CWindowManager::instance = 0;
CWindowManager::CWindowManager(void)
	:inited(false)
{
}


CWindowManager::~CWindowManager(void)
{
}

CWindowManager* CWindowManager::GetInstance()
{
	if(instance == 0)
	{
		instance = new CWindowManager();
	}
	return instance;
}

bool CWindowManager::Update()
{
	
	UpdateWindowDimension();
	UpdateWindowPosition();

	return true;
}

bool CWindowManager::Init(int windowWidth,int windowHeight,int windowPositionX,int windowPositionY,bool fullScreen,std::string programName)
{
	if(!inited)
	{
		defaultWindowStatus.Set(windowWidth,windowHeight,windowPositionX,windowPositionY,fullScreen);
		defaultWindowStatus.programName = programName;
		windowStatus = defaultWindowStatus;
		//this->PrintDebugWindowInformation();
		//this->PrintDebugDefaultWindowInformation();
		return Init();
	}else
	{
		SetAndUpdateWindowPosition(windowPositionX,windowPositionY);
		SetAndUpdateWindowDimension(windowWidth,windowHeight);
		SetAndUpdateFullScreen(fullScreen);
		return true;
	}
	return false;
}

bool CWindowManager::Init()
{
	glutInitWindowPosition(windowStatus.windowPositionX,windowStatus.windowPositionY);
	glutInitWindowSize(windowStatus.windowWidth,windowStatus.windowHeight);
	glutCreateWindow(windowStatus.programName.c_str());
	if(windowStatus.fullScreen)
	{
		glutFullScreen();
	}
	inited = true;
	return true;
}

bool CWindowManager::Reset()
{
	windowStatus = defaultWindowStatus;

	//glutPositionWindow(windowStatus.windowPositionX,windowStatus.windowPositionY);
	//glutReshapeWindow(windowStatus.windowWidth, windowStatus.windowHeight);
	Update();

	return true;
}

bool CWindowManager::CleanUp()
{
	return true;
}

void CWindowManager::SetAndUpdateWindowDimension(int newWindowWidth,int newWindowHeight)
{
	SetWindowWidth(newWindowWidth);
	SetWindowHeight(newWindowHeight);
	//glutReshapeWindow(windowStatus.windowWidth, windowStatus.windowHeight);
	UpdateWindowDimension();
}

void CWindowManager::SetAndUpdateWindowPosition(int newWindowPositionX,int newWindowPositionY)
{
	SetWindowPositionX(newWindowPositionX);
	SetWindowPositionY(newWindowPositionY);
	//glutPositionWindow(windowStatus.windowPositionX,windowStatus.windowPositionY);
	UpdateWindowDimension();
}

void CWindowManager::SetAndUpdateWindowWidth(int newWindowWidth)
{
	SetWindowWidth(newWindowWidth);
	//glutReshapeWindow(windowStatus.windowWidth, windowStatus.windowHeight);
	UpdateWindowDimension();
}

void CWindowManager::SetAndUpdateWindowHeight(int newWindowHeight)
{
	SetWindowHeight(newWindowHeight);
	//glutReshapeWindow(windowStatus.windowWidth, windowStatus.windowHeight);
	UpdateWindowDimension();
}

void CWindowManager::SetAndUpdateWindowPositionX(int newWindowPositionX)
{
	SetWindowPositionX(newWindowPositionX);
	glutPositionWindow(windowStatus.windowPositionX,windowStatus.windowPositionY);
	UpdateWindowPosition();
}

void CWindowManager::SetAndUpdateWindowPositionY(int newWindowPositionY)
{
	SetWindowPositionY(newWindowPositionY);
	//glutPositionWindow(windowStatus.windowPositionX,windowStatus.windowPositionY);
	UpdateWindowPosition();
}

void CWindowManager::SetAndUpdateFullScreen(bool fullscreen)
{
	//if(inited == false)//check for is this function used in first inited;
	//{
	//	if(fullscreen)
	//	{
	//		glutFullScreen();
	//		SetFullScreen(fullscreen);//update the boolean
	//	}
	//	return;
	//}

	if(windowStatus.fullScreen != fullscreen)
	{
		if(fullscreen)
		{
			glutFullScreen();
		}else
		{
			//glutPositionWindow(windowStatus.windowPositionX,windowStatus.windowPositionY);
			//glutReshapeWindow(windowStatus.windowWidth, windowStatus.windowHeight);
			Update();
		}
		SetFullScreen(fullscreen);//update the boolean
		return;
	}



}

void CWindowManager::PrintDebugDefaultWindowInformation()
{
	printf("\n");
	printf("\n FullScreen: %s", defaultWindowStatus.fullScreen?"true":"false");
	printf("\n Window Height: %d",defaultWindowStatus.windowHeight);
	printf("\n Window Width: %d",defaultWindowStatus.windowWidth);
	printf("\n Window Position X: %d",defaultWindowStatus.windowPositionX);
	printf("\n Window Position Y: %d",defaultWindowStatus.windowPositionY);
}

void CWindowManager::PrintDebugWindowInformation()
{
	printf("\n");
	printf("\n FullScreen: %s", windowStatus.fullScreen?"true":"false");
	printf("\n Window Height: %d",windowStatus.windowHeight);
	printf("\n Window Width: %d",windowStatus.windowWidth);
	printf("\n Window Position X: %d",windowStatus.windowPositionX);
	printf("\n Window Position Y: %d",windowStatus.windowPositionY);
}

void CWindowManager::PrintDebugInformation()
{
	CEntity::PrintDebugInformation();
	PrintDebugWindowInformation();
}