
#include "myApplication.h"


#include "SystemDefination.h"

void changeSize(int w, int h) {
	//myApplication::GetInstance()->changeSize(w,h);
	CGameStateManager::GetInstance()->changeSize(w,h);
}

void renderScene(void) {
	//myApplication::GetInstance()->RenderScene();
	CGameStateManager::GetInstance()->RenderScene();
}

void update(void) {
	//myApplication::GetInstance()->RenderScene();
	CGameStateManager::GetInstance()->Update();
}

void inputKey(int key, int x, int y) {
	//myApplication::GetInstance()->InputKey(key,x,y);
	CGameStateManager::GetInstance()->InputKey(key,x,y);
}
void inputUpKey(int key, int x, int y) {
	//myApplication::GetInstance()->InputKey(key,x,y);
	CGameStateManager::GetInstance()->InputUpKey(key,x,y);
}
void KeyboardDown(unsigned char key, int x, int y){
	//myApplication::GetInstance()->KeyboardDown(key,x,y);
	CGameStateManager::GetInstance()->KeyboardDown(key,x,y);
}

void KeyboardUp(unsigned char key, int x, int y){
	//myApplication::GetInstance()->KeyboardUp(key,x,y);
	CGameStateManager::GetInstance()->KeyboardUp(key,x,y);
}

void MouseMove(int x, int y){
	//myApplication::GetInstance()->MouseMove(x,y);
	CGameStateManager::GetInstance()->MouseMove(x,y);
}

void MouseClick(int button, int state, int x, int y){
	//myApplication::GetInstance()->MouseClick(button, state, x, y);
	CGameStateManager::GetInstance()->MouseClick(button,state,x,y);
}
void mouseWheel(int button, int dir, int x, int y) {
	//myApplication::GetInstance()->MouseWheel(button,dir,x,y);
	CGameStateManager::GetInstance()->MouseWheel(button, dir, x, y);
}
void CleanUpUponExit(void)
{
	//myApplication::GetInstance()->CleanUp();
	//myApplication::getInstance()->theGSM->getInstance()->getCurrentState()->Cleanup();
	CGameStateManager::GetInstance()->CleanUpUponExit();
}



int main(int argc, char **argv )
{
		CWindowManager* WM = CWindowManager::GetInstance();
		CGameStateManager* GSM = CGameStateManager::GetInstance();
		CLuaManager* LM = CLuaManager::GetInstance();
		CMusicSystem* MS = CMusicSystem::GetInstance();
		CImageManager* IM = CImageManager::GetInstance();

		LM->Init("mylua.lua");

		MS->RegisterSound2D(LM->GetWithCheckString("TEST_SOUND"));
		MS->RegisterBgm2D(LM->GetWithCheckString("MENU_BGM"));
		MS->RegisterBgm2D(LM->GetWithCheckString("MAIN_GAME_BGM"));
		MS->RegisterBgm2D(LM->GetWithCheckString("INTRO_SCENE_BGM"));

		//MS->RegisterSound2D("sound1.mp3");
		//MS->RegisterBgm2D("persona.mp3");
		//MS->RegisterBgm2D("underthemoon.mp3");
		//MS->RegisterBgm2D("FilmRolling.mp3");

		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
		WM->Init(LM->GetWithCheckNumber<int>("WINDOW_WIDTH"),LM->GetWithCheckNumber<int>("WINDOW_HEIGHT"),LM->GetWithCheckNumber<int>("WINDOW_POSITION_X"),LM->GetWithCheckNumber<int>("WINDOW_POSITION_Y"),LM->GetWithCheckBoolean("FULLSCREEN"),LM->GetWithCheckString("PROGRAM_NAME").c_str());
		
		myApplication::argv=argv;

#ifdef PRELOAD_TEXTURE
		IM->RegisterTGA("sonia2.tga");
		IM->RegisterTGA("kanon.tga");
		IM->RegisterTGA("kaede.tga");
		IM->RegisterTGA("tenri.tga");
		IM->RegisterTGA("rockyground.tga");
		IM->RegisterTGA("flare.tga");
		IM->RegisterTGA("MuteButton.tga");
		IM->RegisterTGA("UnMuteButton.tga");
		IM->RegisterTGA("BackButton.tga");
		IM->RegisterTGA("ExitButton.tga");
		IM->RegisterTGA("CreateGameButton.tga");
		IM->RegisterTGA("JoinGameButton.tga");
		IM->RegisterTGA("MultiPlayerButton.tga");
		IM->RegisterTGA("OptionButton.tga");
		IM->RegisterTGA("SettingButton.tga");
		IM->RegisterTGA("SinglePlayerButton.tga");
		IM->RegisterTGA("CreditButton.tga");
		IM->RegisterTGA("BackButton.tga");
		IM->RegisterTGA("pointIcon.tga");
		IM->RegisterTGA("health.tga");
		IM->RegisterTGA("background.tga");
		IM->RegisterTGA("credit.tga");
		IM->RegisterTGA("InstructionButton.tga");
		IM->RegisterTGA("Instruction.tga");
		IM->RegisterTGA("optionpage.tga");
		IM->RegisterTGA("IntroScene.tga");
		IM->RegisterTGA("mainmenu.tga");
		IM->RegisterTGA("GameOver.tga");
		IM->RegisterTGA("GameOverDisplay.tga");
#endif
		//IM->RegisterTGA("pointIcon.tga");

		GSM->ChangeState(CSplashState::GetInstance());
		//GSM->ChangeState(CMenuState::GetInstance());

		//GSM->ChangeState(CSplashState::GetInstance());
		//GSM->ChangeState(CMenuState::GetInstance());

		//GSM->ChangeState(myApplication::GetInstance());

		//glutInitWindowPosition(LM->GetWithCheckNumber<int>("WINDOW_POSITION_X"),LM->GetWithCheckNumber<int>("WINDOW_POSITION_Y"));
		//glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
		//glutCreateWindow(LM->GetWithCheckString("PROGRAM_NAME").c_str());
		if(LM->GetWithCheckBoolean("FULLSCREEN") == true)
		{
			glutFullScreen();
		}
		atexit(CleanUpUponExit);

		glutReshapeFunc(changeSize);
		glutDisplayFunc(renderScene);
		glutIdleFunc(update);
		//	glutSpecialFunc(inputKey);
		//glutIdleFunc(renderScene);
		glutSpecialFunc(inputKey);
		glutSpecialUpFunc(inputUpKey);
		glutKeyboardFunc(KeyboardDown);
		glutKeyboardUpFunc(KeyboardUp);
		glutPassiveMotionFunc(MouseMove);
		glutMouseFunc(MouseClick);// for mouse click
		glutMouseWheelFunc(mouseWheel);
		//if (myApplication::GetInstance()->Init() == true)
		//{
			glutMainLoop();
		//}
		//else
		//{
		//	printf("Error Initialising Program\n");
		////	return 1;
		//}
		
		


		return 0;
};
