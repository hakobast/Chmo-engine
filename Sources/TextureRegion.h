#ifndef EngineTesting_TextureRegion_h
#define EngineTesting_TextureRegion_h

#include <iostream>
struct TextureRegion
{
public:
	TextureRegion(){};
	TextureRegion(const float* uv)
	{
		std::memcpy(u_v, uv, sizeof(float)* 8);
	}
	//float operator [](int index) const;
	float* operator [](int index);
	float u_v[8];
};

//inline float TextureRegion::operator[](int index)const
//{
//	return u_v[index];
//}

inline float* TextureRegion::operator[](int index)
{
	return &u_v[index];
}
#endif