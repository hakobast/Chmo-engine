//
//  Transform.h
//  OpenGLTesting
//
//  Created by Hakob on 11/7/14.
//  Copyright (c) 2014 Haksist. All rights reserved.
//

#ifndef OpenGLTesting_GameTransform_h
#define OpenGLTesting_GameTransform_h

#include "GL_LIBS.h"

#include "Vectors.h"
#include "Matrix4.h"
#include "Component.h"

using namespace std;

class Transform: public Component
{
	friend class GameObject;
private:
	Matrix4 matrix;
	Vector3 _Up;
	Vector3 _Forward;
	Transform() :
		Location(Vector3(0.0f, 0.0f, 0.0f)),
		_Up(Vector3(0.0f, 1.0f, 0.0f)),
		_Forward(Vector3(0.0f,0.0f,1.0f)),
		ScaleLocal(Vector3(1.0f,1.0f,1.0f)){};
protected:
	~Transform();
public:
	Vector3 Location;
	Vector3 ScaleLocal;
	Vector3 Right();
	Vector3 Up();
	Vector3 Forward();
	Matrix4 getMatrix(bool calcScale = false);

	void applyTransformation();
	void Translate(GLfloat x, GLfloat y, GLfloat z);
	void TranslateForward(GLfloat step);
	void TranslateUp(GLfloat step);
	void TranslateRight(GLfloat step);
	void SetRotation(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
	void Rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
	void RotateY(GLfloat Angle);
	void RotateZ(GLfloat Angle);
	void RotateX(GLfloat Angle);
};

inline Vector3 Transform::Right()
{
	return _Up.cross(_Forward);
}

inline Vector3 Transform::Up()
{ 
	return _Up;
}

inline Vector3 Transform::Forward()
{
	return _Forward;
}

#endif