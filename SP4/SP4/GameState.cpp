#include "GameState.h"


CGameState::CGameState(void)
	:inited(false)
	,GSM(0)
	,FRM(0)
	,LM(0)
	,WM(0)
	,MS(0)
	,OM(0)
	,mouse(0)
	,keyboard(0)
{
	testnumber = 10;
}


CGameState::~CGameState(void)
{
}
