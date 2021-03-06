#pragma once
#include "gamestate.h"

#include "Sprite.h"
#include <vector>

class COnlinePlayState :
	public CGameState
{
public:
	static COnlinePlayState* instance;
private:
	CSprite backgroundImage[1];
	typedef std::vector<CUIButton*> TButtonList;
	TButtonList buttonList;
	int internalState;
	std::string ip;
private:
	COnlinePlayState(void);

	STARTUPINFO si;     
	PROCESS_INFORMATION pi;
	
	void startupServer(LPCTSTR lpApplicationName);
	void closeServer(void);
public:
	static COnlinePlayState* GetInstance();
	
	~COnlinePlayState(void);

	 void InputKey(int key, int x, int y);
	 void InputUpKey(int key, int x, int y);
	 void KeyboardDown(unsigned char key, int x, int y);
	 void KeyboardUp(unsigned char key, int x, int y);
	 void MouseMove (int x, int y);
	 void MouseClick(int button, int state, int x, int y);
	 void MouseWheel(int button, int dir, int x, int y);
	 void changeSize (int w, int h);
//
	 void SetHUD(bool m_bHUDmode);
	 void Render2D();
	 void Render3D();
	 void RenderScene(void);
	 void ButtonTriggerCall(std::string buttonName);
	 void RenderBackground();

	 bool Update();
	 bool Init();
	 bool Reset();
	 bool CleanUp();
};

