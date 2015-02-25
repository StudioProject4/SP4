#include "GameStateManager.h"
#include "GameState.h"

CGameStateManager* CGameStateManager::instance = 0;

CGameStateManager::CGameStateManager(void)
{
}


CGameStateManager::~CGameStateManager(void)
{
}

CGameStateManager* CGameStateManager::GetInstance()
{
	if(instance == 0)
	{
		instance = new CGameStateManager();
	}
	return instance;
}

bool CGameStateManager::ChangeState(CGameState* newstate)
{
	if(!gamestatestack.empty())
	{
		gamestatestack.pop();
	}

	
	if(newstate->CheckInitedBefore() == false)
	{
		return PushAndInitNewState(newstate);	
	}else
	{
		gamestatestack.push(newstate);
	}

	return true;
}

bool CGameStateManager::PushAndInitNewState(CGameState* newstate)
{
	if(newstate->Init())
	{
		gamestatestack.push(newstate);
		return true;
	}
	printf("Error Initing newstate");
	return false;
}

bool CGameStateManager::PopAndCleanLastState()
{
	if(!gamestatestack.empty())
	{
		bool result = gamestatestack.top()->CleanUp();
		gamestatestack.pop();
		return result;
	}
	return false;
}

//void CGameStateManager::PushState(CGameState* newstate)
//{
//
//}
//
//void CGameStateManager::PopState()
//{
//
//}
void CGameStateManager::CleanUpUponExit(void)
{
	//gamestatestack.top()->CleanUp();
	PopAndCleanLastState();
}
void CGameStateManager::RenderScene(void)
{
	gamestatestack.top()->RenderScene();
	//glutPostRedisplay();
}

void CGameStateManager::Update(void)
{
	gamestatestack.top()->Update();
}
void CGameStateManager::InputUpKey(int key, int x, int y)
{
	gamestatestack.top()->InputUpKey(key,x,y);
}
void CGameStateManager::InputKey(int key, int x, int y)
{
	gamestatestack.top()->InputKey(key,x,y);
}

void CGameStateManager::KeyboardDown(unsigned char key, int x, int y)
{
	gamestatestack.top()->KeyboardDown(key,x,y);
}

void CGameStateManager::KeyboardUp(unsigned char key, int x, int y) 
{
	gamestatestack.top()->KeyboardUp(key,x,y);
}

void CGameStateManager::MouseMove (int x, int y) 
{
	gamestatestack.top()->MouseMove(x,y);
}

void CGameStateManager::MouseClick(int button, int state, int x, int y) 
{
	gamestatestack.top()->MouseClick(button,state,x,y);
}

void CGameStateManager::MouseWheel(int button, int dir, int x, int y)
{
	gamestatestack.top()->MouseWheel(button,dir,x,y);
}

void CGameStateManager::changeSize (int w, int h)
{
	gamestatestack.top()->changeSize(w,h);
}