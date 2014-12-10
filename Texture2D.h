#ifndef EngineTesting_Texture2D_h
#define EngineTesting_Texture2D_h

#include <GL\glut.h>
#include <string>

#include "smart_pointer.h"
#include "TextureRegion.h"

class Texture2D:public RemovableObject
{
public:
	GLuint texture_id;
	std::string file_name;
	int width;
	int height;
	TextureRegion* textures;

	Texture2D(const char*filename);
	Texture2D(const char*filename,int region[]);
	virtual ~Texture2D();
	void bindTexture();
	TextureRegion& operator [](int index);
};

inline void Texture2D::bindTexture()
{
	glBindTexture(GL_TEXTURE_2D, texture_id);
}

inline TextureRegion& Texture2D::operator [](int index)
{
	return textures[index];
}

#endif