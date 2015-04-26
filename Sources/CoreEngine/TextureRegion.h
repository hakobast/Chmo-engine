#ifndef EngineTesting_TextureRegion_h
#define EngineTesting_TextureRegion_h

#include <iostream>
#include <stdio.h>

struct TextureRegion
{
public:
	TextureRegion(){};
	TextureRegion(const GLfloat* uv)
	{
		memcpy(u_v, uv, sizeof(GLfloat)* 8);
	}
	//float operator [](int index) const;
	GLfloat* operator [](int index);
	GLfloat u_v[8];
};

//inline float TextureRegion::operator[](int index)const
//{
//	return u_v[index];
//}

inline GLfloat* TextureRegion::operator[](int index)
{
	return &u_v[index];
}
#endif