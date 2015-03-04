#include "Sprite.h"

#include <stdio.h>
#include <iostream>

CSprite::CSprite()
	: maxframe(1)
	,numberoflayer(1)
	,currentframe(0)
	,pause(false)
	,frameinterval(10)
	,framespeed(1)
	,size(32.f,32.f)//the size need to be inline with tilesize
	,currentlayer(currentlayer)
	,currenttimecounter(0)
	,lateralinvert(false)
	,RED(1.f)
	,BLUE(1.f)
	,GREEN(1.f)
	,ALPHA(1.f)
{

	framesize.x = 1.0f/maxframe;
	framesize.y = 1.0f/numberoflayer;
}
CSprite::CSprite(ushort maxframe,ushort numberoflayer,ushort currentlayer)
	: maxframe(maxframe)
	,numberoflayer(numberoflayer)
	,currentframe(0)
	,pause(false)
	,frameinterval(20)
	,framespeed(1)
	,size(32.f,32.f)//the size need to be inline with tilesize
	,currentlayer(currentlayer)
	,currenttimecounter(0)
	,lateralinvert(false)
	,RED(1.f)
	,BLUE(1.f)
	,GREEN(1.f)
	,ALPHA(1.f)
{

	framesize.x = 1.0f/maxframe;
	framesize.y = 1.0f/numberoflayer;
}

bool CSprite::Init(ushort maxframe, ushort numberoflayer,ushort currentlayer)
{
	this->maxframe = maxframe;
	this->numberoflayer = numberoflayer;
	this->currentlayer = currentlayer;
	framesize.x = 1.0f/maxframe;
	framesize.y = 1.0f/numberoflayer;

	return true;
}

CSprite::~CSprite(void)
{
}

bool CSprite::LoadTGA( char *filename)
{
	TextureImage *texture = &owntexture;

	GLubyte		TGAheader[12] = { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 };	// Uncompressed TGA Header
	GLubyte		TGAcompare[12];								// Used To Compare TGA Header
	GLubyte		header[6];									// First 6 Useful Bytes From The Header
	GLuint		bytesPerPixel;								// Holds Number Of Bytes Per Pixel Used In The TGA File
	GLuint		imageSize;									// Used To Store The Image Size When Setting Aside Ram
	GLuint		temp;										// Temporary Variable
	GLuint		type = GL_RGBA;								// Set The Default GL Mode To RBGA (32 BPP)

	FILE *file = fopen(filename, "rb");						// Open The TGA File

	if (file == NULL ||										// Does File Even Exist?
		fread(TGAcompare, 1, sizeof(TGAcompare), file) != sizeof(TGAcompare) ||	// Are There 12 Bytes To Read?
		memcmp(TGAheader, TGAcompare, sizeof(TGAheader)) != 0 ||	// Does The Header Match What We Want?
		fread(header, 1, sizeof(header), file) != sizeof(header))				// If So Read Next 6 Header Bytes
	{
		if (file == NULL)									// Did The File Even Exist? *Added Jim Strong*
			return false;									// Return False
		else
		{
			fclose(file);									// If Anything Failed, Close The File
			return false;									// Return False
		}
	}

	texture->width = header[1] * 256 + header[0];			// Determine The TGA Width	(highbyte*256+lowbyte)
	texture->height = header[3] * 256 + header[2];			// Determine The TGA Height	(highbyte*256+lowbyte)

	if (texture->width <= 0 ||								// Is The Width Less Than Or Equal To Zero
		texture->height <= 0 ||								// Is The Height Less Than Or Equal To Zero
		(header[4] != 24 && header[4] != 32))					// Is The TGA 24 or 32 Bit?
	{
		fclose(file);										// If Anything Failed, Close The File
		return false;										// Return False
	}

	texture->bpp = header[4];							// Grab The TGA's Bits Per Pixel (24 or 32)
	bytesPerPixel = texture->bpp / 8;						// Divide By 8 To Get The Bytes Per Pixel
	imageSize = texture->width*texture->height*bytesPerPixel;	// Calculate The Memory Required For The TGA Data

	texture->imageData = (GLubyte *)malloc(imageSize);		// Reserve Memory To Hold The TGA Data

	if (texture->imageData == NULL ||							// Does The Storage Memory Exist?
		fread(texture->imageData, 1, imageSize, file) != imageSize)	// Does The Image Size Match The Memory Reserved?
	{
		if (texture->imageData != NULL)						// Was Image Data Loaded
			free(texture->imageData);						// If So, Release The Image Data

		fclose(file);										// Close The File
		return false;										// Return False
	}

	for (GLuint i = 0; i < int(imageSize); i += bytesPerPixel)		// Loop Through The Image Data
	{														// Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)
		temp = texture->imageData[i];							// Temporarily Store The Value At Image Data 'i'
		texture->imageData[i] = texture->imageData[i + 2];	// Set The 1st Byte To The Value Of The 3rd Byte
		texture->imageData[i + 2] = temp;					// Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
	}

	fclose(file);											// Close The File

	// Build A Texture From The Data
	glGenTextures(1, &texture[0].texID);					// Generate OpenGL texture IDs

	glBindTexture(GL_TEXTURE_2D, texture[0].texID);			// Bind Our Texture
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtered
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// Linear Filtered

	if (texture[0].bpp == 24)									// Was The TGA 24 Bits
	{
		type = GL_RGB;										// If So Set The 'type' To GL_RGB
	}

	glTexImage2D(GL_TEXTURE_2D, 0, type, texture[0].width, texture[0].height, 0, type, GL_UNSIGNED_BYTE, texture[0].imageData);

	return true;
}

void CSprite::TogglePause(void)
{
	pause = !pause;
}

void CSprite::SetFrozenAtCertainFrame(unsigned short framenumber)
{
	this->currentframe = framenumber;
	pause = true;
}

void CSprite::LiveOn(float dt)
{
	if(!pause)
	{
		currenttimecounter += (framespeed * dt);
		//std::cout<<"Current time counter"<<currenttimecounter<<std::endl;
		//std::cout<<"frameinterval "<<this->frameinterval<<std::endl;
		//std::cout<<"currentframe: "<<currentframe<<std::endl;

		if(currenttimecounter > frameinterval)
		{
			TranverseAnimationFrame(true,true);
		
			currenttimecounter = NULL;
		}
	
	}
}

void CSprite::Render(void)
{
	glPushMatrix();
	////glTranslatef(position.x,position.y,position.z);//uncomment this if sprite class has a position.
		glScalef(size.x,size.y,1);
	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	glColor4f(RED, GREEN,BLUE,ALPHA);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, owntexture.texID);

		if(!lateralinvert)
		{
			////simple forward animation
			glPushMatrix();

				glBegin(GL_TRIANGLE_STRIP);
				
				glTexCoord2f( currentframe	  * framesize.x	,  currentlayer * framesize.y				); glVertex2f(-0.5f,-0.5f);//bottom left
				glTexCoord2f( currentframe	  * framesize.x	,  currentlayer * framesize.y - framesize.y ); glVertex2f(-0.5f,0.5f);//top left
				glTexCoord2f((currentframe+1) * framesize.x ,  currentlayer * framesize.y				); glVertex2f(0.5f,-0.5f);//bottom right
				glTexCoord2f((currentframe+1) * framesize.x ,  currentlayer * framesize.y - framesize.y ); glVertex2f(0.5f,0.5f);//top right

				//glTexCoord2f( currentframe	  * framesize.x	,  currentlayer * framesize.y				); glVertex2f(-1.0f,-1.0f);//bottom left
				//glTexCoord2f( currentframe	  * framesize.x	,  currentlayer * framesize.y - framesize.y ); glVertex2f(-1.0f,1.0f);//top left
				//glTexCoord2f((currentframe+1) * framesize.x ,  currentlayer * framesize.y				); glVertex2f(1.0f,-1.0f);//bottom right
				//glTexCoord2f((currentframe+1) * framesize.x ,  currentlayer * framesize.y - framesize.y ); glVertex2f(1.0f,1.0f);//top right
				glEnd();
			glPopMatrix();
		}else
		{
			////simple forward animation of laterally inverted
			glPushMatrix();
		
				glBegin(GL_TRIANGLE_STRIP);
				glTexCoord2f((currentframe+1) * framesize.x ,  currentlayer * framesize.y				); glVertex2f(-0.5f,-0.5f);//bottom left
				glTexCoord2f((currentframe+1) * framesize.x ,  currentlayer * framesize.y - framesize.y ); glVertex2f(-0.5f,0.5f);//top left
				glTexCoord2f( currentframe	  * framesize.x	,  currentlayer * framesize.y				); glVertex2f(0.5f,-0.5f);//bottom right
				glTexCoord2f( currentframe	  * framesize.x	,  currentlayer * framesize.y - framesize.y ); glVertex2f(0.5f,0.5f);//top right	
				glEnd();
			glPopMatrix();
		}
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glPopMatrix();
}
void CSprite::SetAnimationLayer(ushort newlayer)
{
	this->currentlayer = newlayer;
}
void CSprite::SetFrameSpeed(float newframespeed)
{
	this->framespeed = newframespeed;
}
void CSprite::SetFrameInterval(float newframeinterval)
{
	this->frameinterval = newframeinterval;
	
}
void CSprite::SetImageSize(float x,float y)
{
	this->size.x = x;
	this->size.y = y;
}
void CSprite::SetVitalInformation(ushort maxframe,ushort numberoflayer)
{
	this->maxframe = maxframe;
	this->numberoflayer = numberoflayer;
	framesize.x = 1.0f/this->maxframe;
	framesize.y = 1.0f/this->numberoflayer;
}

void CSprite::SetColour4f(float red,float green,float blue,float alpha)
{
	this->RED = red;
	this->GREEN = green;
	this->BLUE = blue;
	this->ALPHA = alpha;
}
float CSprite::GetAlpha()
{
	return ALPHA;
}
void CSprite::SetAlpha(float newAlpha)
{
	if(newAlpha >1.0f)
	{
		newAlpha = 1.0f;
	}
	if(newAlpha <0.0f)
	{
		newAlpha = 0.0f;
	}
	ALPHA = newAlpha;
}
void CSprite::OverrideTGATexture(TextureImage* newTexture)
{
	this->owntexture = *newTexture;
}
short CSprite::GetCurrentFrameIndex()
{
	return currentframe;
}

float CSprite::GetImageSizeX()
{
	return size.x;
}
float CSprite::GetImageSizeY()
{
	return size.y;
}
void CSprite::TranverseAnimationFrame(bool forward,bool warp )
{
	if(forward)
	{
		++currentframe;
		if(currentframe > maxframe-1)
		{
			if(warp)
			{	
				currentframe = 0;
			}else
			{
				currentframe = maxframe-1;
			}
			
		}
	}else
	{
		--currentframe;
		if(currentframe < 0)
		{
			if(warp)
			{	
				currentframe = maxframe-1;
			}else
			{
				currentframe = 0;
			}
		}
	}
}
void CSprite::ToggleLateralInvertRender(void)
{
	lateralinvert = !lateralinvert;
}
void  CSprite::TranverseAnimationLayer(bool forward,bool warp)
{
	if(forward)
	{
		++currentlayer;
		if(currentlayer > numberoflayer)
		{
			if(warp)
			{	
				currentlayer = 1;
			}else
			{
				currentlayer = numberoflayer;
			}
			
		}
	}else
	{
		--currentlayer;
		if(currentlayer < 1)
		{
			if(warp)
			{	
				currentlayer = numberoflayer;
			}else
			{
				currentlayer = 1;
			}
		}
	}
}

void CSprite::CheckUp(void)
{
	std::cout<<"Current frame index: "<<currentframe<<std::endl;
	std::cout<<"Current layer index: "<<currentlayer<<std::endl;
	std::cout<<"Frame size x: "<<framesize.x<<std::endl;
	std::cout<<"Frame size y: "<<framesize.y<<std::endl;
}
