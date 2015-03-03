
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



		MS->RegisterSound2D("sound1.mp3");
		MS->RegisterSound2D("sound2.mp3");
		MS->RegisterBgm2D("bgm1.mp3");
		MS->RegisterBgm2D("bgm2.mp3");
		MS->RegisterBgm2D("bgm3.mp3");
		MS->RegisterBgm2D("bgm4.mp3");
		MS->RegisterBgm2D("bgm5.mp3");
		MS->RegisterBgm2D("bgm6.mp3");
		MS->RegisterBgm2D("bgm7.mp3");
		MS->RegisterBgm2D("underthemoon.mp3");
		LM->Init("mylua.lua");
		

		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
		WM->Init(LM->GetWithCheckNumber<int>("WINDOW_WIDTH"),LM->GetWithCheckNumber<int>("WINDOW_HEIGHT"),LM->GetWithCheckNumber<int>("WINDOW_POSITION_X"),LM->GetWithCheckNumber<int>("WINDOW_POSITION_Y"),LM->GetWithCheckBoolean("FULLSCREEN"),LM->GetWithCheckString("PROGRAM_NAME").c_str());
		
		myApplication::argv=argv;
		
		IM->RegisterTGA("sonia2.tga");
		IM->RegisterTGA("kanon.tga");
		IM->RegisterTGA("kaede.tga");
		IM->RegisterTGA("tenri.tga");
		IM->RegisterTGA("rockyground.tga");
		GSM->ChangeState(CSplashState::GetInstance());
		//GSM->ChangeState(CMenuState::GetInstance());

		//GSM->ChangeState(myApplication::GetInstance());

		//glutInitWindowPosition(LM->GetWithCheckNumber<int>("WINDOW_POSITION_X"),LM->GetWithCheckNumber<int>("WINDOW_POSITION_Y"));
		//glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
		//glutCreateWindow(LM->GetWithCheckString("PROGRAM_NAME").c_str());
		//if(LM->GetWithCheckBoolean("FULLSCREEN") == true)
		//{
		//	glutFullScreen();
		//}
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
