#pragma once
#include "Entity.h"
#include "GlobalVariable.h"

class CGameStateManager;
class CFrameRateManager;
class CLuaManager;
class CMouse;
class CKeyboard;

class CGameState:public CEntity
{
public:
	int testnumber;

protected:
	CGameStateManager* GSM;
	CFrameRateManager* FRM;
	CLuaManager* LM;
	CMouse* mouse;
	CKeyboard* keyboard;

	bool inited;
public:
	CGameState(void);
	virtual ~CGameState(void);

	virtual void InputKey(int key, int x, int y) = 0 ;
	virtual void KeyboardDown(unsigned char key, int x, int y) = 0;
	virtual void KeyboardUp(unsigned char key, int x, int y) = 0;
	virtual void MouseMove (int x, int y) = 0;
	virtual void MouseClick(int button, int state, int x, int y) = 0;
	virtual void MouseWheel(int button, int dir, int x, int y) = 0;
	virtual void changeSize (int w, int h) = 0;

	virtual void SetHUD(bool m_bHUDmode) = 0;
	virtual void Render2D() = 0;
	virtual void Render3D() = 0;
	virtual void RenderScene(void) = 0;

	inline bool CheckInitedBefore()
	{
		return inited;
	};
};

