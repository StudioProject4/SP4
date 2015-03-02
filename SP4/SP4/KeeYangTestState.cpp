#include "myApplication.h"
#include "ObjectManager.h"
#include "KeeYangTestState.h"

#include "Mouse.h"
#include "Keyboard.h"
#include "LuaManager.h"
#include "FrameRateManager.h"
#include "GameStateManager.h"
#include "MusicSystem\MusicSystem.h"


CKeeYangTestState* CKeeYangTestState::instance = 0;

CKeeYangTestState::CKeeYangTestState(void)
{
}

CKeeYangTestState* CKeeYangTestState::GetInstance()
{
	if(instance == 0)
	{
		instance = new CKeeYangTestState();
	}
	return instance;
}

CKeeYangTestState::~CKeeYangTestState(void)
{
}

void CKeeYangTestState::SetHUD(bool m_bHUDmode)
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

void CKeeYangTestState::Render2D()
{
	
	
	//SP->RenderGrid();
	//SP->RenderSquare(400,300,100,100);
	//SP->RenderSquare(300,300,100,100);
	//SP->RenderSquare(200,300,100,100);
	//SP->RenderSquare(100,300,100,100);
	/*for(TBallVector::iterator it = ballList.begin(); it!= ballList.end(); ++it)
	{
		(*it)->Render();
	}*/
	//SP->RenderObjects();

	OM->SP->RenderGrid();
	OM->SP->RenderObjects();

	FRM->drawFPS();
}

void CKeeYangTestState::Render3D()
{
}

void CKeeYangTestState::RenderScene(void)
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

void CKeeYangTestState::InputKey(int key, int x, int y)
{
	switch (key) {
		case GLUT_KEY_LEFT : 
			keyboard->leftArrow = true;
			break;
		case GLUT_KEY_RIGHT : 
			keyboard->rightArrow = true;
			break;
		case GLUT_KEY_UP : 
			keyboard->upArrow = true;
			break;
		case GLUT_KEY_DOWN : 
			break;
	}
}

void CKeeYangTestState::InputUpKey(int key, int x, int y)
{
		switch (key) {
		case GLUT_KEY_LEFT : 
			keyboard->leftArrow = false;
			break;
		case GLUT_KEY_RIGHT : 
			keyboard->rightArrow = false;
			break;
		case GLUT_KEY_UP : 
			keyboard->upArrow = false;
			break;;
		case GLUT_KEY_DOWN : 
			break;
	}
}

void CKeeYangTestState::KeyboardDown(unsigned char key, int x, int y)
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
			//CGameStateManager::GetInstance()->ChangeState(myApplication::GetInstance());
			//this->PrintDebugInformation();
			GSM->PrintDebugInformation();
		break;

		case '3':
			MS->PrintBgmTrackList();
			MS->TranverseBgmTrack(false);
			break;
		case '4':
			SP->PrintDebugInformation();
			break;
		case '5':
			this->ballList[0]->SetVelocity(10,0);
			break;
		case '6':
			this->ballList[0]->SetVelocity(-10,0);
			break;
		case '7':
			this->ballList[0]->SetVelocity(0,10);
			break;
		case '8':
			this->ballList[0]->SetVelocity(0,-10);
			break;
		case '9':
			std::cout<<std::endl;
			std::cout<<"Ball pos"<<ballList[0]->pos<<std::endl;
			std::cout<<"Ball Top Left Point"<<ballList[0]->TopLeft<<std::endl;
			std::cout<<"Ball Bottom Right Point"<<ballList[0]->BottomRight<<std::endl;
			std::cout<<"Ball Top Left Cell Index"<<ballList[0]->TopLeftCellIndex<<std::endl;
			std::cout<<"Ball Bottom Right Cell Index"<<ballList[0]->BottomRightCellIndex<<std::endl;
			//this->ballList[0]->SetVelocity(0,0);
			break;
		case 'o':
			//SP->AddObjectNeo(ballList[0],&SP->cellList[4]);
			//for(short i = 0 ; i <SP->cellList[4].objectList.size();++i)
			//{
			//	SP->cellList[4].objectList[i]->PrintDebugInformation();
			//}

			//std::cout<<ballList[0]->ownerCellList.size()<<std::endl;
			std::cout<<std::endl;
			std::cout<<SP->GetCell(0,0)->objectList.size()<<std::endl;
			std::cout<<SP->GetCell(1,0)->objectList.size()<<std::endl;
			std::cout<<SP->GetCell(0,1)->objectList.size()<<std::endl;
			std::cout<<SP->GetCell(1,1)->objectList.size()<<std::endl;
			break;
		case 'c':
			system("cls");
			break;
		case 'p':
			for(short i = 0 ; i<ballList[0]->ownerCellList.size();++i)
			{
				std::cout<<ballList[0]->ownerCellList[i]<<std::endl;
			}
			break;
		case 'v':
			//SP->GetCell(0,0)->PrintDebugInformation();
			break;
		case 'b':
			//SP->GetCell(1,0)->PrintDebugInformation();
			GSM->ExitApplication();
			break;
		case 'n':
			//SP->GetCell(0,1)->PrintDebugInformation();
			GSM->GoBackLastState();
			break;
		case 'm':
			//SP->GetCell(1,1)->PrintDebugInformation();
			GSM->GoToPreviousState();
			break;
	}
}

void CKeeYangTestState::KeyboardUp(unsigned char key, int x, int y)
{
	//printf("\nMenuState KeyboardUp");
	keyboard->myKeys[key]= false;
}

void CKeeYangTestState::MouseMove (int x, int y)
{
	//printf("\nMenuState Mousemove");

	int diffX = x - mouse->lastX;
	int diffY = y - mouse->lastY;

	mouse->lastX = x;
	mouse->lastY = y;
}

void CKeeYangTestState::MouseClick(int button, int state, int x, int y)
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

void CKeeYangTestState::MouseWheel(int button, int dir, int x, int y)
{
	//printf("\nMenuState Mousewheel");
}

void CKeeYangTestState::changeSize (int w, int h)
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

bool CKeeYangTestState::Update()
{

	if(keyboard->myKeys['a'])
	{
		ballList[0]->SetVelocity(-5,0);
	}
	if(keyboard->myKeys['d'])
	{
		ballList[0]->SetVelocity(5,0);
	}
	if(keyboard->myKeys['w'])
	{
		ballList[0]->SetVelocity(0,-5);
	}
	if(keyboard->myKeys['s'])
	{
		ballList[0]->SetVelocity(0,5);
	}
	if(keyboard->myKeys['r'])
	{
		ballList[0]->radius *= 0.5;
	}
	if(keyboard->myKeys['t'])
	{
		ballList[0]->radius*=2;
	}
	if(keyboard->myKeys[VK_SPACE] == true)
	{
		ballList[0]->SetVelocity(0,0);
	}

	if(keyboard->myKeys[VK_ESCAPE] == true)
	{
		GSM->ExitApplication();
	}
	
	
	//SP->UpdateObjects();
	

	if(FRM->UpdateAndCheckTimeThreehold())
	{
		//std::cout<<"Update"<<std::endl;
		OM->Update();
	}

	return true;
}

bool CKeeYangTestState::Init()
{
	inited = true;
	
	name = "keeyangTest";
	genericTag = "CGameState";
	tag = "application";

	FRM = CFrameRateManager::GetInstance();
	LM = CLuaManager::GetInstance();
	mouse = CMouse::GetInstance();
	keyboard = CKeyboard::GetInstance();
	WM = CWindowManager::GetInstance();
	MS = CMusicSystem::GetInstance();
	OM = new CObjectManager();
	GSM = CGameStateManager::GetInstance();
	GSM->currentState = GSM->STATE_MENU;
	glEnable(GL_TEXTURE_2D);

	ball * newball = nullptr;

	newball = new ball;
	newball->SetPosition( 10,20);
	newball->id = 1;
	ballList.push_back(newball);

	//newball = new ball;
	//newball->SetPosition( 50,20);
	//newball->SetColour(1,1,1);
	//newball->id = 8;
	//ballList.push_back(newball);

	newball = new ball;
	newball->SetPosition(400,300);
	newball->SetColour(0,1,0);
	newball->radius = 100.f;
	ballList.push_back(newball);

	SP = new CSpatialPartion((short)WM->GetWindowWidth(),(short)WM->GetWindowHeight(),32,32);
	OM->ChangeSpatialParition(SP);
	for(short i2 = 0; i2<ballList.size();++i2)
	{
		OM->AddObject(ballList[i2]);
		
	}


	return true;
}

bool CKeeYangTestState::Reset()
{
	return Init();
}

bool CKeeYangTestState::CleanUp()
{
	std::cout<<"Test state clean up"<<std::endl;

	if(OM != 0)
	{
		delete OM;
		OM = 0;
	}

	//SP->NotifyAllObjectsAlreadyDeletedOutside();
	//delete SP;

	return true;
}
