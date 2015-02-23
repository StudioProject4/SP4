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
	Vector3 NP(-N.y,N.x,0);
	NP.Normalize();
	w0=w0-NP*(length*0.5);
	float r=obj->phys.size.x;
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
	w0=w0-N*(r+h/2);//offset the wall to a point by radius and width of wall
	float dist=(obj->pos-w0).Dot(N);
	float spd=obj->phys.vel.Dot(N);
	
	float th=dist/spd;
	if(th>500||th<0)
		return false;
	

	Vector3 bh=obj->pos+obj->phys.vel*th;//point of collision

	Vector3 w1=w0+NP*(l);
	Vector3 w2=w0;
	float useless=(w1-bh).Dot(NP);
	float useless2=(bh-w2).Dot(NP);
	if((w1-bh).Dot(NP)<0||(bh-w2).Dot(NP)<0)//check if its between the 2 edges
	{
		return false;
	}

	//use dot product to check normals and to get the 
	//dir the object is relative to me(wheather is to the left or to the right)

	//change angle based on direction the object is in
	float p=(w0-b1).Dot(normal);
	if((w0-b1).Dot(normal)>0)//go1 pos to go2 pos
	{
		cout<<"++\n";
		angleVel+=30;//change to add/subtract force
		obj->phys.vel.y*=0.5;
	}
	else
	{
		cout<<"--\n";
		angleVel-=30;
		obj->phys.vel.y*=0.5;
	}
	//applyGrav=true;
	//move the object back so that its not colliding anymore

	//after changing the angle

	//increase bounding box size based on the new angle;
	obj->phys.inAir=false;
	return true;
}

bool CLeverDoor::Update()
{
	float delta=0.0166;
	//pos=phys.Update(pos);
	float leverGrav=200;
	if(curAngle>-70&&curAngle<70)
	{
		angleVel+=normal.y*leverGrav*delta;
		applyGrav=true;
	}
	else if(applyGrav)
	{
		angleVel=0;
		applyGrav=false;
	}

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

	glColor3f(1,1,1);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glTranslatef(pos.x,pos.y,0);
		glTranslatef(0,-length/2,0);
		glRotatef(-curAngle,0,0,1);
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