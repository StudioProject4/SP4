#pragma once
#include "gamestate.h"
#include "ChineseMale.h"
#include "Vector3.h"
#include "RenderUntilty.h"
#include "LeverDoor.h"
#include "TestObject.h"


class KennardTestState :
	public CGameState
{
public:
	static KennardTestState* s_instance;
	static KennardTestState* GetInstance()
	{
		if(s_instance==0)
			s_instance=new KennardTestState;
		return s_instance;
	}

	//test object
	CTestObject test;
	//end of test object
	
	CLeverDoor theLever;

	void InputKey(int key,int x,int y);
	void InputUpKey(int key, int x, int y){};
	void KeyboardDown(unsigned char key,int x,int y);
	void KeyboardUp(unsigned char key,int x,int y);
	void MouseMove(int x,int y);
	void MouseClick(int button,int state,int x,int y);
	void MouseWheel(int button,int dir,int x,int y);
	
	void changeSize(int w,int h);
	void SetHUD(bool m_bHUDmode);
	
	void Render2D();
	void Render3D();
	void RenderScene(void);
	
	bool Update();
	bool Init();
	bool Reset();
	bool CleanUp();

	KennardTestState(void);
	~KennardTestState(void);
};

