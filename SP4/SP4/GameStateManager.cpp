#include "GameStateManager.h"
#include "GameState.h"

#include "MusicSystem\MusicSystem.h"
#include "ImageManager.h"
#include "FrameRateManager.h"
#include "LuaManager.h"
#include "WindowManager.h"

//#define DEFENSIVE_CODE

CGameStateManager* CGameStateManager::instance = 0;

CGameStateManager::CGameStateManager(void)
	:lastState(nullptr)
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
	//if(!gamestatestack.empty())
	//{
	//	gamestatestack.pop_back();
	//}

	
	if(newstate->CheckInitedBefore() == false)
	{
		return PushAndInitNewState(newstate);	
	}else
	{
		RecordLastState();
		//gamestatestack.push(newstate);
		gamestatestack.push_back(newstate);
	}

	return true;
}
void CGameStateManager::RecordLastState()
{
	if(!gamestatestack.empty())
	{
		lastState = gamestatestack.back();
	}
}
bool CGameStateManager::PushAndInitNewState(CGameState* newstate)
{
	if(newstate->Init())
	{
		//gamestatestack.push(newstate);
		RecordLastState();
		gamestatestack.push_back(newstate);
		return true;
	}
	printf("Error Initing newstate");
	return false;
}

bool CGameStateManager::PopAndCleanLastState()
{
	if(!gamestatestack.empty())
	{
		//bool result = gamestatestack.top()->CleanUp();
		//gamestatestack.pop();
		RecordLastState();
		bool result = gamestatestack.back()->CleanUp();
		gamestatestack.pop_back();

		if(gamestatestack.empty())
		{
			ExitApplication();
		}

		return result;
	}
	return false;
}

void CGameStateManager::CleanUpUponExit(void)
{
	//gamestatestack.top()->CleanUp();
	PopAndCleanLastState();
}
void CGameStateManager::RenderScene(void)
{
	//gamestatestack.top()->RenderScene();
#ifdef DEFENSIVE_CODE
	if(!gamestatestack.empty())
	{
		gamestatestack.back()->RenderScene();
	}
#else
	gamestatestack.back()->RenderScene();
#endif

}

void CGameStateManager::Update(void)
{
	//gamestatestack.top()->Update();

#ifdef DEFENSIVE_CODE
	if(!gamestatestack.empty())
	{
		gamestatestack.back()->Update();
	}
#else
	gamestatestack.back()->Update();
#endif

}

void CGameStateManager::InputUpKey(int key, int x, int y)
{
	//gamestatestack.top()->InputUpKey(key,x,y);

#ifdef DEFENSIVE_CODE
	if(!gamestatestack.empty())
	{
		gamestatestack.back()->InputUpKey(key,x,y);
	}
#else
	gamestatestack.back()->InputUpKey(key,x,y);
#endif

}

void CGameStateManager::InputKey(int key, int x, int y)
{
	//gamestatestack.top()->InputKey(key,x,y);

#ifdef DEFENSIVE_CODE
	if(!gamestatestack.empty())
	{
		gamestatestack.back()->InputKey(key,x,y);
	}
#else
	gamestatestack.back()->InputKey(key,x,y);
#endif

}

void CGameStateManager::KeyboardDown(unsigned char key, int x, int y)
{
	//gamestatestack.top()->KeyboardDown(key,x,y);
	//gamestatestack.back()->KeyboardDown(key,x,y);

#ifdef DEFENSIVE_CODE
	if(!gamestatestack.empty())
	{
		gamestatestack.back()->KeyboardDown(key,x,y);
	}
#else
	gamestatestack.back()->KeyboardDown(key,x,y);
#endif

}

void CGameStateManager::KeyboardUp(unsigned char key, int x, int y) 
{
	//gamestatestack.top()->KeyboardUp(key,x,y);

#ifdef DEFENSIVE_CODE
	if(!gamestatestack.empty())
	{
		gamestatestack.back()->KeyboardUp(key,x,y);
	}
#else
	gamestatestack.back()->KeyboardUp(key,x,y);
#endif

}

void CGameStateManager::MouseMove (int x, int y) 
{
	//gamestatestack.top()->MouseMove(x,y);

#ifdef DEFENSIVE_CODE
	if(!gamestatestack.empty())
	{
		gamestatestack.back()->MouseMove(x,y);
	}
#else
	gamestatestack.back()->MouseMove(x,y);
#endif

}

void CGameStateManager::MouseClick(int button, int state, int x, int y) 
{
	//gamestatestack.top()->MouseClick(button,state,x,y);

#ifdef DEFENSIVE_CODE
	if(!gamestatestack.empty())
	{
		gamestatestack.back()->MouseClick(button,state,x,y);
	}
#else
	gamestatestack.back()->MouseClick(button,state,x,y);
#endif

}

void CGameStateManager::MouseWheel(int button, int dir, int x, int y)
{
	//gamestatestack.top()->MouseWheel(button,dir,x,y);

#ifdef DEFENSIVE_CODE
	if(!gamestatestack.empty())
	{
		gamestatestack.back()->MouseWheel(button,dir,x,y);
	}
#else
	gamestatestack.back()->MouseWheel(button,dir,x,y);
#endif

}

void CGameStateManager::changeSize (int w, int h)
{
	//gamestatestack.top()->changeSize(w,h);

#ifdef DEFENSIVE_CODE
	if(!gamestatestack.empty())
	{
		gamestatestack.back()->changeSize(w,h);
	}
#else
	gamestatestack.back()->changeSize(w,h);
#endif

}

void CGameStateManager::GoBackLastState()
{
	if(lastState)
	{
		ChangeState(lastState);
	}
}

void CGameStateManager::GoToPreviousState()
{
	if(!gamestatestack.empty())
	{
		lastState = gamestatestack.back();
		gamestatestack.pop_back();

		if(gamestatestack.empty())
		{
			ExitApplication();
		}

	}
}
bool CGameStateManager::CleanUp()
{
	gamestatestack.clear();
	if(CMusicSystem::GetInstance()->Exit() && CImageManager::GetInstance()->Exit()&& CFrameRateManager::GetInstance()->Exit() && CWindowManager::GetInstance()->Exit())
	{
		return true;
	}
	return false;
}

void CGameStateManager::ExitApplication()
{
	//if all singeton object exit successfully then exit(0)
	//static int called = 0 ;
	//called++;

	//printf("\n exiting program %d",called);

	if(CleanUp())
	{	
		printf("\nsafely exit");
		
	}else
	{
		printf("\nUnsafely exit");
	}
	
	exit(0);
}

void CGameStateManager::PrintDebugInformation()
{
	if(!gamestatestack.empty())
	{

		printf("Size of game state stack %d ",gamestatestack.size());

		for(TGameStateList::iterator it = gamestatestack.begin(); it != gamestatestack.end(); ++it)
		{
			printf("\nGame State Name:  %s ", (*it)->name);
		}
	}
}