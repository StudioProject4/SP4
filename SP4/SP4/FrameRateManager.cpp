#include "FrameRateManager.h"
#include <mmsystem.h>

CFrameRateManager* CFrameRateManager::instance = NULL;

CFrameRateManager::CFrameRateManager(void)
{
	Init();
}
CFrameRateManager* CFrameRateManager::GetInstance()
{
	if(instance == NULL)
	{
		instance = new CFrameRateManager();
	}
	return instance;
}
bool CFrameRateManager::Init()
{
	name = "frameratemanager";

	frameCount = 0;
	fps = 0;
	currentTime = 0;
	previousTime = 0;
	font_style = GLUT_BITMAP_TIMES_ROMAN_24;
	timelastcall=timeGetTime();
	frequency = 30.0f;
	deltaTime = 0;
	timethreeshold = 1000;

	return true;
}

CFrameRateManager::~CFrameRateManager(void)
{
}

bool CFrameRateManager::Update()
{
	deltaTime = (timeGetTime()-timelastcall);

	if (deltaTime>timethreeshold/frequency)
	{
		// Calculate the framerate
		CalculateFPS();

		timelastcall=timeGetTime();

		return true;
	}
	return false;
}

bool CFrameRateManager::Reset()
{
	return Init();
}

bool CFrameRateManager::CleanUp()
{
	return true;
}

bool CFrameRateManager::UpdateAndCheckTimeThreehold()
{
	return Update();
}
void CFrameRateManager::CalculateFPS()
{
	//  Increase frame count
	frameCount++;

	//  Get the number of milliseconds since glutInit called
	//  (or first call to glutGet(GLUT ELAPSED TIME)).
	currentTime = glutGet(GLUT_ELAPSED_TIME);

	//  Calculate time passed
	int timeInterval = currentTime - previousTime;

	if(timeInterval > timethreeshold)
	{
		//  calculate the number of frames per second
		fps = frameCount / (timeInterval / timethreeshold);

		//  Set time
		previousTime = currentTime;

		//  Reset frame count
		frameCount = 0;
		//game update here,so you most likely won't use this function.
	}
}
void CFrameRateManager::drawFPS(float xpos,float ypos)
{
	//  Load the identity matrix so that FPS string being drawn
	//  won't get animates
	glLoadIdentity ();

	//  Print the FPS to the window
	if (fps > 28.30f)
		glColor3f( 1.0f, 1.0f, 0.0f);
	else if (fps > 28.0f)
		glColor3f( 1.0f, 0.0f, 1.0f);
	else 
		glColor3f( 1.0f, 0.0f, 0.0f);
	printw (xpos, ypos, 0, "FPS: %4.2f", fps);
}
//void CFrameRateManager::printw (float x, float y, float z, char* format, ...)
//{
//	va_list args;	//  Variable argument list
//	int len;		//	String length
//	int i;			//  Iterator
//	char * text;	//	Text
//
//	//  Initialize a variable argument list
//	va_start(args, format);
//
//	//  Return the number of characters in the string referenced the list of arguments.
//	//  _vscprintf doesn't count terminating '\0' (that's why +1)
//	len = _vscprintf(format, args) + 1; 
//
//	//  Allocate memory for a string of the specified size
//	text = (char *)malloc(len * sizeof(char));
//
//	//  Write formatted output using a pointer to the list of arguments
//	vsprintf_s(text, len, format, args);
//
//	//  End using variable argument list 
//	va_end(args);
//
//	//  Specify the raster position for pixel operations.
//	glRasterPos3f (x, y, z);
//
//
//	//  Draw the characters one by one
//	for (i = 0; text[i] != '\0'; i++)
//		glutBitmapCharacter(font_style, text[i]);
//
//	//  Free the allocated memory for the string
//	free(text);
//}