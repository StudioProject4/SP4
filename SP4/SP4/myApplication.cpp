#include "myApplication.h"
#include <mmsystem.h>
myApplication* myApplication::instance = NULL;

myApplication::myApplication(void)
	: Map(NULL)
{
	//Init();
}
myApplication* myApplication::GetInstance()
{
	if(instance ==NULL)
	{
		instance = new myApplication();
	}
	return instance;
}

myApplication::~myApplication(void)
{
}

bool myApplication::CleanUp()
{
	MS->Exit();

	if(Map != NULL)
	{
		delete Map;
		Map = NULL;
	}

	if(instance != NULL)
	{
		Release();
		instance = NULL;
	}
	return true;
	if(playerOne != NULL)
	{
		delete playerOne;
		playerOne = NULL;
	}
	if(playerTwo != NULL)
	{
		delete playerTwo;
		playerTwo - NULL;
	}
	if(theAIOne != NULL)
	{
		delete theAIOne;
		theAIOne = NULL;
	}
	if(theAITwo != NULL)
	{
		delete theAITwo;
		theAITwo = NULL;
	}
	CMusicSystem::GetInstance()->Exit();
	if(instance != NULL)
	{
		Release();
		instance = NULL;
	}
	return true;

}
bool myApplication::Reset()
{
	return Init();
}

bool myApplication::Init()
{
	inited = true;
	//for(unsigned short i = 0; i<255; ++i)
	//{
	//	myKeys[i] = false;
	//}
	tag = "application";
	name = "Main Application";

	glEnable(GL_TEXTURE_2D);

	//frameCount = 0;
	//fps = 0;
	//currentTime = 0;
	//previousTime = 0;
	//font_style = GLUT_BITMAP_TIMES_ROMAN_24;
	//timelastcall=timeGetTime();
	//frequency = 30.0f;

	//loading texture
	LoadTGA(&testimage,"sonia2.tga");


	//background
	LoadTGA( &BackgroundTexture[0], "back.tga");

	LoadTGA( &TileMapTexture[1], "tile0_blank.tga");
	LoadTGA( &TileMapTexture[0], "BlackWalls.tga");
	//LoadTGA( &TileMapTexture[1], "LavaGround.tga");
	LoadTGA( &TileMapTexture[2], "BlackWallCut.tga");
	LoadTGA( &TileMapTexture[3], "HealthCross.tga");
	LoadTGA( &TileMapTexture[4], "SpeedUp.tga");
	LoadTGA( &TileMapTexture[5], "Invincible.tga");
	LoadTGA( &TileMapTexture[6], "PointsAdd.tga");
	LoadTGA( &TileMapTexture[7], "Jump.tga");
	//LoadTGA( &TileMapTexture[0], "tile0_blank");


	glDisable(GL_TEXTURE_2D);


	//getting instance of managers
	FRM = CFrameRateManager::GetInstance();
	LM = CLuaManager::GetInstance();
	mouse = CMouse::GetInstance();
	keyboard = CKeyboard::GetInstance();
	WM = CWindowManager::GetInstance();
	MS = CMusicSystem::GetInstance();
	OM = new CObjectManager();

	//playerOne = OM->manufacturer->CreateChineseMale();
	//playerTwo = new CMalayFemale();
	//theAIOne = new CMalayMob();
	//theAITwo = new CChineseMob();

	playerOne = OM->manufacturer->CreateChineseMale();
	playerOne->Init(Vector3(64,64),Vector3(0,0,0),0);
	playerTwo = OM->manufacturer->CreateMalayFemale();
	theAIOne = OM->manufacturer->CreateMalayMob();
	theAITwo = OM->manufacturer->CreateChineseMob();

	testmale = OM->manufacturer->CreateChineseMale();

	 mapOffset_x =  mapOffset_y=
	 tileOffset_x =tileOffset_y=
	 mapFineOffset_x= mapFineOffset_y=
	 theNumOfTiles_Height
	= theNumOfTiles_Width
	= rearWallOffset_x=rearWallOffset_y
	 =rearWalltileOffset_x= rearWalltileOffset_y
	= rearWallFineOffset_x= rearWallFineOffset_y = 0;

	//map
	Map = new CMap();
	//Map->Init( SCREEN_HEIGHT, SCREEN_WIDTH, 1632, 1344, TILE_SIZE );
	Map->Init(SCREEN_HEIGHT,SCREEN_WIDTH*2,SCREEN_HEIGHT,SCREEN_WIDTH*2,TILE_SIZE);
	
	playerTwo->phys.map=Map;
	playerOne->phys.map=Map;
	
	////load map
	//if(Map->LevelCount == 1)
	//{
	//	Map->LoadMap("Level1_1.csv");
	//}
	//if(Map->LevelCount == 2)
	//{
	//	Map->LoadMap("Level1_1.csv");
	//}
	//if(Map->LevelCount == 3)
	//{
	//	Map->LoadMap("Level1_1.csv");
	//}
	//if(Map->LevelCount == 4)
	//{
	//	Map->LoadMap("Level1_1.csv");
	//}
	//if(Map->LevelCount == 5)
	//{
	//	Map->LoadMap("Level1_1.csv");
	//}
	
	

	theNumOfTiles_Height = Map->getNumOfTiles_ScreenHeight();
	theNumOfTiles_Width = Map->getNumOfTiles_ScreenWidth();

	//std::cout<< Map->getNumOfTiles_MapHeight()<<std::endl;
	//std::cout<< Map->getNumOfTiles_MapWidth()<<std::endl;
	
	return true;
}

bool myApplication::Update()
{


		if(keyboard->myKeys['a'])
		{
			playerOne->MoveLeft();
		}
		if(keyboard->myKeys['d'])
		{
			playerOne->MoveRight();
		}
		if(keyboard->myKeys['w'])
		{
			playerOne->Jump();
		}
		if(keyboard->myKeys['s'])
		{
		
		}
		if(keyboard->myKeys[VK_ESCAPE] == true)
		{
			exit(0);
		}
		if(keyboard->myKeys['j'] == true)
		{
			playerTwo->MoveLeft();
		}
		if(keyboard->myKeys['l'] == true)
		{
			playerTwo->MoveRight();
		}
		if(keyboard->myKeys['i'] == true)
		{
			playerTwo->Jump();
		}
		if(keyboard->myKeys[VK_ESCAPE] == true)
		{
			exit(0);
			//GSM->PopAndCleanLastState();
		}
		if(keyboard->myKeys['k'] == true)
		{
		
		}
		if(keyboard->leftArrow == true)
		{
			playerTwo->MoveLeft();
		}
		if(keyboard->rightArrow == true)
		{
			playerTwo->MoveRight();
		}
		if(keyboard->upArrow == true)
		{
			playerTwo->Jump();
		}
	if(FRM->UpdateAndCheckTimeThreehold())
	{
		theAIOne->AI.SetEnemyPos(playerOne->pos);
		theAIOne->Update();
		theAITwo->AI.SetEnemyPos(playerTwo->pos);
		theAITwo->Update();
	}

	playerOne->Update();
	playerTwo->Update();
		Map->RunMap();
		//std::cout << playerOne->pos.x << std::endl;
		//std::cout << playerOne->pos.y << std::endl;
		//std::cout << Map->lookupPosition(playerOne->pos,false) << std::endl;


	return true;
}
void myApplication::RenderTileMap()
{
	glEnable(GL_TEXTURE_2D);
	mapFineOffset_x = mapOffset_x % TILE_SIZE;

	glPushMatrix();
	for (int i = 0; i < theNumOfTiles_Height; i++)
	{
		for (int k = 0; k < theNumOfTiles_Width + 1; k++)
		{
			// If we have reached the right side of the Map, then do not display the extra column of tiles.
			if ((tileOffset_x + k) >= Map->getNumOfTiles_MapWidth())
				break;
			glPushMatrix();
			glTranslatef((GLfloat)(k * TILE_SIZE - mapFineOffset_x), (GLfloat)(i * TILE_SIZE), 0.0f);
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture(GL_TEXTURE_2D, TileMapTexture[Map->theScreenMap[i][tileOffset_x + k]].texID);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 1); glVertex2f(0, 0);
			glTexCoord2f(0, 0); glVertex2f(0, TILE_SIZE);
			glTexCoord2f(1, 0); glVertex2f(TILE_SIZE, TILE_SIZE);
			glTexCoord2f(1, 1); glVertex2f(TILE_SIZE, 0);
			glEnd();
			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
			glPopMatrix();
		}
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}
void myApplication::RenderBackground()
{
	glEnable(GL_TEXTURE_2D);

	// Draw Background image
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, BackgroundTexture[0].texID );
		glPushMatrix();
			glBegin(GL_QUADS);
				int height = 100 * 1.333/1.5;
				glTexCoord2f(0,0); glVertex2f(0,800);
				glTexCoord2f(1,0); glVertex2f(1024,800);
				glTexCoord2f(1,1); glVertex2f(1024,0);
				glTexCoord2f(0,1); glVertex2f(0,0);				
			glEnd();
		glPopMatrix();
		glDisable(GL_BLEND);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	
}
void myApplication::Render2D()
{
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,testimage.texID);
	glBegin(GL_QUADS);
	glEnd();
	glPopMatrix();
	//drawFPS();
	FRM->drawFPS();
	RenderBackground();
	RenderTileMap();

	//if(Map->Level == 1)


//	PowerUp->Update();


	
	//RenderTileMap();
	//glPushMatrix();
	//for(int i = 0; i < theNumOfTiles_Height; i ++)

	//{
	//	RenderBackground();
	//	RenderTileMap();
	//	glPushMatrix();
	//	for(int i = 0; i < theNumOfTiles_Height; i ++)
	//	{
	//		//for(int k = 0; k < theNumOfTiles_Width+1; k ++)
	//		for(int k = 0; k < theNumOfTiles_Width; k ++)
	//	
	//		{
	//					// If we have reached the right side of the Map, then do not display the extra column of tiles.
	//		/*if ( (tileOffset_x+k) >= theMap->getNumOfTiles_MapWidth() )
	//			break;*/
	//			glPushMatrix();
	//		//	glTranslatef(k*TILE_SIZE-mapFineOffset_x, i*TILE_SIZE, 0);
	//			glTranslatef(k*TILE_SIZE, i* TILE_SIZE, 0);
	//			glEnable( GL_TEXTURE_2D );
	//			glEnable( GL_BLEND );
	//			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	//			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//			glBindTexture( GL_TEXTURE_2D, TileMapTexture[Map->theScreenMap[i][k]].texID); /*TileMapTexture[theMap->theScreenMap[i][tileOffset_x+k]].texID );*/
	//			glBegin(GL_QUADS);
	//				glTexCoord2f(0,1); glVertex2f(0,0);
	//				glTexCoord2f(0,0); glVertex2f(0,TILE_SIZE);
	//				glTexCoord2f(1,0); glVertex2f(TILE_SIZE,TILE_SIZE);
	//				glTexCoord2f(1,1); glVertex2f(TILE_SIZE,0);
	//			glEnd();
	//			glDisable( GL_BLEND );
	//			glDisable( GL_TEXTURE_2D );
	//			glPopMatrix();
	//		}
	//	}
	//	glPopMatrix();
	//}
	//if(Map->Level == 2)
	//{
	//		RenderBackground();
	//	RenderTileMap();
	//	glPushMatrix();
	//	for(int i = 0; i < theNumOfTiles_Height; i ++)
	//	{
	//		//for(int k = 0; k < theNumOfTiles_Width+1; k ++)
	//		for(int k = 0; k < theNumOfTiles_Width; k ++)
	//	
	//		{
	//					// If we have reached the right side of the Map, then do not display the extra column of tiles.
	//		/*if ( (tileOffset_x+k) >= theMap->getNumOfTiles_MapWidth() )
	//			break;*/
	//			glPushMatrix();
	//		//	glTranslatef(k*TILE_SIZE-mapFineOffset_x, i*TILE_SIZE, 0);
	//			glTranslatef(k*TILE_SIZE, i* TILE_SIZE, 0);
	//			glEnable( GL_TEXTURE_2D );
	//			glEnable( GL_BLEND );
	//			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	//			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//			glBindTexture( GL_TEXTURE_2D, TileMapTexture[Map->theScreenMap[i][k]].texID); /*TileMapTexture[theMap->theScreenMap[i][tileOffset_x+k]].texID );*/
	//			glBegin(GL_QUADS);
	//				glTexCoord2f(0,1); glVertex2f(0,0);
	//				glTexCoord2f(0,0); glVertex2f(0,TILE_SIZE);
	//				glTexCoord2f(1,0); glVertex2f(TILE_SIZE,TILE_SIZE);
	//				glTexCoord2f(1,1); glVertex2f(TILE_SIZE,0);
	//			glEnd();
	//			glDisable( GL_BLEND );
	//			glDisable( GL_TEXTURE_2D );
	//			glPopMatrix();
	//		}
	//	}
	//	glPopMatrix();
	//}
	//testmale->Render();
	playerOne->Render();
	playerTwo->Render();
	theAIOne->Render();
	theAITwo->Render();
//	PowerUp->Update();

	
}
void myApplication::Render3D()
{

}
void myApplication::RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);

	//float deltaTime = (timeGetTime()-timelastcall);
	//
	//if (deltaTime>1000/frequency)
	//{
	//	// Calculate the framerate
	//	calculateFPS();

	//	timelastcall=timeGetTime();

	//	Update();
	//}

	Render3D();

	SetHUD( true );
		Render2D();
	SetHUD( false );
	glDisable(GL_DEPTH_TEST);
	// Flush off any entity which is not drawn yet, so that we maintain the frame rate.
	glFlush();

	// swapping the buffers causes the rendering above to be shown
	glutSwapBuffers();
	glutPostRedisplay();
}
void myApplication::InputUpKey(int key, int x, int y)
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
void myApplication::InputKey(int key, int x, int y)
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
void myApplication::KeyboardDown(unsigned char key, int x, int y)
{
	keyboard->myKeys[key] = true;

	switch(key)
	{
		case '1':
			//this->PrintDebugInformation();
			//mouse->PrintDebugInformation();
			//MS->PlayBgmTrack("bgm1.mp3");
			//MS->PlaySoundTrack(0);
			//std::cout<<MS->currentSoundTrack<<std::endl;
			//MS->FetchSound()->PrintDebugInformation();
			MS->PlaySoundPoolTrack2D("sound1.mp3");
			
		break;

		case '2':
			//CGameStateManager::GetInstance()->ChangeState(CMenuState::GetInstance());
			//this->PrintDebugInformation();
			//MS->PlayBgmTrack("bgm2.mp3");
			//MS->PlaySoundTrack(1);
			//std::cout<<MS->currentSoundTrack<<std::endl;
			MS->PlaySoundPoolTrack2D("sound2.mp3");
			
		break;
		
		case '3':
			MS->PrintSoundPoolList();
			//MS->TranverseSoundTrack();
			
			break;
		case '4':
			MS->PrintCurrentSoundTrack();
			
			break;
		case '5':
			MS->ResetSoundTrackPlayPosition(MS->currentSoundTrack);
			break;
		case '6':
			MS->PrintSoundTrackList();
			break;
		case '7':
			std::cout<< testmale<<std::endl;
			testmale->PrintDebugInformation();
			
			break;
		case '8':
			
			break;
		case '9':
			MS->Exit();
			break;
	}
}

void myApplication::KeyboardUp(unsigned char key, int x, int y)
{
	keyboard->myKeys[key]= false;
}

void myApplication::MouseMove (int x, int y)
{
	int diffX = x - mouse->lastX;
	int diffY = y - mouse->lastY;

	mouse->lastX = x;
	mouse->lastY = y;
}
void myApplication::MouseWheel(int button, int dir, int x, int y)
{

}
void myApplication::MouseClick(int button, int state, int x, int y)
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
void myApplication::changeSize (int w, int h)
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
void myApplication::SetHUD(bool m_bHUDmode)
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
};
////-------------------------------------------------------------------------
////  Draws a string at the specified coordinates.
////-------------------------------------------------------------------------
//void myApplication::printw (float x, float y, float z, char* format, ...)
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
//    for (i = 0; text[i] != '\0'; i++)
//        glutBitmapCharacter(font_style, text[i]);
//
//	//  Free the allocated memory for the string
//	free(text);
//}
//void myApplication::calculateFPS()
//{
//	//  Increase frame count
//	frameCount++;
//
//	//  Get the number of milliseconds since glutInit called
//	//  (or first call to glutGet(GLUT ELAPSED TIME)).
//	currentTime = glutGet(GLUT_ELAPSED_TIME);
//
//	//  Calculate time passed
//	int timeInterval = currentTime - previousTime;
//
//	if(timeInterval > 1000)
//	{
//		//  calculate the number of frames per second
//		fps = frameCount / (timeInterval / 1000.0f);
//
//		//  Set time
//		previousTime = currentTime;
//
//		//  Reset frame count
//		frameCount = 0;
//		//game update here,so you most likely won't use this function.
//	}
//}
//void myApplication::drawFPS()
//{
//	//  Load the identity matrix so that FPS string being drawn
//	//  won't get animates
//	glLoadIdentity ();
//
//	//  Print the FPS to the window
//	if (fps > 28.30f)
//		glColor3f( 1.0f, 1.0f, 0.0f);
//	else if (fps > 28.0f)
//		glColor3f( 1.0f, 0.0f, 1.0f);
//	else 
//		glColor3f( 1.0f, 0.0f, 0.0f);
//	printw (25.0, 25.0, 0, "FPS: %4.2f", fps);
//}
//bool myApplication::LoadTGA(TextureImage *texture,const char *filename)			// Loads A TGA File Into Memory
//{
//	GLubyte		TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};	// Uncompressed TGA Header
//	GLubyte		TGAcompare[12];								// Used To Compare TGA Header
//	GLubyte		header[6];									// First 6 Useful Bytes From The Header
//	GLuint		bytesPerPixel;								// Holds Number Of Bytes Per Pixel Used In The TGA File
//	GLuint		imageSize;									// Used To Store The Image Size When Setting Aside Ram
//	GLuint		temp;										// Temporary Variable
//	GLuint		type=GL_RGBA;								// Set The Default GL Mode To RBGA (32 BPP)
//
//	FILE *file = fopen(filename, "rb");						// Open The TGA File
//
//	if(	file==NULL ||										// Does File Even Exist?
//		fread(TGAcompare,1,sizeof(TGAcompare),file)!=sizeof(TGAcompare) ||	// Are There 12 Bytes To Read?
//		memcmp(TGAheader,TGAcompare,sizeof(TGAheader))!=0				||	// Does The Header Match What We Want?
//		fread(header,1,sizeof(header),file)!=sizeof(header))				// If So Read Next 6 Header Bytes
//	{
//		if (file == NULL)									// Did The File Even Exist? *Added Jim Strong*
//			return false;									// Return False
//		else
//		{
//			fclose(file);									// If Anything Failed, Close The File
//			return false;									// Return False
//		}
//	}
//
//	texture->width  = header[1] * 256 + header[0];			// Determine The TGA Width	(highbyte*256+lowbyte)
//	texture->height = header[3] * 256 + header[2];			// Determine The TGA Height	(highbyte*256+lowbyte)
//
//	if(	texture->width	<=0	||								// Is The Width Less Than Or Equal To Zero
//		texture->height	<=0	||								// Is The Height Less Than Or Equal To Zero
//		(header[4]!=24 && header[4]!=32))					// Is The TGA 24 or 32 Bit?
//	{
//		fclose(file);										// If Anything Failed, Close The File
//		return false;										// Return False
//	}
//
//	texture->bpp	= header[4];							// Grab The TGA's Bits Per Pixel (24 or 32)
//	bytesPerPixel	= texture->bpp/8;						// Divide By 8 To Get The Bytes Per Pixel
//	imageSize		= texture->width*texture->height*bytesPerPixel;	// Calculate The Memory Required For The TGA Data
//
//	texture->imageData=(GLubyte *)malloc(imageSize);		// Reserve Memory To Hold The TGA Data
//
//	if(	texture->imageData==NULL ||							// Does The Storage Memory Exist?
//		fread(texture->imageData, 1, imageSize, file)!=imageSize)	// Does The Image Size Match The Memory Reserved?
//	{
//		if(texture->imageData!=NULL)						// Was Image Data Loaded
//			free(texture->imageData);						// If So, Release The Image Data
//
//		fclose(file);										// Close The File
//		return false;										// Return False
//	}
//
//	for(GLuint i=0; i<int(imageSize); i+=bytesPerPixel)		// Loop Through The Image Data
//	{														// Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)
//		temp=texture->imageData[i];							// Temporarily Store The Value At Image Data 'i'
//		texture->imageData[i] = texture->imageData[i + 2];	// Set The 1st Byte To The Value Of The 3rd Byte
//		texture->imageData[i + 2] = temp;					// Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
//	}
//
//	fclose (file);											// Close The File
//
//	// Build A Texture From The Data
//	glGenTextures(1, &texture[0].texID);					// Generate OpenGL texture IDs
//
//	glBindTexture(GL_TEXTURE_2D, texture[0].texID);			// Bind Our Texture
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtered
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// Linear Filtered
//
//	if (texture[0].bpp==24)									// Was The TGA 24 Bits
//	{
//		type=GL_RGB;										// If So Set The 'type' To GL_RGB
//	}
//
//	glTexImage2D(GL_TEXTURE_2D, 0, type, texture[0].width, texture[0].height, 0, type, GL_UNSIGNED_BYTE, texture[0].imageData);
//
//	return true;											// Texture Building Went Ok, Return True
//
//};
//bool myApplication::LoadTGA(TextureImage *texture, char *filename)			// Loads A TGA File Into Memory
//{
//	GLubyte		TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};	// Uncompressed TGA Header
//	GLubyte		TGAcompare[12];								// Used To Compare TGA Header
//	GLubyte		header[6];									// First 6 Useful Bytes From The Header
//	GLuint		bytesPerPixel;								// Holds Number Of Bytes Per Pixel Used In The TGA File
//	GLuint		imageSize;									// Used To Store The Image Size When Setting Aside Ram
//	GLuint		temp;										// Temporary Variable
//	GLuint		type=GL_RGBA;								// Set The Default GL Mode To RBGA (32 BPP)
//
//	FILE *file = fopen(filename, "rb");						// Open The TGA File
//
//	if(	file==NULL ||										// Does File Even Exist?
//		fread(TGAcompare,1,sizeof(TGAcompare),file)!=sizeof(TGAcompare) ||	// Are There 12 Bytes To Read?
//		memcmp(TGAheader,TGAcompare,sizeof(TGAheader))!=0				||	// Does The Header Match What We Want?
//		fread(header,1,sizeof(header),file)!=sizeof(header))				// If So Read Next 6 Header Bytes
//	{
//		if (file == NULL)									// Did The File Even Exist? *Added Jim Strong*
//			return false;									// Return False
//		else
//		{
//			fclose(file);									// If Anything Failed, Close The File
//			return false;									// Return False
//		}
//	}
//
//	texture->width  = header[1] * 256 + header[0];			// Determine The TGA Width	(highbyte*256+lowbyte)
//	texture->height = header[3] * 256 + header[2];			// Determine The TGA Height	(highbyte*256+lowbyte)
//
//	if(	texture->width	<=0	||								// Is The Width Less Than Or Equal To Zero
//		texture->height	<=0	||								// Is The Height Less Than Or Equal To Zero
//		(header[4]!=24 && header[4]!=32))					// Is The TGA 24 or 32 Bit?
//	{
//		fclose(file);										// If Anything Failed, Close The File
//		return false;										// Return False
//	}
//
//	texture->bpp	= header[4];							// Grab The TGA's Bits Per Pixel (24 or 32)
//	bytesPerPixel	= texture->bpp/8;						// Divide By 8 To Get The Bytes Per Pixel
//	imageSize		= texture->width*texture->height*bytesPerPixel;	// Calculate The Memory Required For The TGA Data
//
//	texture->imageData=(GLubyte *)malloc(imageSize);		// Reserve Memory To Hold The TGA Data
//
//	if(	texture->imageData==NULL ||							// Does The Storage Memory Exist?
//		fread(texture->imageData, 1, imageSize, file)!=imageSize)	// Does The Image Size Match The Memory Reserved?
//	{
//		if(texture->imageData!=NULL)						// Was Image Data Loaded
//			free(texture->imageData);						// If So, Release The Image Data
//
//		fclose(file);										// Close The File
//		return false;										// Return False
//	}
//
//	for(GLuint i=0; i<int(imageSize); i+=bytesPerPixel)		// Loop Through The Image Data
//	{														// Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)
//		temp=texture->imageData[i];							// Temporarily Store The Value At Image Data 'i'
//		texture->imageData[i] = texture->imageData[i + 2];	// Set The 1st Byte To The Value Of The 3rd Byte
//		texture->imageData[i + 2] = temp;					// Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
//	}
//
//	fclose (file);											// Close The File
//
//	// Build A Texture From The Data
//	glGenTextures(1, &texture[0].texID);					// Generate OpenGL texture IDs
//
//	glBindTexture(GL_TEXTURE_2D, texture[0].texID);			// Bind Our Texture
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtered
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// Linear Filtered
//
//	if (texture[0].bpp==24)									// Was The TGA 24 Bits
//	{
//		type=GL_RGB;										// If So Set The 'type' To GL_RGB
//	}
//
//	glTexImage2D(GL_TEXTURE_2D, 0, type, texture[0].width, texture[0].height, 0, type, GL_UNSIGNED_BYTE, texture[0].imageData);
//
//	return true;											// Texture Building Went Ok, Return True
//
//};