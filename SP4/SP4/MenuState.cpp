#include "MenuState.h"

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
CMenuState* CMenuState::instance = 0;

CMenuState::CMenuState(void)
{
}

CMenuState::~CMenuState(void)
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

void CMenuState::InputKey(int key, int x, int y)
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

void CMenuState::InputUpKey(int key, int x, int y)
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

void CMenuState::KeyboardDown(unsigned char key, int x, int y)
{
	keyboard->myKeys[key] = true;
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

void CMenuState::KeyboardUp(unsigned char key, int x, int y)
{
	keyboard->myKeys[key] = false;
}

void CMenuState::MouseMove (int x, int y)
{
	int diffX = x - mouse->lastX;
	int diffY = y - mouse->lastY;

	mouse->lastX = x;
	mouse->lastY = y;
}

void CMenuState::MouseClick(int button, int state, int x, int y)
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

void CMenuState::MouseWheel(int button, int dir, int x, int y)
{
}

void CMenuState::changeSize (int w, int h)
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
	RenderBackground();

	for(TButtonList::iterator it = buttonList.begin(); it != buttonList.end(); ++it)
	{
		(*it)->Render();
	}

	FRM->drawFPS();
}

void CMenuState::Render3D()
{
}

void CMenuState::RenderScene(void)
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

bool CMenuState::Update()
{
	for(unsigned short i = 0 ; i< buttonList.size();++i)
	{
		buttonList[i]->Update();
		if(buttonList[i]->ColisionCheck(mouse))
		{
			//std::cout<<"Button COllided"<<std::endl;
			PageTransitionTrigger(buttonList[i]->name);
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

bool CMenuState::Init()
{
	inited = true;
	
	name = "menu";
	genericTag = "CGameState";
	tag = "application";

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


	backgroundImage[0].Init(1,1,0);
	backgroundImage[0].SetImageSize(WM->GetOriginalWindowWidth(),WM->GetOriginalWindowHeight());
	backgroundImage[0].OverrideTGATexture(IM->GetTGAImage("sonia2.tga"));

	CUIButton* a_button = 0;

	a_button = new CUIButtonRectangle();
	a_button->ownTexture.Init(1);
	a_button->ownTexture.OverrideTGATexture(IM->GetTGAImage("kaede.tga"));
	a_button->SetPosition(WM->GetOriginalWindowWidth()*0.5,WM->GetOriginalWindowHeight()*0.35);
	a_button->SetSize(WM->GetOriginalWindowWidth()*0.45,WM->GetOriginalWindowHeight()*0.2);
	a_button->name ="SinglePlayerButton";
	buttonList.push_back(a_button);

	a_button = new CUIButtonRectangle();
	a_button->ownTexture.Init(1);
	a_button->ownTexture.OverrideTGATexture(IM->GetTGAImage("kanon.tga"));
	a_button->SetPosition(WM->GetOriginalWindowWidth()*0.5,WM->GetOriginalWindowHeight()*0.6);
	a_button->SetSize(WM->GetOriginalWindowWidth()*0.45,WM->GetOriginalWindowHeight()*0.2);
	a_button->name ="OnlinePlayButton";
	buttonList.push_back(a_button);

	a_button = new CUIButtonRectangle();
	a_button->ownTexture.Init(1);
	a_button->ownTexture.OverrideTGATexture(IM->GetTGAImage("tenri.tga"));
	a_button->SetPosition(WM->GetOriginalWindowWidth()*0.5,WM->GetOriginalWindowHeight()*0.85);
	a_button->SetSize(WM->GetOriginalWindowWidth()*0.45,WM->GetOriginalWindowHeight()*0.2);
	a_button->name ="OptionButton";
	buttonList.push_back(a_button);


	a_button = new CUIButtonCircle();
	a_button->ownTexture.Init(1);
	a_button->ownTexture.OverrideTGATexture(IM->GetTGAImage("sonia2.tga"));
	a_button->SetPosition(WM->GetOriginalWindowWidth()*0.1,WM->GetOriginalWindowHeight()*0.9);
	a_button->SetSize(WM->GetOriginalWindowWidth()*0.08,WM->GetOriginalWindowHeight()*0.08);
	a_button->name ="CreditButton";
	buttonList.push_back(a_button);

	a_button = new CUIButtonCircle();
	a_button->ownTexture.Init(1);
	a_button->ownTexture.OverrideTGATexture(IM->GetTGAImage("sonia2.tga"));
	a_button->SetPosition(WM->GetOriginalWindowWidth()*0.9,WM->GetOriginalWindowHeight()*0.9);
	a_button->SetSize(WM->GetOriginalWindowWidth()*0.08,WM->GetOriginalWindowHeight()*0.08);
	a_button->name ="ExitButton";
	buttonList.push_back(a_button);
	

	return true;
}

bool CMenuState::Reset()
{
	return Init();
}

bool CMenuState::CleanUp()
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

void CMenuState::RenderBackground()
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
 void CMenuState::PageTransitionTrigger(std::string buttonName)
 {
	 if(mouse->CheckLeftButtonReleased())
	 {
		 if(buttonName == "SinglePlayerButton")
		 {
			 //if(mouse->CheckLeftButtonReleased())
			 // {
			 GSM->ChangeState(myApplication::GetInstance());
			 // }
		 }else
			 if(buttonName == "OnlinePlayButton")
			 {
				 // if(mouse->CheckLeftButtonReleased())
				 // {
				 GSM->ChangeState(myApplication::GetInstance());
				 //}
			 }else
				 if(buttonName == "OptionButton")
				 {
					 // if(mouse->CheckLeftButtonReleased())
					 // {
					 GSM->ChangeState(myApplication::GetInstance());
					 // }
				 }else
					 if(buttonName == "CreditButton")
					 {
						 // if(mouse->CheckLeftButtonReleased())
						 // {
						 GSM->ChangeState(myApplication::GetInstance());
						 // }
					 }else
						 if(buttonName == "ExitButton")
						 {
							 // if(mouse->CheckLeftButtonReleased())
							 // {
							 GSM->ExitApplication();
							 // }
						 }
	 }
 }