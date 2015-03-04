#include "OnlinePlayState.h"

#include "ObjectManager.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "LuaManager.h"
#include "WindowManager.h"
#include "FrameRateManager.h"
#include "GameStateManager.h"
#include "ImageManager.h"
#include "MusicSystem\MusicSystem.h"

#include "UIButtonCircle.h"
#include "UIButtonRectangle.h"
#include "myApplication.h"
COnlinePlayState* COnlinePlayState::instance = 0;

COnlinePlayState::COnlinePlayState(void):
internalState(0)
{
}

COnlinePlayState::~COnlinePlayState(void)
{
}

COnlinePlayState* COnlinePlayState::GetInstance()
{
	if(instance == 0)
	{
		instance = new COnlinePlayState();
	}
	return instance;
}

void COnlinePlayState::InputKey(int key, int x, int y)
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

void COnlinePlayState::InputUpKey(int key, int x, int y)
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

void COnlinePlayState::KeyboardDown(unsigned char key, int x, int y)
{
	keyboard->myKeys[key] = true;
	if(internalState==0)
	{
		switch(key)
		{
			case 't':
				//backgroundImage[0].CheckUp();
				//buttonList.front()->PrintDebugInformation();
				mouse->PrintDebugInformation();
				break;
			case '2':
				//mouse->PrintDebugInformation();
				//GSM->PrintDebugInformation();
				GSM->ChangeState(myApplication::GetInstance());
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
}

void COnlinePlayState::KeyboardUp(unsigned char key, int x, int y)
{
	keyboard->myKeys[key] = false;
	if(internalState==1)
	{
		if(key==8)
			ip.pop_back();
		else if(key==13)
		{
			if(ip=="")
			{
				GSM->ChangeState(myApplication::GetInstance(true));
			}
			else
				GSM->ChangeState(myApplication::GetInstance(true,ip));
		}
		else
			ip+=key;
	}
}

void COnlinePlayState::MouseMove (int x, int y)
{
	int diffX = x - mouse->lastX;
	int diffY = y - mouse->lastY;

	mouse->lastX = x;
	mouse->lastY = y;
	mouse->gameX=mouse->lastX/WM->GetWindowRatioDifferenceX();
	mouse->gameY=mouse->lastY/WM->GetWindowRatioDifferenceY();
}

void COnlinePlayState::MouseClick(int button, int state, int x, int y)
{

	switch (button) {
		case GLUT_LEFT_BUTTON:
			switch(state)
			{
				case GLUT_DOWN:
					//mouse->mLButtonUp = true;	
					mouse->SetLeftButton(true);
					break;
				case GLUT_UP:
					//mouse->mLButtonUp = false;	
					mouse->SetLeftButton(false);
					break;
			}
			break;

		case GLUT_RIGHT_BUTTON:

			switch(state)
			{
				case GLUT_DOWN:
					//mouse->mRButtonUp = true;	
					mouse->SetRightButton(true);
					break;
				case GLUT_UP:
					//mouse->mRButtonUp = false;
					mouse->SetRightButton(false);
					break;
			}
			break;

		case GLUT_MIDDLE_BUTTON:
		
			switch(state)
			{
				case GLUT_DOWN:
					//mouse->middleButtonUp = true;	
					mouse->SetMiddleButton(true);
					break;
				case GLUT_UP:
					//mouse->middleButtonUp = false;	
					mouse->SetMiddleButton(false);
					break;
			}
			break;
	}
}

void COnlinePlayState::MouseWheel(int button, int dir, int x, int y)
{
}

void COnlinePlayState::changeSize (int w, int h)
{
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

void COnlinePlayState::SetHUD(bool m_bHUDmode)
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

void COnlinePlayState::Render2D()
{
	RenderBackground();
	switch(internalState)
	{
	case 0:
		for(TButtonList::iterator it = buttonList.begin(); it != buttonList.end(); ++it)
		{
			(*it)->Render();
		}
		break;
	case 1:
		printw(500,200,0,"IP :%s",ip.c_str());
		break;
	}
	FRM->drawFPS();
}

void COnlinePlayState::Render3D()
{
}

void COnlinePlayState::RenderScene(void)
{
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

bool COnlinePlayState::Update()
{
	for(unsigned short i = 0 ; i< buttonList.size();++i)
	{
		buttonList[i]->Update();
		if(buttonList[i]->ColisionCheck(mouse))
		{
			//std::cout<<"Button COllided"<<std::endl;
			ButtonTriggerCall(buttonList[i]->name);
		}else
		{
			//std::cout<<"=D "<<std::endl;
		}
	}

	if(keyboard->myKeys[VK_ESCAPE] == true)
	{
		GSM->ExitApplication();
	}

	if(FRM->UpdateAndCheckTimeThreehold())
	{
		OM->Update();
	}
	return true;
}

bool COnlinePlayState::Init()
{
	inited = true;
	
	name = "onlineplay";
	tag = "COnlinePlayState";
	genericTag = "CGameState";

	IM = CImageManager::GetInstance();
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

	IM->RegisterTGA("BackButton.tga");
	IM->RegisterTGA("CreateGameButton.tga");
	IM->RegisterTGA("JoinGameButton.tga");

	backgroundImage[0].Init(1,1,0);
	backgroundImage[0].SetImageSize((float)WM->GetOriginalWindowWidth(),(float)WM->GetOriginalWindowHeight());
	backgroundImage[0].OverrideTGATexture(IM->GetTGAImage("kanon.tga"));

	CUIButton* a_button = 0;

	a_button = new CUIButtonRectangle();
	a_button->ownTexture.Init(1);
	a_button->ownTexture.OverrideTGATexture(IM->GetTGAImage("CreateGameButton.tga"));
	a_button->SetPosition(WM->GetOriginalWindowWidth()*0.5f,WM->GetOriginalWindowHeight()*0.35f);
	a_button->SetSize(WM->GetOriginalWindowWidth()*0.45f,WM->GetOriginalWindowHeight()*0.2f);
	a_button->name ="CreateGameButton";
	buttonList.push_back(a_button);

	a_button = new CUIButtonRectangle();
	a_button->ownTexture.Init(1);
	a_button->ownTexture.OverrideTGATexture(IM->GetTGAImage("JoinGameButton.tga"));
	a_button->SetPosition(WM->GetOriginalWindowWidth()*0.5f,WM->GetOriginalWindowHeight()*0.6f);
	a_button->SetSize(WM->GetOriginalWindowWidth()*0.45f,WM->GetOriginalWindowHeight()*0.2f);
	a_button->name ="JoinGameButton";
	buttonList.push_back(a_button);

	//a_button = new CUIButtonRectangle();
	//a_button->ownTexture.Init(1);
	//a_button->ownTexture.OverrideTGATexture(IM->GetTGAImage("tenri.tga"));
	//a_button->SetPosition(WM->GetOriginalWindowWidth()*0.5,WM->GetOriginalWindowHeight()*0.85);
	//a_button->SetSize(WM->GetOriginalWindowWidth()*0.45,WM->GetOriginalWindowHeight()*0.2);
	//a_button->name ="OptionButton";
	//buttonList.push_back(a_button);


	a_button = new CUIButtonCircle();
	a_button->ownTexture.Init(1);
	a_button->ownTexture.OverrideTGATexture(IM->GetTGAImage("BackButton.tga"));
	a_button->SetPosition(WM->GetOriginalWindowWidth()*0.1f,WM->GetOriginalWindowHeight()*0.9f);
	a_button->SetSize(WM->GetOriginalWindowWidth()*0.08f,WM->GetOriginalWindowHeight()*0.08f);
	a_button->name ="BackButton";
	buttonList.push_back(a_button);

	//a_button = new CUIButtonCircle();
	//a_button->ownTexture.Init(1);
	//a_button->ownTexture.OverrideTGATexture(IM->GetTGAImage("sonia2.tga"));
	//a_button->SetPosition(WM->GetOriginalWindowWidth()*0.9,WM->GetOriginalWindowHeight()*0.9);
	//a_button->SetSize(WM->GetOriginalWindowWidth()*0.08,WM->GetOriginalWindowHeight()*0.08);
	//a_button->name ="ExitButton";
	//buttonList.push_back(a_button);
	

	return true;
}

bool COnlinePlayState::Reset()
{
	return Init();
}

bool COnlinePlayState::CleanUp()
{
	for(TButtonList::iterator it = buttonList.begin(); it != buttonList.end(); ++it)
	{
		if((*it) != 0)
		{
			delete (*it);
			(*it) = 0;
		}
	}

	if(OM != 0)
	{
		delete OM;
		OM = 0;
	}


	return true;
}

void COnlinePlayState::RenderBackground()
{
	//glEnable(GL_TEXTURE_2D);

	//// Draw Background image
	//glPushMatrix();
	//	glEnable(GL_BLEND);
	//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//	
	//	glBindTexture(GL_TEXTURE_2D, backgroundImage[0].owntexture.texID);
	//	//glBindTexture(GL_TEXTURE_2D, IM->GetTGAImage("sonia2.tga")->texID);
	//	glPushMatrix();
	//		glBegin(GL_QUADS);
	//			int height = 100 * 1.333/1.5;
	//			glTexCoord2f(0,0); glVertex2f(0,800);
	//			glTexCoord2f(1,0); glVertex2f(1024,800);
	//			glTexCoord2f(1,1); glVertex2f(1024,0);
	//			glTexCoord2f(0,1); glVertex2f(0,0);				
	//		glEnd();
	//	glPopMatrix();
	//	glDisable(GL_BLEND);
	//glPopMatrix();
	//glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(400,300,0);
	backgroundImage[0].Render();
	glPopMatrix();
}

void COnlinePlayState::ButtonTriggerCall(std::string buttonName)
{
	if(mouse->CheckLeftButtonReleased())
	{
		MS->PlaySoundPoolTrack2D("sound1.mp3");
		if(buttonName == "CreateGameButton")
		{
			startupServer("server.exe");
			GSM->ChangeState(myApplication::GetInstance(true));
		}
		else if(buttonName == "JoinGameButton")
		{
			internalState=1;
			//GSM->ChangeState(myApplication::GetInstance(true));
		}
		else if(buttonName == "BackButton")
		{
			GSM->GoToPreviousState();
		}

	}
}


void COnlinePlayState::startupServer(LPCTSTR lpApplicationName)
{
	// additional information
	
	// set the size of the structures
	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );

	// start the program up
	CreateProcess( lpApplicationName,   // the path
		NULL,			// Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi );          // Pointer to PROCESS_INFORMATION structure
}

void COnlinePlayState::closeServer()
{
	// Close process and thread handles. 
	CloseHandle( pi.hProcess );
	CloseHandle( pi.hThread );
}