#pragma once
#include<iostream>
struct SContainer2D
{
	float x;
	float y;

	SContainer2D()
		:x(0)
		,y(0)
	{
		
	}
	SContainer2D(float x,float y)
		:x(x)
		,y(y)
	{
		
	}

	bool operator==( const SContainer2D& rhs ) const
	{
		//bool result = false;
		if(this->x == rhs.x && this->y == rhs.y)
		{
			return true;
		}else
		{
			return false;
		}
		return false;
	}

	bool operator!=( const SContainer2D& rhs ) const
	{
		//bool result = false;
		if(this->x == rhs.x && this->y == rhs.y)
		{
			return false;
		}else
		{
			return true;
		}
		return false;
	}

	SContainer2D SContainer2D::operator-( const SContainer2D& rhs ) const
	{
		return SContainer2D(x - rhs.x, y - rhs.y);
	}
	friend std::ostream& operator<<( std::ostream& os, SContainer2D& rhs) //print to ostream
	{

		os << "[ " << rhs.x << ", " << rhs.y << " ]";
		return os;

	}
};

