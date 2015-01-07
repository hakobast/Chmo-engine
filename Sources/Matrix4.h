//
//  Matrix4.h
//  OpenGLTesting
//
//  Created by Hakob on 11/7/14.
//  Copyright (c) 2014 Haksist. All rights reserved.
//

#ifndef OpenGLTesting_Matrix4_h
#define OpenGLTesting_Matrix4_h

#include <GL\glut.h>
#include <iostream>
#include <math.h>

#define Sign(v) (v == 0.0f ? 0.0f : (v > 0.0f ? 1.0f : -1.0f))

using namespace std;

/*
|0 4 8  12|
|1 5 9  13|
|2 6 10 14|
|3 7 11 15|
*/
struct Matrix4
{
private:
	GLfloat m[16];

public:
	Matrix4(bool identity = true){

		if (identity)
			makeIdentity();
		else
			for (int i = 0; i < 16; i++)
				m[i] = 0.0f;
	}

	void makeIdentity();
	void setRow(int row, const GLfloat arr[], int size);
	void setColumn(int column,const GLfloat arr[], int size);
	void print() const;
	 
	Matrix4& setTranslation(GLfloat x, GLfloat y, GLfloat z);
	Matrix4& setRotation(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
	Matrix4& setScale(GLfloat x, GLfloat y, GLfloat z);
	Matrix4& TranslateMatrix(GLfloat x, GLfloat y, GLfloat z);
	Matrix4& RotateMatrix(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
	Matrix4& ScaleMatrix(GLfloat x, GLfloat y, GLfloat z);

	Matrix4 operator* (const Matrix4& n) const;
	Matrix4& operator*= (const Matrix4& n);
	GLfloat& operator[] (int index);
	GLfloat operator[] (int index) const;
};

inline void Matrix4::makeIdentity()
{
	m[0] = 1.0f; m[4] = 0.0f; m[8] = 0.0f; m[12] = 0.0f;
	m[1] = 0.0f; m[5] = 1.0f; m[9] = 0.0f; m[13] = 0.0f;
	m[2] = 0.0f; m[6] = 0.0f; m[10] = 1.0f; m[14] = 0.0f;
	m[3] = 0.0f; m[7] = 0.0f; m[11] = 0.0f; m[15] = 1.0f;
}

/*
row = [0,3]
size = [1,4]
*/
inline void Matrix4::setRow(int row, const GLfloat arr[], int size)
{
	for (int i = 0; i < size; i++)
		m[row + i*4] = arr[i];
}

/*
column = [0,3]
size = [1,4]
*/
inline void Matrix4::setColumn(int column, const GLfloat arr[], int size)
{
	for (int i = 0; i < size; i++)
		m[column*4 + i] = arr[i];
}

inline Matrix4& Matrix4::setTranslation(GLfloat x, GLfloat y, GLfloat z)
{
	m[12] = x; m[13] = y; m[14] = z; return *this;
}

inline void Matrix4::print() const
{
	printf("***********************\n");
	for (int j = 0; j < 4; j++)
	{
		for (int k = j; k < 16; k += 4)
		{
			printf("[%0.2f]", m[k]);
		}

		printf("\n");
	}
}

inline GLfloat& Matrix4:: operator[] (int index)
{
	return m[index];
}

inline GLfloat Matrix4:: operator[] (int index) const
{
	return m[index];
}
#endif