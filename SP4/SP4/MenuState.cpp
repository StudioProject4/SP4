#include "myApplication.h"
#include "MenuState.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "LuaManager.h"
#include "FrameRateManager.h"
#include "GameStateManager.h"
#include "MusicSystem\MusicSystem.h"



CMenuState* CMenuState::instance = 0;

CMenuState::CMenuState(void)
{
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
		//glOrtho( 0, WM->GetWindowWidth() , WM->GetWindowHeight(), 0, -1, 1 );    
		glOrtho( 0, WM->GetOriginalWindowWidth() , WM->GetOriginalWindowHeight(), 0, -1, 1 );  
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
	SP->RenderObjects();
	/*for(TBallVector::iterator it = ballList.begin(); it!= ballList.end(); ++it)
	{
		(*it)->Render();
	}*/

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
	glutPostRedisplay();
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
			MS->TranverseBgmTrack(false);
			break;
		case '4':
			SP->PrintDebugInformation();
			break;
		case '5':
			this->ballList[0]->SetVelocity(1,0);
			break;
		case '6':
			SP->RemoveObject(this->ballList[0]);
			break;
		case '7':
			SP->UpdateObjectOwnerCell(ballList[0]);
			SP->PrintDebugInformation();
			break;
		case '8':
			SP->AddObject(this->ballList[0]);
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
	SP->UpdateObjects();

	if(keyboard->myKeys[VK_ESCAPE] == true)
	{
		exit(0);
	}

	if(FRM->UpdateAndCheckTimeThreehold())
	{
		for(TBallVector::iterator it = ballList.begin(); it!= ballList.end(); ++it)
		{
			(*it)->Update();
			SP->UpdateObjectOwnerCell((*it));
		}
		//SP->Update();
	}

	return true;
}

bool CMenuState::Init()
{
	inited = true;

	name = "menu";
	tag = "application";

	FRM = CFrameRateManager::GetInstance();
	LM = CLuaManager::GetInstance();
	mouse = CMouse::GetInstance();
	keyboard = CKeyboard::GetInstance();
	WM = CWindowManager::GetInstance();
	MS = CMusicSystem::GetInstance();
	OM = new CObjectManager();

	glEnable(GL_TEXTURE_2D);

	ball * newball = nullptr;

	newball = new ball;
	newball->SetPosition( 0,20);
	ballList.push_back(newball);

	newball = new ball;
	newball->SetPosition( 0,40);
	newball->SetColour(1,1,1);
	ballList.push_back(newball);

	newball = new ball;
	newball->SetPosition(0,60);
	newball->SetColour(1,0,0);
	ballList.push_back(newball);

	SP = new CSpatialPartion((short)WM->GetWindowWidth(),(short)WM->GetWindowHeight(),40,40);
	
	for(short i2 = 0; i2<ballList.size();++i2)
	{
		SP->AddObject(ballList[i2]);
	}
	//for(short i = 0 ; i<2000;++i)
	//{
	//	newball = new ball;
	//	ballList.push_back(newball);
	//}

	return true;
}

bool CMenuState::Reset()
{
	return true;
}

bool CMenuState::CleanUp()
{
	MS->Exit();
	if(OM != 0)
	{
		delete OM;
		OM = 0;
	}
	for(TBallVector::iterator it = ballList.begin(); it!= ballList.end(); ++it)
	{
		delete (*it);
	}
	return true;
}
