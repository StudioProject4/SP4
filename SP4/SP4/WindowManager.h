#pragma once
#include "entity.h"
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <string>
class CWindowStatus
{
public:
	int windowHeight;
	int windowWidth;
	int OldwindowHeight;
	int OldwindowWidth;
	int windowPositionX;
	int windowPositionY;
	
	float ratioDiffX;
	float ratioDiffY;

	bool fullScreen;
	std::string programName;
	CWindowStatus()
		:
		 windowHeight(600)
		,OldwindowHeight(windowHeight)
		,windowWidth(800)
		,OldwindowWidth(windowWidth)
		,windowPositionX(50)
		,windowPositionY(50)
		,fullScreen(false)
		,ratioDiffX(1)
		,ratioDiffY(1)
		,programName("sp4")
	{};
	void Set(int windowWidth,int windowHeight ,int windowPositionX,int windowPositionY ,bool fullScreen )
	{
		this->windowWidth = windowWidth;
		this->windowHeight = windowHeight;
		this->windowPositionX = windowPositionX;
		this->windowPositionY = windowPositionY;
		this->fullScreen = fullScreen;
		CalculateWindowDifferRatio();
	};
	void CalculateWindowDifferRatio()
	{
		ratioDiffX = ((float)windowWidth/OldwindowWidth);
		ratioDiffY = ((float)windowHeight/OldwindowHeight);
	};
};

class CWindowManager :
	public CEntity
{
private:
	CWindowStatus windowStatus;
	CWindowStatus defaultWindowStatus;
	bool inited;

public:
	static CWindowManager* instance;
private:
	bool Init();
	CWindowManager(void);

	inline void SetWindowWidth(int newWindowWidth)
	{
		windowStatus.windowWidth = newWindowWidth;
	};

	inline void SetWindowHeight(int newWindowHeight)
	{
		windowStatus.windowHeight = newWindowHeight;
	};
public:
	static CWindowManager* GetInstance();
	~CWindowManager(void);

	void SetAndUpdateWindowWidth(int newWindowWidth);
	void SetAndUpdateWindowHeight(int newWindowHeight);
	void SetAndUpdateWindowPositionX(int newWindowPositionX);
	void SetAndUpdateWindowPositionY(int newWindowPositionY);
	void SetAndUpdateFullScreen(bool fullscreen);
	void SetAndUpdateWindowDimension(int newWindowWidth,int newWindowHeight);
	void SetAndUpdateWindowPosition(int newWindowPositionX,int newWindowPositionY);
	bool Update();
	bool Init(int windowWidth,int windowHeight = 600,int windowPositionX = 50,int windowPositionY = 50,bool fullScreen = false,std::string programName = "newWindow");
	bool Reset();
	bool CleanUp();
	void PrintDebugDefaultWindowInformation();
	void PrintDebugWindowInformation();
	void PrintDebugInformation();
	
	inline void UpdateWindowDimension()
	{		
		glutReshapeWindow(windowStatus.windowWidth, windowStatus.windowHeight);
	};
	inline void UpdateWindowPosition()
	{
		glutPositionWindow(windowStatus.windowPositionX,windowStatus.windowPositionY);
	};
	inline void CreateGlutWindow(std::string programname)
	{
		glutCreateWindow(programname.c_str());
	};
	inline void CreateGlutWindow(char * programname)
	{
		glutCreateWindow(programname);
	};
	inline void CreateGlutWindow(const char * programname)
	{
		glutCreateWindow(programname);
	};
	inline int GetWindowWidth()
	{
		return windowStatus.windowWidth;
	};

	inline int GetWindowHeight()
	{
		return windowStatus.windowHeight;
	};

	inline int GetWindowPositionX()
	{
		return windowStatus.windowPositionX;
	};

	inline int GetWindowPositionY()
	{
		return windowStatus.windowPositionY;
	};

	inline bool GetFullScreen()
	{
		return windowStatus.fullScreen;
	};
	inline std::string GetProgramName()
	{
		return windowStatus.programName;
	};
	inline std::string GetDefaultProgramName()
	{
		return defaultWindowStatus.programName;
	};

public:
	//setter//without updates to the glutscreen
	inline int GetOriginalWindowHeight()
	{
		return windowStatus.OldwindowHeight;
	};
	inline int GetOriginalWindowWidth()
	{
		return windowStatus.OldwindowWidth;
	};
	inline void SetWindowDimension(int newWindowWidth,int newWindowHeight)
	{
		SetWindowWidth(newWindowWidth);
		SetWindowHeight(newWindowHeight);
		windowStatus.CalculateWindowDifferRatio();
	};
	inline void SetWindowPositionX(int newWindowPositionX)
	{
		windowStatus.windowPositionX = newWindowPositionX;
	};

	inline void SetWindowPositionY(int newWindowPositionY)
	{
		windowStatus.windowPositionY = newWindowPositionY;
	};
	inline void SetWindowPosition(int newWindowPositionX,int newWindowPositionY)
	{
		SetWindowPositionX(newWindowPositionX);
		SetWindowPositionY(newWindowPositionY);
	};
	inline void SetFullScreen(bool fullscreen)
	{
		windowStatus.fullScreen = fullscreen;
	};
	inline float GetWindowRatioDifferenceX()
	{
		return windowStatus.ratioDiffX;
	};
	inline float GetWindowRatioDifferenceY()
	{
		return windowStatus.ratioDiffY;
	};
};

