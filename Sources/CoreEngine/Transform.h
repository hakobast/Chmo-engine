
#ifndef OpenGLTesting_GameTransform_h
#define OpenGLTesting_GameTransform_h

#include "LIBS.h"

#include "../Extras/Vectors.h"
#include "../Extras/Matrix4.h"
#include "Component.h"

using namespace std;

class Transform: public Component
{
	friend class GameObject;
private:
	Matrix4 matrix_;
	Vector3 location_;
	Vector3 scaleLocal_;
	Vector3 up_;
	Vector3 forward_;
	Transform() :
		location_(Vector3(0.0f, 0.0f, 0.0f)),
		up_(Vector3(0.0f, 1.0f, 0.0f)),
		forward_(Vector3(0.0f,0.0f,1.0f)),
		scaleLocal_(Vector3(1.0f,1.0f,1.0f)){};
protected:
	~Transform();
public:
	void getPosition(Vector3& v) const;
	Vector3 getPosition() const;
	void setPosition(Vector3 newPos);
	void getScale(Vector3& v) const;
	Vector3 getScale() const;
	void setScale(Vector3 newScale);
	Vector3 Right() const;
	Vector3 Up() const;
	Vector3 Forward() const;
	void getMatrix(Matrix4& matrix, bool calcScale = false);

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

inline Vector3 Transform::getPosition() const
{
	return location_;
}

inline void Transform::getPosition(Vector3& v) const
{
	v.x = location_.x;
	v.y = location_.y;
	v.z = location_.z;
}

inline void Transform::setPosition(Vector3 newPos)
{
	location_ = newPos;
}

inline void Transform::getScale(Vector3& v) const
{
	v.x = scaleLocal_.x;
	v.y = scaleLocal_.y;
	v.z = scaleLocal_.z;
}

inline Vector3 Transform::getScale() const
{
	return scaleLocal_;
}

inline void Transform::setScale(Vector3 newScale)
{
	scaleLocal_ = newScale;
}

inline Vector3 Transform::Right() const
{
	return up_.cross(forward_);
}

inline Vector3 Transform::Up() const
{ 
	return up_;
}

inline Vector3 Transform::Forward() const
{
	return forward_;
}

#endif