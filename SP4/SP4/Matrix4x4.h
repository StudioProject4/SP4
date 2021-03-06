#pragma once
#include <cmath>
#include <iostream>
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#include <stdio.h>
#include <windows.h> // Header File For Windows
#include <gl\gl.h> // Header File For The OpenGL32 Library
#include <gl\glu.h> // Header File For The GLu32 Library
using namespace std;

class Matrix4x4
{
public:
	float matrix[16];
	Matrix4x4();
	bool rotated;
	void Translatef(float x,float y,float z);
	void Rotatef(float angle,float x,float y,float z);
	void Scalef(float xScale,float yScale,float zScale);
	void Inverse();
	void Finish();
	void Clear();
	void coutM();
	int INDEX4(int x,int y);
	float angle;
	void PrintSelf(void);

	//! multiplication by a matrix
	const Matrix4x4 operator *(const Matrix4x4 &m)
	{
		Matrix4x4 temp;
		temp.matrix[0] = matrix[0]*m.matrix[0] + matrix[1]*m.matrix[4] + matrix[2]*m.matrix[8] + matrix[3]*m.matrix[12];
		temp.matrix[1] = matrix[0]*m.matrix[1] + matrix[1]*m.matrix[5] + matrix[2]*m.matrix[9] + matrix[3]*m.matrix[13];
		temp.matrix[2] = matrix[0]*m.matrix[2] + matrix[1]*m.matrix[6] + matrix[2]*m.matrix[10] + matrix[3]*m.matrix[14];
		temp.matrix[3] = matrix[0]*m.matrix[3] + matrix[1]*m.matrix[7] + matrix[2]*m.matrix[11] + matrix[3]*m.matrix[15];

		temp.matrix[4] = matrix[4]*m.matrix[0] + matrix[5]*m.matrix[4] + matrix[6]*m.matrix[8] + matrix[7]*m.matrix[12];
		temp.matrix[5] = matrix[4]*m.matrix[1] + matrix[5]*m.matrix[5] + matrix[6]*m.matrix[9] + matrix[7]*m.matrix[13];
		temp.matrix[6] = matrix[4]*m.matrix[2] + matrix[5]*m.matrix[6] + matrix[6]*m.matrix[10] + matrix[7]*m.matrix[14];
		temp.matrix[7] = matrix[4]*m.matrix[3] + matrix[5]*m.matrix[7] + matrix[6]*m.matrix[11] + matrix[7]*m.matrix[15];

		temp.matrix[8] = matrix[8]*m.matrix[0] + matrix[9]*m.matrix[4] + matrix[10]*m.matrix[8] + matrix[11]*m.matrix[12];
		temp.matrix[9] = matrix[8]*m.matrix[1] + matrix[9]*m.matrix[5] + matrix[10]*m.matrix[9] + matrix[11]*m.matrix[13];
		temp.matrix[10] = matrix[8]*m.matrix[2] + matrix[9]*m.matrix[6] + matrix[10]*m.matrix[10] + matrix[11]*m.matrix[14];
		temp.matrix[11] = matrix[8]*m.matrix[3] + matrix[9]*m.matrix[7] + matrix[10]*m.matrix[11] + matrix[11]*m.matrix[15];

		temp.matrix[12] = matrix[12]*m.matrix[0] + matrix[13]*m.matrix[4] + matrix[14]*m.matrix[8] + matrix[15]*m.matrix[12];
		temp.matrix[13] = matrix[12]*m.matrix[1] + matrix[13]*m.matrix[5] + matrix[14]*m.matrix[9] + matrix[15]*m.matrix[13];
		temp.matrix[14] = matrix[12]*m.matrix[2] + matrix[13]*m.matrix[6] + matrix[14]*m.matrix[10] + matrix[15]*m.matrix[14];
		temp.matrix[15] = matrix[12]*m.matrix[3] + matrix[13]*m.matrix[7] + matrix[14]*m.matrix[11] + matrix[15]*m.matrix[15];

		return temp;
	}

	Matrix4x4& operator=(const Matrix4x4 &m)
	{
		//Matrix4x4 temp;
		matrix[0] = m.matrix[0];
		matrix[1] = m.matrix[1];
		matrix[2] = m.matrix[2];
		matrix[3] = m.matrix[3];

	    matrix[4] = m.matrix[4];
		matrix[5] = m.matrix[5];
		matrix[6] = m.matrix[6];
		matrix[7] = m.matrix[7];

		matrix[8] = m.matrix[8];
		matrix[9] = m.matrix[9];
		matrix[10] = m.matrix[10];
		matrix[11] = m.matrix[11];

		matrix[12] = m.matrix[12];
		matrix[13] = m.matrix[13];
		matrix[14] = m.matrix[14];
		matrix[15] = m.matrix[15];
		return *this;

	}
	bool rotatedCheck();
	bool gluInvertMatrix()
		{
			float inv[16], det;
			unsigned short i;

			inv[0] = matrix[5]  * matrix[10] * matrix[15] - 
					 matrix[5]  * matrix[11] * matrix[14] - 
					 matrix[9]  * matrix[6]  * matrix[15] + 
					 matrix[9]  * matrix[7]  * matrix[14] +
					 matrix[13] * matrix[6]  * matrix[11] - 
					 matrix[13] * matrix[7]  * matrix[10];

			inv[4] = -matrix[4]  * matrix[10] * matrix[15] + 
					  matrix[4]  * matrix[11] * matrix[14] + 
					  matrix[8]  * matrix[6]  * matrix[15] - 
					  matrix[8]  * matrix[7]  * matrix[14] - 
					  matrix[12] * matrix[6]  * matrix[11] + 
					  matrix[12] * matrix[7]  * matrix[10];

			inv[8] = matrix[4]  * matrix[9] * matrix[15] - 
					 matrix[4]  * matrix[11] * matrix[13] - 
					 matrix[8]  * matrix[5] * matrix[15] + 
					 matrix[8]  * matrix[7] * matrix[13] + 
					 matrix[12] * matrix[5] * matrix[11] - 
					 matrix[12] * matrix[7] * matrix[9];

			inv[12] = -matrix[4]  * matrix[9] * matrix[14] + 
					   matrix[4]  * matrix[10] * matrix[13] +
					   matrix[8]  * matrix[5] * matrix[14] - 
					   matrix[8]  * matrix[6] * matrix[13] - 
					   matrix[12] * matrix[5] * matrix[10] + 
					   matrix[12] * matrix[6] * matrix[9];

			inv[1] = -matrix[1]  * matrix[10] * matrix[15] + 
					  matrix[1]  * matrix[11] * matrix[14] + 
					  matrix[9]  * matrix[2] * matrix[15] - 
					  matrix[9]  * matrix[3] * matrix[14] - 
					  matrix[13] * matrix[2] * matrix[11] + 
					  matrix[13] * matrix[3] * matrix[10];

			inv[5] = matrix[0]  * matrix[10] * matrix[15] - 
					 matrix[0]  * matrix[11] * matrix[14] - 
					 matrix[8]  * matrix[2] * matrix[15] + 
					 matrix[8]  * matrix[3] * matrix[14] + 
					 matrix[12] * matrix[2] * matrix[11] - 
					 matrix[12] * matrix[3] * matrix[10];

			inv[9] = -matrix[0]  * matrix[9] * matrix[15] + 
					  matrix[0]  * matrix[11] * matrix[13] + 
					  matrix[8]  * matrix[1] * matrix[15] - 
					  matrix[8]  * matrix[3] * matrix[13] - 
					  matrix[12] * matrix[1] * matrix[11] + 
					  matrix[12] * matrix[3] * matrix[9];

			inv[13] = matrix[0]  * matrix[9] * matrix[14] - 
					  matrix[0]  * matrix[10] * matrix[13] - 
					  matrix[8]  * matrix[1] * matrix[14] + 
					  matrix[8]  * matrix[2] * matrix[13] + 
					  matrix[12] * matrix[1] * matrix[10] - 
					  matrix[12] * matrix[2] * matrix[9];

			inv[2] = matrix[1]  * matrix[6] * matrix[15] - 
					 matrix[1]  * matrix[7] * matrix[14] - 
					 matrix[5]  * matrix[2] * matrix[15] + 
					 matrix[5]  * matrix[3] * matrix[14] + 
					 matrix[13] * matrix[2] * matrix[7] - 
					 matrix[13] * matrix[3] * matrix[6];

			inv[6] = -matrix[0]  * matrix[6] * matrix[15] + 
					  matrix[0]  * matrix[7] * matrix[14] + 
					  matrix[4]  * matrix[2] * matrix[15] - 
					  matrix[4]  * matrix[3] * matrix[14] - 
					  matrix[12] * matrix[2] * matrix[7] + 
					  matrix[12] * matrix[3] * matrix[6];

			inv[10] = matrix[0]  * matrix[5] * matrix[15] - 
					  matrix[0]  * matrix[7] * matrix[13] - 
					  matrix[4]  * matrix[1] * matrix[15] + 
					  matrix[4]  * matrix[3] * matrix[13] + 
					  matrix[12] * matrix[1] * matrix[7] - 
					  matrix[12] * matrix[3] * matrix[5];

			inv[14] = -matrix[0]  * matrix[5] * matrix[14] + 
					   matrix[0]  * matrix[6] * matrix[13] + 
					   matrix[4]  * matrix[1] * matrix[14] - 
					   matrix[4]  * matrix[2] * matrix[13] - 
					   matrix[12] * matrix[1] * matrix[6] + 
					   matrix[12] * matrix[2] * matrix[5];

			inv[3] = -matrix[1] * matrix[6] * matrix[11] + 
					  matrix[1] * matrix[7] * matrix[10] + 
					  matrix[5] * matrix[2] * matrix[11] - 
					  matrix[5] * matrix[3] * matrix[10] - 
					  matrix[9] * matrix[2] * matrix[7] + 
					  matrix[9] * matrix[3] * matrix[6];

			inv[7] = matrix[0] * matrix[6] * matrix[11] - 
					 matrix[0] * matrix[7] * matrix[10] - 
					 matrix[4] * matrix[2] * matrix[11] + 
					 matrix[4] * matrix[3] * matrix[10] + 
					 matrix[8] * matrix[2] * matrix[7] - 
					 matrix[8] * matrix[3] * matrix[6];

			inv[11] = -matrix[0] * matrix[5] * matrix[11] + 
					   matrix[0] * matrix[7] * matrix[9] + 
					   matrix[4] * matrix[1] * matrix[11] - 
					   matrix[4] * matrix[3] * matrix[9] - 
					   matrix[8] * matrix[1] * matrix[7] + 
					   matrix[8] * matrix[3] * matrix[5];

			inv[15] = matrix[0] * matrix[5] * matrix[10] - 
					  matrix[0] * matrix[6] * matrix[9] - 
					  matrix[4] * matrix[1] * matrix[10] + 
					  matrix[4] * matrix[2] * matrix[9] + 
					  matrix[8] * matrix[1] * matrix[6] - 
					  matrix[8] * matrix[2] * matrix[5];

			det = matrix[0] * inv[0] + matrix[1] * inv[4] + matrix[2] * inv[8] + matrix[3] * inv[12];

			if (det == 0)
				return false;

			det = 1.0f / det;

			for (i = 0; i < 16; i++)
				matrix[i] = inv[i] * det;

			return true;
		}
};
