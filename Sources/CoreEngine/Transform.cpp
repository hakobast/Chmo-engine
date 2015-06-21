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

void Transform::getMatrix(Matrix4& matrix, bool calcScale)
{
	Vector3 _Right = Right();
	matrix[0] = _Right[0];
	matrix[1] = _Right[1];
	matrix[2] = _Right[2];
	matrix[3] = 0.0f;

	matrix[4] = up_[0];
	matrix[5] = up_[1];
	matrix[6] = up_[2];
	matrix[7] = 0.0f;

	matrix[8] = forward_[0];
	matrix[9] = forward_[1];
	matrix[10] = forward_[2];
	matrix[11] = 0.0f;

	matrix[12] = location_[0];
	matrix[13] = location_[1];
	matrix[14] = location_[2];
	matrix[15] = 1.0f;

	if (calcScale)
	{
		matrix[0] *= scaleLocal_[0];
		matrix[1] *= scaleLocal_[0];
		matrix[2] *= scaleLocal_[0];

		matrix[4] *= scaleLocal_[1];
		matrix[5] *= scaleLocal_[1];
		matrix[6] *= scaleLocal_[1];

		matrix[8] *= scaleLocal_[2];
		matrix[9] *= scaleLocal_[2];
		matrix[10] *= scaleLocal_[2];
	}
}

void Transform::TranslateForward(GLfloat step)
{
	location_[0] += forward_[0] * step;
	location_[1] += forward_[1] * step;
	location_[2] += forward_[2] * step;
}

void Transform::TranslateUp(GLfloat step)
{
	location_[0] += up_[0] * step;
	location_[1] += up_[1] * step;
	location_[2] += up_[2] * step;
}

void Transform::TranslateRight(GLfloat step)
{
	Vector3 R = Right();
	location_[0] += R[0] * step;
	location_[1] += R[1] * step;
	location_[2] += R[2] * step;
}

void Transform::RotateY(GLfloat Angle)
{
	matrix_.setRotation(Angle*DEG_TO_RAD, up_[0], up_[1], up_[2]);
	forward_.rotateVector(matrix_);
}

void Transform::RotateZ(GLfloat Angle)
{
	matrix_.setRotation(Angle*DEG_TO_RAD, forward_[0], forward_[1], forward_[2]);
	up_.rotateVector(matrix_);
}

void Transform::RotateX(GLfloat Angle)
{
	Vector3 xAxis = Right();
	matrix_.setRotation(Angle*DEG_TO_RAD, xAxis[0], xAxis[1], xAxis[2]);

	forward_.rotateVector(matrix_);
	up_.rotateVector(matrix_);
}

void Transform::Translate(GLfloat x, GLfloat y, GLfloat z)
{
	getMatrix(matrix_);
	matrix_.TranslateMatrix(x, y, z);

	memcpy(&location_[0], &matrix_[12], sizeof(GLfloat)* 3);
}

void Transform::Rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
	matrix_.setRotation(angle*DEG_TO_RAD, x, y, z);

	up_.rotateVector(matrix_);
	forward_.rotateVector(matrix_);
}

void Transform::SetRotation(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
	matrix_.setRotation(angle*DEG_TO_RAD, x, y, z);

	memcpy(&up_[0], &matrix_[4], sizeof(GLfloat)* 3);
	memcpy(&forward_[0], &matrix_[8], sizeof(GLfloat)* 3);
}