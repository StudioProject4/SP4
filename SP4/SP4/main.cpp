#include "SystemDefination.h"
#include "myApplication.h"

int WINDOW_WIDTH;
int WINDOW_HEIGHT;
void changeSize(int w, int h) {
	//myApplication::GetInstance()->changeSize(w,h);
	CGameStateManager::GetInstance()->changeSize(w,h);
}

void renderScene(void) {
	//myApplication::GetInstance()->RenderScene();
	CGameStateManager::GetInstance()->RenderScene();
}

void inputKey(int key, int x, int y) {
	//myApplication::GetInstance()->InputKey(key,x,y);
	CGameStateManager::GetInstance()->InputKey(key,x,y);
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

		CGameStateManager* GSM = CGameStateManager::GetInstance();
		GSM->ChangeState(myApplication::GetInstance());
		
		CLuaManager* LM = CLuaManager::GetInstance();
		LM->Init("mylua.lua");
		WINDOW_WIDTH = LM->GetWithCheckNumber<int>("WINDOW_WIDTH");
		WINDOW_HEIGHT = LM->GetWithCheckNumber<int>("WINDOW_HEIGHT");

		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
		glutInitWindowPosition(LM->GetWithCheckNumber<int>("WINDOW_POSITION_X"),LM->GetWithCheckNumber<int>("WINDOW_POSITION_Y"));
		glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
		glutCreateWindow(LM->GetWithCheckString("PROGRAM_NAME").c_str());
		if(LM->GetWithCheckBoolean("FULLSCREEN") == true)
		{
			glutFullScreen();
		}
		atexit(CleanUpUponExit);

		glutReshapeFunc(changeSize);
		glutDisplayFunc(renderScene);
		glutIdleFunc(renderScene);
		//	glutSpecialFunc(inputKey);
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
