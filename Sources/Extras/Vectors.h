
#ifndef OpenGLTesting_Vector3_h
#define OpenGLTesting_Vector3_h

#include "Matrix4.h"
#include <iostream>
#include <math.h>

#define GLT_PI	3.14159265358979323846f
#define DEG_TO_RAD 0.017453292519943296f
#define RAD_TO_DEG 57.2957795130823229f

const float EPSILON = 0.000001f;

struct Vector2
{
	float x, y;
	Vector2() :x(0.0f), y(0.0f){}
	Vector2(float x, float y) :x(x), y(y){}

public:
	static const Vector2 ZERO;
	static const Vector2 ONE;
	static const Vector2 RIGHT;
	static const Vector2 UP;

	void set(float x, float y);
	void set(GLint x, GLint y);
	Vector2 duplicate() const;
	float magnitude() const;
	float sqrmagnitude() const;
	Vector2& normalize();
	Vector2 normalized() const;
	float distance(const Vector2& other) const;
	float dot(const Vector2& other) const;
	Vector2 cross(const Vector2& other) const;
	bool compare(const Vector2& other, float epsilon) const;
	float* getPointer();

	Vector2 operator +(const Vector2& other);
	Vector2 operator -(const Vector2& other);
	Vector2 operator *(const Vector2& other);
	Vector2 operator *(const float scale);
	Vector2 operator /(const Vector2& other);
	Vector2 operator /(const float scale);
	Vector2& operator +=(const Vector2& other);
	Vector2& operator -=(const Vector2& other);
	Vector2& operator *=(const Vector2& other);
	Vector2& operator *=(const float scale);
	Vector2& operator /=(const Vector2& other);
	Vector2& operator /=(const float scale);
	float operator [](int index) const;
	float& operator [](int index);
	bool operator ==(const Vector2& other) const;
	bool operator !=(const Vector2& other) const;
	friend std::ostream& operator << (std::ostream& stream, const Vector2& v2);

};

inline std::ostream& operator << (std::ostream& stream, const Vector2& v2)
{
	return stream << "V2(" << v2.x << ", " << v2.y << ")";
}

inline void Vector2::set(float x, float y)
{
	this->x = x; this->y = y;
}

inline void Vector2::set(GLint x, GLint y)
{
	this->x = (float)x; this->y = (float)y;
}

inline Vector2 Vector2::duplicate() const
{
	return Vector2(x, y);
}

inline float Vector2::magnitude() const
{
	return sqrtf(x*x + y*y);
}

inline float Vector2::sqrmagnitude() const
{
	return x*x + y*y;
}

inline float Vector2::distance(const Vector2& other) const
{
	return sqrtf((other.x - x)*(other.x - x) +
		(other.y - y)*(other.y - y));
}

inline float Vector2::dot(const Vector2& other) const
{
	return x*other.x + y*other.y;
}

inline Vector2& Vector2::normalize()
{
	float m = sqrtf(x*x + y*y);
	if (m < EPSILON)
		return *this;

	x /= m;
	y /= m;

	return *this;
}

inline Vector2 Vector2::normalized() const
{
	float m = sqrtf(x*x + y*y);
	if (m < EPSILON)
		return *this;

	return Vector2(x / m, y / m);
}

inline float* Vector2::getPointer()
{
	return (&x);
}

inline bool Vector2::compare(const Vector2& other, float epsilon) const
{
	return fabs(x - other.x) <= epsilon && fabs(y - other.y) <= epsilon;
}

inline float Vector2:: operator [](int index) const
{
	return (&x)[index];
}

inline float& Vector2:: operator [](int index)
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

inline Vector2 Vector2:: operator*(const float scale)
{
	return Vector2(x*scale, y*scale);
}

inline Vector2 Vector2:: operator/(const Vector2& other)
{
	return Vector2(x / other.x, y / other.y);
}

inline Vector2 Vector2:: operator/(const float scale)
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

inline Vector2& Vector2:: operator *=(const float scale)
{
	x *= scale; y *= scale; return *this;
}

inline Vector2& Vector2:: operator /=(const float scale)
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
    float x,y,z;
    Vector3():x(0.0f),y(0.0f),z(0.0f){}
    Vector3(float x, float y,float z):x(x),y(y),z(z){}
    
public:
	static const Vector3 ZERO;
	static const Vector3 ONE;
	static const Vector3 RIGHT;
	static const Vector3 UP;
	static const Vector3 FORWARD;

    void set(float x,float y,float z);
    Vector3 duplicate() const;
    float magnitude() const;
    float sqrmagnitude() const;
    Vector3& normalize();
    Vector3 normalized() const;
    float distance(const Vector3& other) const;
    float dot(const Vector3& other) const;
    Vector3 cross(const Vector3& other) const;
    Vector3& rotateVector(float angle, float xAxis, float yAxis, float zAxis);
    Vector3& rotateVector(const Matrix4 rotationMatrix);
    bool compare(const Vector3& other, float epsilon) const;
	float* getPointer();

    Vector3 operator +(const Vector3& other);
    Vector3 operator -(const Vector3& other);
    Vector3 operator *(const Vector3& other);
    Vector3 operator *(const float scale);
    Vector3 operator /(const Vector3& other);
    Vector3 operator /(const float scale);
    Vector3& operator +=(const Vector3& other);
    Vector3& operator -=(const Vector3& other);
    Vector3& operator *=(const Vector3& other);
    Vector3& operator *=(const float scale);
    Vector3& operator /=(const Vector3& other);
    Vector3& operator /=(const float scale);
    float operator [](int index) const;
    float& operator [](int index);
    bool operator ==(const Vector3& other) const;
    bool operator !=(const Vector3& other) const;
	friend std::ostream& operator <<(std::ostream& stream, const Vector3& v3);
};

inline std::ostream& operator <<(std::ostream& stream, const Vector3& v3)
{
	return stream << "V3(" << v3.x << "," << v3.y << "," << v3.z << ")";
}

inline void Vector3::set(float x, float y,float z)
{
    this->x=x;this->y=y;this->z=z;
}

inline Vector3 Vector3:: duplicate() const
{
    return Vector3(x,y,z);
}

inline float Vector3::magnitude() const
{
    return sqrtf(x*x+y*y+z*z);
}

inline float Vector3::sqrmagnitude() const
{
    return x*x+y*y+z*z;
}

inline float Vector3:: distance(const Vector3& other) const
{
    return sqrtf((other.x-x)*(other.x-x)+
                 (other.y-y)*(other.y-y)+
                 (other.z-z)*(other.z-z));
}

inline float Vector3:: dot(const Vector3& other) const
{
    return x*other.x + y*other.y + z*other.z;
}

inline Vector3 Vector3:: cross(const Vector3& other) const
{
    return Vector3(y*other.z-z*other.y,z*other.x-x*other.z,x*other.y-y*other.x);
}

inline Vector3& Vector3::rotateVector(float angle, float xAxis, float yAxis, float zAxis)
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

inline Vector3& Vector3::normalize()
{
    float m = sqrtf(x*x+y*y+z*z);
    if(m < EPSILON)
        return *this;
    
    x/=m;
    y/=m;
    z/=m;
    
    return *this;
}

inline Vector3 Vector3:: normalized() const
{
    float m = sqrtf(x*x+y*y+z*z);
    if(m < EPSILON)
        return *this;
    
    return Vector3(x/m,y/m,z/m);
}

inline float* Vector3::getPointer()
{
	return (&x);
}

inline bool Vector3:: compare(const Vector3& other, float epsilon) const
{
    return fabs(x-other.x) <= epsilon && fabs(y-other.y) <= epsilon && fabs(z-other.z) <= epsilon;
}

inline float Vector3:: operator [](int index) const
{
    return (&x)[index];
}

inline float& Vector3:: operator [](int index)
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

inline Vector3 Vector3:: operator*(const float scale)
{
    return Vector3(x*scale,y*scale,z*scale);
}

inline Vector3 Vector3:: operator/(const Vector3& other)
{
    return Vector3(x/other.x,y/other.y,z/other.z);
}

inline Vector3 Vector3:: operator/(const float scale)
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

inline Vector3& Vector3:: operator *=(const float scale)
{
    x*=scale;y*=scale;z*=scale;return *this;
}

inline Vector3& Vector3:: operator /=(const float scale)
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

#pragma region VECTOR_4

struct Vector4
{
	float x, y, z, w;
	Vector4() :x(0.0f), y(0.0f), z(0.0f) , w(0.0f){}
	Vector4(float x, float y, float z, float w) :x(x), y(y), z(z), w(w){}

public:
	void set(float x, float y, float z, float w);
	Vector4 duplicate() const;
	float magnitude() const;
	float sqrmagnitude() const;
	Vector4& normalize();
	Vector4 normalized() const;
	float distance(const Vector4& other) const;
	float dot(const Vector4& other) const;
	bool compare(const Vector4& other, float epsilon) const;
	float* getPointer();

	Vector4 operator +(const Vector4& other);
	Vector4 operator -(const Vector4& other);
	Vector4 operator *(const Vector4& other);
	Vector4 operator *(const float scale);
	Vector4 operator /(const Vector4& other);
	Vector4 operator /(const float scale);
	Vector4& operator +=(const Vector4& other);
	Vector4& operator -=(const Vector4& other);
	Vector4& operator *=(const Vector4& other);
	Vector4& operator *=(const float scale);
	Vector4& operator /=(const Vector4& other);
	Vector4& operator /=(const float scale);
	float operator [](int index) const;
	float& operator [](int index);
	bool operator ==(const Vector4& other) const;
	bool operator !=(const Vector4& other) const;
	friend std::ostream& operator <<(std::ostream& stream, const Vector4& v3);
};

inline std::ostream& operator <<(std::ostream& stream, const Vector4& v4)
{
	return stream << "V4(" << v4.x << "," << v4.y << "," << v4.z  << "," << v4.w << ")";
}

inline void Vector4::set(float x, float y, float z, float w)
{
	this->x = x; this->y = y; this->z = z; this->w = w;
}

inline Vector4 Vector4::duplicate() const
{
	return Vector4(x, y, z, w);
}

inline float Vector4::magnitude() const
{
	return sqrtf(x*x + y*y + z*z + w*w);
}

inline float Vector4::sqrmagnitude() const
{
	return x*x + y*y + z*z + w*w;
}

inline Vector4& Vector4::normalize()
{
	float m = sqrtf(x*x + y*y + z*z + w*w);
	if (m < EPSILON)
		return *this;

	x /= m;
	y /= m;
	z /= m;
	w /= m;

	return *this;
}

inline Vector4 Vector4::normalized() const
{
	float m = sqrtf(x*x + y*y + z*z + w*w);
	if (m < EPSILON)
		return *this;

	return Vector4(x / m, y / m, z / m, w/m);
}

inline float Vector4::distance(const Vector4& other) const
{
	return sqrtf((other.x - x)*(other.x - x) +
		(other.y - y)*(other.y - y) +
		(other.z - z)*(other.z - z) + 
		(other.w-w)*(other.w-w));
}

inline float Vector4::dot(const Vector4& other) const
{
	return x*other.x + y*other.y + z*other.z + w*other.w;
}

inline float* Vector4::getPointer()
{
	return (&x);
}

inline bool Vector4::compare(const Vector4& other, float epsilon) const
{
	return fabs(x - other.x) <= epsilon && fabs(y - other.y) <= epsilon && fabs(z - other.z) <= epsilon && fabs(w - other.w) <= epsilon;
}

inline float Vector4:: operator [](int index) const
{
	return (&x)[index];
}

inline float& Vector4:: operator [](int index)
{
	return (&x)[index];
}

inline Vector4 Vector4:: operator+(const Vector4& other)
{
	return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
}

inline Vector4 Vector4:: operator-(const Vector4& other)
{
	return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
}

inline Vector4 Vector4:: operator*(const Vector4& other)
{
	return Vector4(x*other.x, y*other.y, z*other.z, w*other.w);
}

inline Vector4 Vector4:: operator*(const float scale)
{
	return Vector4(x*scale, y*scale, z*scale, w*scale);
}

inline Vector4 Vector4:: operator/(const Vector4& other)
{
	return Vector4(x / other.x, y / other.y, z / other.z, w / other.w);
}

inline Vector4 Vector4:: operator/(const float scale)
{
	return Vector4(x / scale, y / scale, z / scale, w / scale);
}

inline Vector4& Vector4:: operator +=(const Vector4& other)
{
	x += other.x; y += other.y; z += other.z; return *this;
}

inline Vector4& Vector4:: operator -=(const Vector4& other)
{
	x -= other.x; y -= other.y; z -= other.z; return *this;
}

inline Vector4& Vector4:: operator *=(const Vector4& other)
{
	x *= other.x; y *= other.y; z *= other.z; return *this;
}

inline Vector4& Vector4:: operator /=(const Vector4& other)
{
	x /= other.x; y /= other.y; z /= other.z; return *this;
}

inline Vector4& Vector4:: operator *=(const float scale)
{
	x *= scale; y *= scale; z *= scale; return *this;
}

inline Vector4& Vector4:: operator /=(const float scale)
{
	x /= scale; y /= scale; z /= scale; return *this;
}

inline bool Vector4:: operator ==(const Vector4& other) const
{
	return fabs(x - other.x) <= EPSILON && fabs(y - other.y) <= EPSILON && fabs(z - other.z) <= EPSILON;
}

inline bool Vector4:: operator !=(const Vector4& other) const
{
	return fabs(x - other.x) > EPSILON && fabs(y - other.y) > EPSILON && fabs(z - other.z) > EPSILON;
}

#pragma endregion VECTOR_4


#endif
