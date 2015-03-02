#pragma once
#include <stack>
#include <deque>
#include <vector>
class CGameState;

class CGameStateManager
{
public:
	enum EGameStateType
	{
		STATE_NONE,
		STATE_MYAPPLICATION,
		STATE_MENU,
		STATE_TOTAL
	};
	EGameStateType currentState;

	static CGameStateManager* instance;
private:
	typedef std::vector<CGameState*> TGameStateVector;
	typedef std::stack<CGameState*> TGameStateStack;
	typedef std::deque<CGameState*> TGameStateDeque;

	typedef TGameStateDeque TGameStateList;
	TGameStateList gamestatestack;

	CGameStateManager(void);
	CGameState* lastState;
public:

	static CGameStateManager* GetInstance();
	~CGameStateManager(void);

	bool ChangeState(CGameState* newstate);
	bool PushAndInitNewState(CGameState* newstate);
	bool PopAndCleanLastState();
	//bool BackPreviousState();
	//void PushState(CGameState* newstate);
	//void PopState();

	//relay the message.
	 void InputKey(int key, int x, int y);
	 void InputUpKey(int key, int x, int y);
	 void KeyboardDown(unsigned char key, int x, int y);
	 void KeyboardUp(unsigned char key, int x, int y) ;
	 void MouseMove (int x, int y) ;
	 void MouseClick(int button, int state, int x, int y) ;
	 void MouseWheel(int button, int dir, int x, int y);
	 void changeSize (int w, int h);
	 void RenderScene(void);
	 void Update(void);
	 void CleanUpUponExit(void);
	
	 void GoBackLastState();
	 void GoToPreviousState();
	 void RecordLastState();

	 bool CleanUp();
	 void ExitApplication();

	 void PrintDebugInformation();
};

