#include "ChineseMale.h"
#include "Physics.h"

#include "ImageManager.h"

CChineseMale :: CChineseMale()
{
}

CChineseMale :: ~CChineseMale()
{
	if(theSprite != NULL)
	{
		delete theSprite;
		theSprite = NULL;
	}
}

bool CChineseMale :: Init(Vector3 newPos,Vector3 newDir,int entityID)
{
	pos = newPos;
	dir = newDir;
	id = entityID;
	Init();
	return true;
}

bool CChineseMale :: Update()
{
	pos=phys.Update(pos);
	//std::cout<<phys.Update(pos)<<std::endl
	if(GetIsInvulnerable() == true)
	{
		if(invulTimer->TestTime(refTime))
		{
			SetIsInvulnerable(true);
			invulTimer->SetActive(false,refTime);
		}
	}
	return true;
}

bool CChineseMale :: Init()
{
	name = "GenericChineseKid";
	tag = "ChineseMale";
	genericTag = "Character";

	theSprite = new CSprite(1,1,0);
	
	theSprite->OverrideTGATexture(CImageManager::GetInstance()->GetTGAImage("sonia2.tga"));
	//theSprite->LoadTGA("sonia2.tga");
	
	SetIsInvulnerable(false);

	phys.Init(pos,Vector3(theSprite->GetImageSizeX(),theSprite->GetImageSizeY()));
	this->UpdateObjectTopLeftAndBottomRightPoint(false);
	SetPlayerID(1);

	invulTimer = MVCTime :: GetInstance();
	refTime = invulTimer->PushNewTime(1000);
	invulTimer->SetActive(false,refTime);
	
	return true;
}

bool CChineseMale :: Reset()
{
	return Init();
}

bool CChineseMale :: CleanUp()
{
	return true;
}
bool CChineseMale :: OnCollision2(CBaseObject* a_obj,bool again)
{

	return true;
}
bool CChineseMale :: Render()
{
	glPushMatrix();
	glTranslatef(pos.x,pos.y,pos.z);
	theSprite->Render();
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(0,1,0);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glTranslatef(pos.x,pos.y,0);
		//glRotatef(curAngle,0,0,1);
		glScalef(this->phys.size.x,this->phys.size.y,0);
		//glBindTexture(GL_TEXTURE_2D,this->testimage.texID);
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
		glPopMatrix();
	glPushMatrix();
	return true;
}