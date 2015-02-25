#include "ChineseMale.h"
#include "Physics.h"

CChineseMale :: CChineseMale()
{
	Init();
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
	//std::cout<<phys.Update(pos)<<std::endl;
	return true;
}

bool CChineseMale :: Init()
{
	name = "GenericChineseKid";
	tag = "ChineseMale";
	genericTag = "Character";

	theSprite = new CSprite(1,1,0);
	theSprite->LoadTGA("sonia2.tga");

	phys.Init(pos,Vector3(theSprite->GetImageSizeX(),theSprite->GetImageSizeY(),1));
	SetPlayerID(1);

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
bool CChineseMale :: OnCollision(CBaseObject* a_obj)
{
	if(a_obj->genericTag = "Character")
	{
		//nothing
	}
	if(a_obj->genericTag = "Enemy")
	{
		if(a_obj->tag = "MalayMob")
		{
			if(clock() - invultimer > 5000)
			{
				hp.TakeDMG();
				std :: cout << "ChineseMale's HP : " << hp.GetHealth() << std :: endl;
			}
		}
	}
	//if(a_obj->genericTag = "Powerup")
	//{
	//	//to be continued when powerups are done
	//	if(a_obj->name = "HpAdd")
	//	{
	//		if(clock() - invultimer > 5000)
	//		{
	//			hp.RecoverHealth();
	//		}
	//	}

	//	if(a_obj->name = "Invincible")
	//	{
	//	}
	//	if(a_obj->name = "PtAdd")
	//	{
	//		points.PointsReceive(10);
	//	}
	//	if(a_obj->name = "JumpHt")
	//	{
	//	}
	//	if(a_obj->name = "SpdAdd")
	//	{
	//	}

	//}
	if(a_obj->genericTag = "Obstacle")
	{
		//to be continued when powerups are done
	}

	//if(a_obj->genericTag = "Character")
	//{
	//	//nothing
	//}
	//if(a_obj->genericTag = "Enemy")
	//{
	//	if(a_obj->tag = "MalayMob")
	//	{
	//		if(clock() - invultimer > 5000)
	//		{
	//			hp.TakeDMG();
	//			std :: cout << "ChineseMale's HP : " << hp.GetHealth() << std :: endl;
	//		}
	//	}
	//}
	//if(a_obj->genericTag = "Powerup")
	//{
	//	//to be continued when powerups are done
	//}
	//if(a_obj->genericTag = "Obstacle")
	//{
	//	//to be continued when powerups are done
	//}

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