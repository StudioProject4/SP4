#include "LeverDoor.h"


CLeverDoor::CLeverDoor(void)
{
}


CLeverDoor::~CLeverDoor(void)
{
}

bool CLeverDoor::OnCollision(CBaseObject* obj)
{
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
	w0-=Vector3(0,length*0.5,0);
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
	/*
	if(go1->vel.Dot(N)<0)
	{
		return false;
	}
	*/
	w0=w0-N*(r+h*0.5);//offset the wall to a point by radius and width of wall
	float dist=(obj->pos-w0).Dot(N);
	float spd=obj->phys.vel.Dot(N);
	if(!spd)
	{
		spd=1;
	}
	
	float th=dist/spd;
	//if(th>1||th<0)
		//return false;
	

	Vector3 bh=obj->pos+obj->phys.vel*th;//point of collision

	colPoint=bh;

	Vector3 w1=w0+NP*(l+r);
	Vector3 w2=w0;
	width1=w1;
	width2=w2;
	

	if((w1-bh).Dot(NP)<0||(bh-w2).Dot(NP)<0)//check if its between the 2 edges
	{
		return false;
	}

	//check pos against this object
	Vector3 startPos=w0;
	float offset=(obj->pos.x-startPos.x);
	if(curAngle!=0)
		offset*=(curAngle/abs(curAngle));
	float nYpos=0;
	
	float tempAngle=-curAngle;
	nYpos=cos(tempAngle*3.142/180)*-offset;//get y pos based on the angle and the offset
	//offset it based on height of object
	nYpos+=pos.y;

	//use dot product to check normals and to get the 
	//dir the object is relative to me(wheather is to the left or to the right)

	//change angle based on direction the object is in
	float delta=0.0166;
	float leverGrav=200;
	if(obj->phys.vel.LengthSquared()==0)
	{
		//angleVel-=normal.y*leverGrav*delta;
		//obj->pos.y=nYpos;
		applyGrav=false;
	}
	else if((w0-b1).Dot(normal)>0)//go1 pos to go2 pos
	{
		float nAVel=obj->phys.vel.Dot(normal);
		angleVel-=nAVel;
		Vector3 vel=obj->phys.vel;
		float ratio=(nAVel*nAVel)/vel.LengthSquared();
		obj->phys.vel=obj->phys.vel*ratio;
		cout<<"++:"<<nAVel<<"\n";
		if(curAngle>=0)
		{
			obj->pos.y=nYpos;
		}
	}
	else
	{
		float nAVel=obj->phys.vel.Dot(normal);
		angleVel-=nAVel;
		Vector3 vel=obj->phys.vel;
		float ratio=(nAVel*nAVel)/vel.LengthSquared();
		obj->phys.vel=obj->phys.vel*ratio;
		cout<<"--:"<<nAVel<<"\n";
		if(curAngle<=0)
		{
			obj->pos.y=nYpos;
		}
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
	float leverGrav=200;
	if(curAngle>-70&&curAngle<70)
	{
		if(applyGrav||angleVel!=0)
			angleVel+=normal.y*leverGrav*delta;
		if(angleVel<1&&angleVel>-1)
			angleVel=0;
	}
	applyGrav=true;
	curAngle+=angleVel*delta;
	normal.x=cos(curAngle/360*2*3.142);
	normal.y=sin(curAngle/360*2*3.142);	
	
	//test limits
	if(curAngle>onTrigger)
	{
		//set on
	}
	else if(curAngle<offTrigger)
	{
		//set off
	}
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

	return true;
}

bool CLeverDoor::Render()
{
	
	//glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glColor3f(1,1,1);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glTranslatef(pos.x,pos.y,0);
		glTranslatef(0,-length/2,0);
		glRotatef(curAngle,0,0,1);
		glTranslatef(0,length/2,0);
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
	glPushMatrix();
	glColor3f(0,1,1);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glTranslatef(width1.x,width1.y,0);
		glScalef(5,5,0);
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
	glPushMatrix();
	glColor3f(0,1,1);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glTranslatef(width2.x,width2.y,0);
		glScalef(5,5,0);
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
	
	glPushMatrix();
	glColor3f(1,0,1);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glTranslatef(colPoint.x,colPoint.y,0);
		glScalef(5,5,0);
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
	glPushMatrix();
	glColor3f(1,1,0);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glTranslatef(pos.x,pos.y-length*0.5,0);
		glScalef(5,5,0);
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
	this->pos=pos;
	this->length=size.y;
	this->width=size.x;
	maxAngle=70;
	minAngle=-70;
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
	return true;
}