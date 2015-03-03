#include "RakNet\RakPeerInterface.h"
#include "RakNet\BitStream.h"
#include "MyMsgIDs.h"

#include "LeverDoor.h"
#include "Door.h"

using namespace RakNet;

extern RakPeerInterface* rakPeerGlobal;

CLeverDoor::CLeverDoor(void):
lastTime(0)
{
}


CLeverDoor::~CLeverDoor(void)
{
}

bool CLeverDoor::OnCollision2(CBaseObject* obj,bool again)
{
	//std::cout<<"lever door collieded"<<std::endl;
	//finding the normal to this object based on the length
	//cos(angle)=adjacent/hyp
	//assuming hyp(length)=1
	//cos(angle)=adjacent=x
	//same logic for sin
	normal.x=cos(curAngle/360*2*3.142);
	normal.y=sin(curAngle/360*2*3.142);	

	//do more precise collision checkingVector3 w0=go2->pos;

	Vector3 w0=this->pos;
	Vector3 b1=obj->pos;
	Vector3 N=this->normal;
	w0+=Vector3(0,length*0.5,0);
	Vector3 NP(-N.y,N.x,0);
	NP.Normalize();
	//w0=w0-NP*(length*0.5);
	float r=obj->phys.size.y*0.6;
	float h=this->width;
	float l=this->length;


	if((w0-b1).Dot(N)<0)//go1 pos to go2 pos
	{
		N=-N;
	}
	//*
	if(obj->phys.vel.Dot(N)<0)
	{
		//return false;
	}
	//*/
	w0=w0-N*(r+h*0.5);//offset the wall to a point by radius and width of wall
	float dist=(obj->pos-w0).Dot(N);
	float spd=obj->phys.vel.Dot(N);
	if(!spd)
	{
		spd=1;
	}
	
	float th=dist/spd;
	if(th>500||th<0)
		return false;
	

	Vector3 bh=obj->pos+obj->phys.vel*th;//point of collision

	colPoint=bh;

	Vector3 w1=w0+NP*(r);
	Vector3 w2=w0-NP*(l+r);
	width1=w1;
	width2=w2;
	
	//*
	if((w1-bh).Dot(NP)<0||(bh-w2).Dot(NP)<0)//check if its between the 2 edges
	{
		return false;
	}
	//*/
	//check pos against this object
	Vector3 startPos=w0;
	float offset=(obj->pos.x-startPos.x);
	if(curAngle!=0)
		offset*=(curAngle/abs(curAngle));
	float nYpos=0;
	
	float tempAngle=-curAngle;
	nYpos=cos(tempAngle*3.1415/180)*-(offset);//get y pos based on the angle and the offset
	//offset it based on height of object
	nYpos+=pos.y+2;

	//use dot product to check normals and to get the 
	//dir the object is relative to me(wheather is to the left or to the right)

	//change angle based on direction the object is in
	float delta=0.0166;
	float leverGrav=200;
	
	bool modded=false;

	if(obj->phys.vel.LengthSquared()==0)
	{
		//angleVel-=normal.y*leverGrav*delta;
		//obj->pos.y=nYpos;
		//applyGrav=false;
	}
	else
	{
		if(obj->phys.vel.Dot(N)>0)
		{
			float nAVel=obj->phys.vel.Dot(normal);//finds the mag of vel in dir of the normal
			angleVel+=nAVel;//mod the angle vel based on that
			Vector3 vel=obj->phys.vel;
			float ratio=(nAVel*nAVel)/vel.LengthSquared();
			obj->phys.vel=obj->phys.vel*ratio;//reduce the vel by a percentage based on how 
			modded=true;
		}
		if((w0-b1).Dot(normal)>0)//go1 pos to go2 pos
		{
			if(curAngle<=-40)
			{
				obj->pos.y=nYpos;
				obj->phys.inAir=false;
				if(obj->phys.vel.x>-0.001&&obj->phys.vel.x<0.001)
					obj->pos.x+=5*delta;
				modded=true;
			}
		}
		else
		{
			
			if(curAngle>=40)
			{
				obj->pos.y=nYpos;
				obj->phys.inAir=false;
				if(obj->phys.vel.x>-0.001&&obj->phys.vel.x<0.001)
					obj->pos.x-=5*delta;;
				modded=true;
			}
		}
	}
	long now=timeGetTime();
	if(now-lastTime>50&&modded&&!again)
	{
		BitStream bs;
		unsigned char msgid=ID_OBJ_UPDATE;
		bs.Write(msgid);
		bs.Write(this->tag);
		bs.Write(this->id);
		bs.Write(obj->id);
		bs.Write(this->curAngle);
		bs.Write(this->angleVel);
		//bs.Write(this->applyGrav);
		bs.Write(obj->pos.x);
		bs.Write(obj->pos.y);
		bs.Write(obj->pos.z);
		bs.Write(obj->phys.vel.x);
		bs.Write(obj->phys.vel.y);
		bs.Write(obj->phys.vel.z);
		rakPeerGlobal->Send(&bs,HIGH_PRIORITY,RELIABLE_ORDERED,0,UNASSIGNED_SYSTEM_ADDRESS,true);
	}
	//move the object back so that its not colliding anymore

	//after changing the angle

	//increase bounding box size based on the new angle;
	//obj->phys.inAir=false;
	return true;
}

bool CLeverDoor::Update()
{
	float delta=0.0166;
	//pos=phys.Update(pos);
	float leverGrav=-200;
	if(curAngle>-70&&curAngle<70)
	{
		if(applyGrav||angleVel!=0)
			angleVel-=normal.y*leverGrav*delta;
		if(angleVel<1&&angleVel>-1)
			angleVel=0;
	}
	applyGrav=true;
	curAngle+=angleVel*delta;
	normal.x=cos(curAngle/360*2*3.142);
	normal.y=sin(curAngle/360*2*3.142);	
	
	if(curAngle>maxAngle)
	{
		curAngle=maxAngle;
		angleVel=0;
	}
	else if(curAngle<minAngle)
	{
		curAngle=minAngle;
		angleVel=0;
	}
	if(curAngle<offTrigger)
	{
		triggered=false;
		doorLink->Trigger();
	}
	else if(curAngle>onTrigger)
	{
		triggered=true;
		doorLink->Trigger();
	}

	return true;
}

bool CLeverDoor::Render()
{
	glPushMatrix();
	glColor3f(1,1,1);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glTranslatef(pos.x,pos.y,0);
		glTranslatef(0,length/2,0);
		glRotatef(curAngle,0,0,1);
		glTranslatef(0,-length/2,0);
		glScalef(this->width,this->length,0);
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
	//glDisable(GL_TEXTURE_2D);
	
	glPopMatrix();
	return true;
}

bool CLeverDoor::Init(Vector3 pos,Vector3 size)
{
	tag= "CLeverDoor";
	genericTag = "CObstacleBase";
	name = "LeverDoor";
	this->pos=pos;
	this->length=size.y;
	this->width=size.x;
	maxAngle=70;
	minAngle=-70;
	onTrigger=40;
	offTrigger=-40;
	phys.Init(pos,size);
	curAngle=-20;
	angleVel=0;
	applyGrav=false;
	if(size.x>size.y)
	{
		phys.size.y=size.x*2;
		phys.size.x*=2;
	}
	else
	{
		phys.size.x=size.y*2;
		phys.size.y*=2;
	}
	this->UpdateObjectTopLeftAndBottomRightPoint(false);
	return true;
}