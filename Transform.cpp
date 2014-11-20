//
//  Transform.cpp
//  OpenGLTesting
//
//  Created by Hakob on 11/7/14.
//  Copyright (c) 2014 Haksist. All rights reserved.
//

#include <iostream>
#include <math.h>
#include "Transform.h"

using namespace std;

GameTransform::~GameTransform()
{
	cout << "~GameTransform()" << endl;
}

void GameTransform::Init()
{
	cout << "GameTransform Init()" << endl;
}

void GameTransform::Update()
{
	cout << "Update Transform" << endl;
	/*getMatrix(true);
	glMultMatrixf(&matrix[0]);*/
}

Matrix4 GameTransform::getMatrix(bool calcScale)
{
	matrix[3] = 0.0f;
	matrix[7] = 0.0f;
	matrix[11] = 0.0f;
	matrix[15] = 1.0f;

	memcpy(&matrix[0], &Right()[0], sizeof(GLfloat)* 3);
	memcpy(&matrix[4], &_Up[0], sizeof(GLfloat)* 3);
	memcpy(&matrix[8], &_Forward[0], sizeof(GLfloat)* 3);
	memcpy(&matrix[12], &Location[0], sizeof(GLfloat)* 3);

	if (calcScale)
	{
		matrix[0] *= ScaleLocal[0];
		matrix[1] *= ScaleLocal[0];
		matrix[2] *= ScaleLocal[0];

		matrix[4] *= ScaleLocal[1];
		matrix[5] *= ScaleLocal[1];
		matrix[6] *= ScaleLocal[1];

		matrix[8] *= ScaleLocal[2];
		matrix[9] *= ScaleLocal[2];
		matrix[10] *= ScaleLocal[2];
	}

	return matrix;
}

void GameTransform::applyTransformation()
{
	getMatrix(true);
	glMultMatrixf(&matrix[0]);
}

void GameTransform::TranslateForward(GLfloat step)
{
	Location[0] += _Forward[0] * step;
	Location[1] += _Forward[1] * step;
	Location[2] += _Forward[2] * step;
}

void GameTransform::TranslateUp(GLfloat step)
{
	Location[0] += _Up[0] * step;
	Location[1] += _Up[1] * step;
	Location[2] += _Up[2] * step;
}

void GameTransform::TranslateRight(GLfloat step)
{
	Vector3 R = Right();
	Location[0] += R[0] * step;
	Location[1] += R[1] * step;
	Location[2] += R[2] * step;
}

void GameTransform::RotateY(GLfloat Angle)
{
	matrix.setRotation(Angle*DEG_TO_RAD, _Up[0], _Up[1], _Up[2]);
	_Forward.rotateVector(matrix);
}

void GameTransform::RotateZ(GLfloat Angle)
{
	matrix.setRotation(Angle*DEG_TO_RAD, _Forward[0], _Forward[1], _Forward[2]);
	_Up.rotateVector(matrix);
}

void GameTransform::RotateX(GLfloat Angle)
{
	Vector3 xAxis = Right();
	matrix.setRotation(Angle*DEG_TO_RAD, xAxis[0], xAxis[1], xAxis[2]);

	_Forward.rotateVector(matrix);
	_Up.rotateVector(matrix);
}

void GameTransform::Translate(GLfloat x, GLfloat y, GLfloat z)
{
	getMatrix();
	matrix.TranslateMatrix(x, y, z);

	memcpy(&Location[0], &matrix[12], sizeof(GLfloat)* 3);
}

void GameTransform::Rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
	matrix.setRotation(angle*DEG_TO_RAD, x, y, z);

	_Up.rotateVector(matrix);
	_Forward.rotateVector(matrix);
}

void GameTransform::SetRotation(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
	matrix.setRotation(angle*DEG_TO_RAD, x, y, z);

	memcpy(&_Up[0], &matrix[4], sizeof(GLfloat)* 3);
	memcpy(&_Forward[0], &matrix[8], sizeof(GLfloat)* 3);
}