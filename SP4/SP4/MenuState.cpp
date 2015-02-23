#include "MenuState.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "LuaManager.h"
#include "FrameRateManager.h"
#include "GameStateManager.h"
#include "MusicSystem\MusicSystem.h"
#include "myApplication.h"


CMenuState* CMenuState::instance;

CMenuState::CMenuState(void)
{
	Init();
}
CMenuState* CMenuState::GetInstance()
{
	if(instance == 0)
	{
		instance = new CMenuState();
	}
	return instance;
}

CMenuState::~CMenuState(void)
{
}

void CMenuState::SetHUD(bool m_bHUDmode)
{
	if (m_bHUDmode == true)
	{
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho( 0, WM->GetWindowWidth() , WM->GetWindowHeight(), 0, -1, 1 );    
		//std::cout<<"Window width"<<WINDOW_WIDTH<<std::endl;
		//std::cout<<"Window Height"<<WINDOW_HEIGHT<<std::endl;
		//glOrtho( 0, 800 , 600, 0, -1, 1 );      
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_TEXTURE_2D);							// Disable Texture Mapping ( NEW )
	}
	else
	{
		//glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glEnable( GL_DEPTH_TEST );

	}
}

void CMenuState::Render2D()
{
	FRM->drawFPS();
}

void CMenuState::Render3D()
{
}

void CMenuState::RenderScene(void)
{
	//printf("\nMenuState RenderScene");

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);


	Render3D();

	SetHUD( true );
		Render2D();
	SetHUD( false );

	// Flush off any entity which is not drawn yet, so that we maintain the frame rate.
	glFlush();

	// swapping the buffers causes the rendering above to be shown
	glutSwapBuffers();
}

void CMenuState::InputKey(int key, int x, int y)
{
	//printf("\nMenuState inputkey");

	switch (key) {
		case GLUT_KEY_LEFT : 
			break;
		case GLUT_KEY_RIGHT : 
			break;
		case GLUT_KEY_UP : 
			break;
		case GLUT_KEY_DOWN : 
			break;
	}
}

void CMenuState::KeyboardDown(unsigned char key, int x, int y)
{
	//printf("\nMenuState KeyboardDown");
	keyboard->myKeys[key] = true;

	switch(key)
	{
		case '1':
			this->PrintDebugInformation();
			//mouse->PrintDebugInformation();
		break;

		case '2':
			CGameStateManager::GetInstance()->ChangeState(myApplication::GetInstance());
			this->PrintDebugInformation();
		break;

		case '3':
			MS->PrintBgmTrackList();
			MS->TranverseBGMTrack(false);
			break;
	}
}

void CMenuState::KeyboardUp(unsigned char key, int x, int y)
{
	//printf("\nMenuState KeyboardUp");
	keyboard->myKeys[key]= false;
}

void CMenuState::MouseMove (int x, int y)
{
	//printf("\nMenuState Mousemove");

	int diffX = x - mouse->lastX;
	int diffY = y - mouse->lastY;

	mouse->lastX = x;
	mouse->lastY = y;
}

void CMenuState::MouseClick(int button, int state, int x, int y)
{
	//printf("\nMenuState Mouseclick");

	mouse->lastX = x;
	mouse->lastY = y;

	switch (button) {

		case GLUT_LEFT_BUTTON:
			mouse->mLButtonUp = state;		
			break;

		case GLUT_RIGHT_BUTTON:
			mouse->mRButtonUp = state;		
			break;

		case GLUT_MIDDLE_BUTTON:
			mouse->middleButtonUp = state;
			break;
	}
}

void CMenuState::MouseWheel(int button, int dir, int x, int y)
{
	//printf("\nMenuState Mousewheel");
}

void CMenuState::changeSize (int w, int h)
{
	//printf("\nMenuState ChangeSize");

		// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	float ratio = (float) (1.0f* w / h);

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	//WINDOW_WIDTH = w;
	//WINDOW_HEIGHT = h;
	WM->SetWindowDimension(w,h);
	//std::cout<<"menustate "<<WINDOW_WIDTH<<std::endl;
	// Set the correct perspective.
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
}

bool CMenuState::Update()
{
	//printf("\nMenuState Update");
		//	if(keyboard->myKeys['1'] == true)
		//{
		//	this->PrintDebugInformation();
		//	//WM->PrintDebugInformation();
		//	//this->PrintDebugInformation();
		//	//std::cout<<"Window width"<<WINDOW_WIDTH<<std::endl;
		//	//std::cout<<"Window Height"<<WINDOW_HEIGHT<<std::endl;
		//}
		//if(keyboard->myKeys['2'] == true)
		//{
		//	CGameStateManager::GetInstance()->ChangeState(myApplication::GetInstance());
		//}

	if(keyboard->myKeys[VK_ESCAPE] == true)
	{
		exit(0);
	}
	if(FRM->UpdateAndCheckTimeThreehold())
	{

	}

	return true;
}

bool CMenuState::Init()
{
	inited = true;

	name = "menu";
	tag = "application";

	mouse = CMouse::GetInstance();
	keyboard = CKeyboard::GetInstance();
	FRM = CFrameRateManager::GetInstance();
	LM = CLuaManager::GetInstance();
	WM = CWindowManager::GetInstance();
	MS = CMusicSystem::GetInstance();

	glEnable(GL_TEXTURE_2D);

	return true;
}

bool CMenuState::Reset()
{
	return true;
}

bool CMenuState::CleanUp()
{
	return true;
}
