#pragma once
#include "gamestate.h"

#include "TestBallObject.h"
#include <vector>

class CSpatialPartion;

class CKeeYangTestState :
	public CGameState
{
public:
	static CKeeYangTestState* instance;
private:
	CKeeYangTestState(void);

	typedef std::vector<ball*> TBallVector;
	TBallVector ballList;
	CSpatialPartion * SP;
public:
	static CKeeYangTestState* GetInstance();
	~CKeeYangTestState(void);

	void InputKey(int key, int x, int y);
	void InputUpKey(int key, int x, int y);
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

