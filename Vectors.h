//
//  Vector3.h
//  OpenGLTesting
//
//  Created by Hakob on 11/7/14.
//  Copyright (c) 2014 Haksist. All rights reserved.
//

#ifndef OpenGLTesting_Vector3_h
#define OpenGLTesting_Vector3_h

#include "Matrix4.h"
#include <GL\glut.h>
#include <iostream>
#include <math.h>

#define GLT_PI	3.14159265358979323846
#define DEG_TO_RAD 0.017453292519943296
#define RAD_TO_DEG 57.2957795130823229

const GLfloat EPSILON = 0.000001f;

struct Vector2
{
	GLfloat x, y;
	Vector2() :x(0.0f), y(0.0f){}
	Vector2(GLfloat x, GLfloat y) :x(x), y(y){}

public:
	void set(GLfloat x, GLfloat y);
	Vector2 duplicate() const;
	GLfloat magnitude() const;
	GLfloat sqrmagnitude() const;
	Vector2& normalize();
	Vector2 normalized() const;
	GLfloat distance(const Vector2& other) const;
	GLfloat dot(const Vector2& other) const;
	Vector2 cross(const Vector2& other) const;
	bool compare(const Vector2& other, GLfloat epsilon) const;

	Vector2 operator +(const Vector2& other);
	Vector2 operator -(const Vector2& other);
	Vector2 operator *(const Vector2& other);
	Vector2 operator *(const GLfloat scale);
	Vector2 operator /(const Vector2& other);
	Vector2 operator /(const GLfloat scale);
	Vector2& operator +=(const Vector2& other);
	Vector2& operator -=(const Vector2& other);
	Vector2& operator *=(const Vector2& other);
	Vector2& operator *=(const GLfloat scale);
	Vector2& operator /=(const Vector2& other);
	Vector2& operator /=(const GLfloat scale);
	GLfloat operator [](int index) const;
	GLfloat& operator [](int index);
	bool operator ==(const Vector2& other) const;
	bool operator !=(const Vector2& other) const;
	friend std::ostream& operator << (std::ostream& stream, const Vector2& v2);

};

inline std::ostream& operator << (std::ostream& stream, const Vector2& v2)
{
	return stream << "V2(" << v2.x << ", " << v2.y << ")";
}

inline void Vector2::set(GLfloat x, GLfloat y)
{
	this->x = x; this->y = y;
}

inline Vector2 Vector2::duplicate() const
{
	return Vector2(x, y);
}

inline GLfloat Vector2::magnitude() const
{
	return sqrtf(x*x + y*y);
}

inline GLfloat Vector2::sqrmagnitude() const
{
	return x*x + y*y;
}

inline GLfloat Vector2::distance(const Vector2& other) const
{
	return sqrtf((other.x - x)*(other.x - x) +
		(other.y - y)*(other.y - y));
}

inline GLfloat Vector2::dot(const Vector2& other) const
{
	return x*other.x + y*other.y;
}

inline Vector2& Vector2::normalize()
{
	GLfloat m = sqrtf(x*x + y*y);
	if (m < EPSILON)
		return *this;

	x /= m;
	y /= m;

	return *this;
}

inline Vector2 Vector2::normalized() const
{
	GLfloat m = sqrtf(x*x + y*y);
	if (m < EPSILON)
		return *this;

	return Vector2(x / m, y / m);
}

inline bool Vector2::compare(const Vector2& other, GLfloat epsilon) const
{
	return fabs(x - other.x) <= epsilon && fabs(y - other.y) <= epsilon;
}

inline GLfloat Vector2:: operator [](int index) const
{
	return (&x)[index];
}

inline GLfloat& Vector2:: operator [](int index)
{
	return (&x)[index];
}

inline Vector2 Vector2:: operator+(const Vector2& other)
{
	return Vector2(x + other.x, y + other.y);
}

inline Vector2 Vector2:: operator-(const Vector2& other)
{
	return Vector2(x - other.x, y - other.y);
}

inline Vector2 Vector2:: operator*(const Vector2& other)
{
	return Vector2(x*other.x, y*other.y);
}

inline Vector2 Vector2:: operator*(const GLfloat scale)
{
	return Vector2(x*scale, y*scale);
}

inline Vector2 Vector2:: operator/(const Vector2& other)
{
	return Vector2(x / other.x, y / other.y);
}

inline Vector2 Vector2:: operator/(const GLfloat scale)
{
	return Vector2(x / scale, y / scale);
}

inline Vector2& Vector2:: operator +=(const Vector2& other)
{
	x += other.x; y += other.y; return *this;
}

inline Vector2& Vector2:: operator -=(const Vector2& other)
{
	x -= other.x; y -= other.y; return *this;
}

inline Vector2& Vector2:: operator *=(const Vector2& other)
{
	x *= other.x; y *= other.y; return *this;
}

inline Vector2& Vector2:: operator /=(const Vector2& other)
{
	x /= other.x; y /= other.y; return *this;
}

inline Vector2& Vector2:: operator *=(const GLfloat scale)
{
	x *= scale; y *= scale; return *this;
}

inline Vector2& Vector2:: operator /=(const GLfloat scale)
{
	x /= scale; y /= scale; return *this;
}

inline bool Vector2:: operator ==(const Vector2& other) const
{
	return fabs(x - other.x) <= EPSILON && fabs(y - other.y) <= EPSILON;
}

inline bool Vector2:: operator !=(const Vector2& other) const
{
	return fabs(x - other.x) > EPSILON && fabs(y - other.y) > EPSILON;
}


struct Vector3
{
    GLfloat x,y,z;
    Vector3():x(0.0f),y(0.0f),z(0.0f){}
    Vector3(GLfloat x, GLfloat y,GLfloat z):x(x),y(y),z(z){}
    
public:
    void set(GLfloat x,GLfloat y,GLfloat z);
    Vector3 duplicate() const;
    GLfloat magnitude() const;
    GLfloat sqrmagnitude() const;
    Vector3& normalize();
    Vector3 normalized() const;
    GLfloat distance(const Vector3& other) const;
    GLfloat dot(const Vector3& other) const;
    Vector3 cross(const Vector3& other) const;
    Vector3& rotateVector(GLfloat angle, GLfloat xAxis, GLfloat yAxis, GLfloat zAxis);
    Vector3& rotateVector(const Matrix4 rotationMatrix);
    bool compare(const Vector3& other, GLfloat epsilon) const;

    Vector3 operator +(const Vector3& other);
    Vector3 operator -(const Vector3& other);
    Vector3 operator *(const Vector3& other);
    Vector3 operator *(const GLfloat scale);
    Vector3 operator /(const Vector3& other);
    Vector3 operator /(const GLfloat scale);
    Vector3& operator +=(const Vector3& other);
    Vector3& operator -=(const Vector3& other);
    Vector3& operator *=(const Vector3& other);
    Vector3& operator *=(const GLfloat scale);
    Vector3& operator /=(const Vector3& other);
    Vector3& operator /=(const GLfloat scale);
    GLfloat operator [](int index) const;
    GLfloat& operator [](int index);
    bool operator ==(const Vector3& other) const;
    bool operator !=(const Vector3& other) const;
	friend std::ostream& operator <<(std::ostream& stream, const Vector3& v3);
};

inline std::ostream& operator <<(std::ostream& stream, const Vector3& v3)
{
	return stream << "V3(" << v3.x << "," << v3.y << "," << v3.z << ")";
}

inline void Vector3::set(GLfloat x, GLfloat y,GLfloat z)
{
    this->x=x;this->y=y;this->z=z;
}

inline Vector3 Vector3:: duplicate() const
{
    return Vector3(x,y,z);
}

inline GLfloat Vector3::magnitude() const
{
    return sqrtf(x*x+y*y+z*z);
}

inline GLfloat Vector3::sqrmagnitude() const
{
    return x*x+y*y+z*z;
}

inline GLfloat Vector3:: distance(const Vector3& other) const
{
    return sqrtf((other.x-x)*(other.x-x)+
                 (other.y-y)*(other.y-y)+
                 (other.z-z)*(other.z-z));
}

inline GLfloat Vector3:: dot(const Vector3& other) const
{
    return x*other.x + y*other.y + z*other.z;
}

inline Vector3 Vector3:: cross(const Vector3& other) const
{
    return Vector3(y*other.z-z*other.y,z*other.x-x*other.z,x*other.y-y*other.x);
}

inline Vector3& Vector3::rotateVector(GLfloat angle, GLfloat xAxis, GLfloat yAxis, GLfloat zAxis)
{
    Matrix4 a = Matrix4();
    a.setRotation(angle*DEG_TO_RAD,xAxis,yAxis,zAxis);
    
    set(x*a[0]+y*a[4]+z*a[8], x*a[1]+y*a[5]+z*a[9], x*a[2]+y*a[6]+z*a[10]);
    return *this;
}

inline Vector3& Vector3::rotateVector(const Matrix4 rotationMatrix)
{
    set(x*rotationMatrix[0]+y*rotationMatrix[4]+z*rotationMatrix[8],
        x*rotationMatrix[1]+y*rotationMatrix[5]+z*rotationMatrix[9],
        x*rotationMatrix[2]+y*rotationMatrix[6]+z*rotationMatrix[10]);
    
    return *this;
}

inline Vector3& Vector3:: normalize()
{
    GLfloat m = sqrtf(x*x+y*y+z*z);
    if(m < EPSILON)
        return *this;
    
    x/=m;
    y/=m;
    z/=m;
    
    return *this;
}

inline Vector3 Vector3:: normalized() const
{
    GLfloat m = sqrtf(x*x+y*y+z*z);
    if(m < EPSILON)
        return *this;
    
    return Vector3(x/m,y/m,z/m);
}

inline bool Vector3:: compare(const Vector3& other, GLfloat epsilon) const
{
    return fabs(x-other.x) <= epsilon && fabs(y-other.y) <= epsilon && fabs(z-other.z) <= epsilon;
}

inline GLfloat Vector3:: operator [](int index) const
{
    return (&x)[index];
}

inline GLfloat& Vector3:: operator [](int index)
{
    return (&x)[index];
}

inline Vector3 Vector3:: operator+(const Vector3& other)
{
    return Vector3(x+other.x,y+other.y,z+other.z);
}

inline Vector3 Vector3:: operator-(const Vector3& other)
{
    return Vector3(x-other.x,y-other.y,z-other.z);
}

inline Vector3 Vector3:: operator*(const Vector3& other)
{
    return Vector3(x*other.x,y*other.y,z*other.z);
}

inline Vector3 Vector3:: operator*(const GLfloat scale)
{
    return Vector3(x*scale,y*scale,z*scale);
}

inline Vector3 Vector3:: operator/(const Vector3& other)
{
    return Vector3(x/other.x,y/other.y,z/other.z);
}

inline Vector3 Vector3:: operator/(const GLfloat scale)
{
    return Vector3(x/scale,y/scale,z/scale);
}

inline Vector3& Vector3:: operator +=(const Vector3& other)
{
    x+=other.x;y+=other.y;z+=other.z;return *this;
}

inline Vector3& Vector3:: operator -=(const Vector3& other)
{
    x-=other.x;y-=other.y;z-=other.z;return *this;
}

inline Vector3& Vector3:: operator *=(const Vector3& other)
{
    x*=other.x;y*=other.y;z*=other.z;return *this;
}

inline Vector3& Vector3:: operator /=(const Vector3& other)
{
    x/=other.x;y/=other.y;z/=other.z;return *this;
}

inline Vector3& Vector3:: operator *=(const GLfloat scale)
{
    x*=scale;y*=scale;z*=scale;return *this;
}

inline Vector3& Vector3:: operator /=(const GLfloat scale)
{
    x/=scale;y/=scale;z/=scale;return *this;
}

inline bool Vector3:: operator ==(const Vector3& other) const
{
    return fabs(x-other.x) <= EPSILON && fabs(y-other.y) <= EPSILON && fabs(z-other.z) <= EPSILON;
}

inline bool Vector3:: operator !=(const Vector3& other) const
{
    return fabs(x-other.x) > EPSILON && fabs(y-other.y) > EPSILON && fabs(z-other.z) > EPSILON;
}

#endif
