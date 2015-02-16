#pragma once
#include "gamestate.h"

class CMenuState :
	public CGameState
{
public:
	static CMenuState* instance;
private:
	CMenuState(void);
public:
	static CMenuState* GetInstance();
	~CMenuState(void);

	void InputKey(int key, int x, int y);
	void KeyboardDown(unsigned char key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);
	void MouseMove (int x, int y);
	void MouseClick(int button, int state, int x, int y);
	void MouseWheel(int button, int dir, int x, int y);
	void changeSize (int w, int h);

	void RenderScene(void);
	void SetHUD(bool m_bHUDmode);
	void Render2D();
	void Render3D();
	bool Update();
	bool Init();
	bool Reset();
	bool CleanUp();
};

