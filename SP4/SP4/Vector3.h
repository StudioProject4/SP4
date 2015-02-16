/******************************************************************************/
/*!
\file	Vector3.h
\author Wen Sheng Tang
\brief
Struct to define a 3D vector
*/
/******************************************************************************/

#ifndef VECTOR3_H
#define VECTOR3_H

#include "MyMath.h"
#include <iostream>
#include "Matrix4x4.h"
#pragma warning( disable: 4290 ) //for throw(DivideByZero)

/******************************************************************************/
/*!
		Class Vector3:
\brief	Defines a 3D vector and its methods
*/
/******************************************************************************/
struct Vector3
{
	float x, y, z;
	bool IsEqual(float a, float b) const;

	Vector3(float a = 0.0, float b = 0.0, float c = 0.0);
	Vector3(const Vector3 &rhs);
	~Vector3();
	
	void Set( float a = 0, float b = 0, float c = 0 ); //Set all data
	void SetZero( void ); //Set all data to zero
	bool IsZero( void ) const; //Check if data is zero

	Vector3 operator+( const Vector3& rhs ) const; //Vector addition
	Vector3& operator+=( const Vector3& rhs ); 
	
	Vector3 operator-( const Vector3& rhs ) const; //Vector subtraction
	Vector3& operator-=( const Vector3& rhs );
	
	Vector3 operator-( void ) const; //Unary negation
	
	Vector3 operator*( float scalar ) const; //Scalar multiplication
	Vector3& operator*=( float scalar );

	bool operator==( const Vector3& rhs ) const; //Equality check
	bool operator!= ( const Vector3& rhs ) const; //Inequality check

	Vector3& operator=(const Vector3& rhs); //Assignment operator

	float Length( void ) const; //Get magnitude
	float LengthSquared (void ) const; //Get square of magnitude
	
	float Dot( const Vector3& rhs ) const; //Dot product
	Vector3 Cross( const Vector3& rhs ) const; //Cross product
	
	//Return a copy of this vector, normalized
	//Throw a divide by zero exception if normalizing a zero vector
	Vector3 Normalized( void ) const throw( DivideByZero );
	
	//Normalize this vector and return a reference to it
	//Throw a divide by zero exception if normalizing a zero vector
	Vector3& Normalize( void ) throw( DivideByZero );
	
	friend std::ostream& operator<<( std::ostream& os, Vector3& rhs); //print to ostream

	friend Vector3 operator*( float scalar, const Vector3& rhs ); //what is this for?

//multiply this vector by a scalar
	Vector3 operator*(const Matrix4x4 &m) const
	{
		return Vector3( x*m.matrix[0] + y*m.matrix[4] + z*m.matrix[8] + 1*m.matrix[12],
						 x*m.matrix[1] + y*m.matrix[5] + z*m.matrix[9] + 1*m.matrix[13],
						 x*m.matrix[2] + y*m.matrix[6] + z*m.matrix[10] + 1*m.matrix[14] );
	}

};

#endif //VECTOR3_H
