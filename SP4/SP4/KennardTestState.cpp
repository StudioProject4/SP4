#include "KennardTestState.h"

#include <GL/glut.h>
#include <GL/freeglut.h>
#include <GL/glext.h>

#include "WindowManager.h"
#include "Keyboard.h"
#include "LuaManager.h"
#include "Mouse.h"
#include "FrameRateManager.h"

KennardTestState::KennardTestState(void)
{
}


KennardTestState::~KennardTestState(void)
{
}

void KennardTestState::InputKey(int key,int x,int y)
{

}

void KennardTestState::KeyboardDown(unsigned char key,int x,int y)
{
	keyboard->myKeys[key] = true;
}

void KennardTestState::KeyboardUp(unsigned char key,int x,int y)
{
	keyboard->myKeys[key] = false;
}

void KennardTestState::MouseMove(int x,int y)
{
	int diffX = x - mouse->lastX;
	int diffY = y - mouse->lastY;

	mouse->lastX = x;
	mouse->lastY = y;
}

void KennardTestState::MouseClick(int button,int state,int x,int y)
{
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

void KennardTestState::MouseWheel(int button,int dir,int x,int y)
{

}

void KennardTestState::changeSize(int w,int h)
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
	//WM->SetAndUpdateWindowDimension(w,h);
	//WINDOW_WIDTH = w;
	//WINDOW_HEIGHT = h;
	WM->SetWindowDimension(w,h);
	//std::cout<<"myapp "<<WINDOW_WIDTH<<std::endl;
	// Set the correct perspective.
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);

}

void KennardTestState::SetHUD(bool m_bHUDmode)
{
	if (m_bHUDmode == true)
	{
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho( 0, WM->GetWindowWidth() , WM->GetWindowHeight(), 0, -1, 1 );  
		//std::cout<<"Window width"<<WINDOW_WIDTH<<std::endl;
		//std::cout<<"Window Height"<<WINDOW_HEIGHT<<std::endl;
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

KennardTestState* KennardTestState::s_instance=0;

void KennardTestState::Render2D()
{
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glColor3f(1,1,1);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glTranslatef(pos.x,pos.y,0);
		cout<<pos<<"\n";
		glScalef(100,100,0);
		glBindTexture(GL_TEXTURE_2D,this->testimage.texID);
		glBegin (GL_TRIANGLE_STRIP);
			glNormal3f(0,0,1);
			glTexCoord2f(0,0);
			glVertex3f(-0.5, 0.5, 0);
		
			glTexCoord2f(0,1.0);
			glVertex3f(-0.5,-0.5,0);

			glTexCoord2f(1.0,0.0);
			glVertex3f(0.5,0.5,0);

			glTexCoord2f(1.0,1.0);
			glVertex3f(0.5,-0.5,0);
		glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void KennardTestState::Render3D()
{

}

void KennardTestState::RenderScene(void)
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

bool KennardTestState::Update()
{
	if(keyboard->myKeys[' '])
	{
		keyboard->myKeys[' ']=false;
		testphys.Jump();
	}
	if(keyboard->myKeys['d'])
	{
		pos.x+=0.1;
		cout<<pos.x<<"\n";
	}
	if(keyboard->myKeys['a'])
	{
		pos.x-=0.1;
		cout<<pos.x<<"\n";
	}
	pos=testphys.Update(pos);
	return true;
}

bool KennardTestState::Init()
{
	inited=true;
	//getting instance of managers
	FRM = CFrameRateManager::GetInstance();
	LM = CLuaManager::GetInstance();
	mouse = CMouse::GetInstance();
	keyboard = CKeyboard::GetInstance();
	WM = CWindowManager::GetInstance();
	pos.Set(100,100,0);
	testphys.Init(pos,Vector3(100,100,1));
	return true;
}

bool KennardTestState::Reset()
{
	Init();
	return true;
}

bool KennardTestState::CleanUp()
{
	return true;
}