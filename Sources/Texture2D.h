#ifndef EngineTesting_Texture2D_h
#define EngineTesting_Texture2D_h

#include <GL\glut.h>
#include <string>
#include <map>

#include "smart_pointer.h"
#include "TextureRegion.h"

class Texture2D:public RemovableObject
{
protected:
	TextureRegion* textures;
public:
	GLuint texture_id;
	std::string file_name;
	int width;
	int height;
	GLenum texture_min_filter;
	GLenum texture_mag_filter;
	GLenum texture_wrap_s = GL_REPEAT;
	GLenum texture_wrap_t = GL_REPEAT;

	Texture2D(const char*filename, bool generateMipmaps = false);
	Texture2D(const char*filename, int region[], bool generateMipmaps = false);
	virtual ~Texture2D();
	void bindTexture();
	void unbindTexture();
	TextureRegion& getTextureRegion(int index = 0);
	TextureRegion& operator [](int index);
};

inline void Texture2D::bindTexture()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,texture_min_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture_mag_filter);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture_wrap_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture_wrap_t);

	glBindTexture(GL_TEXTURE_2D, texture_id);
}

inline void Texture2D::unbindTexture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

inline TextureRegion& Texture2D::getTextureRegion(int index)
{
	if (textures == NULL)
	{
		textures = new TextureRegion;
		textures->u_v[0] = 0.0f;
		textures->u_v[1] = 0.0f;

		textures->u_v[2] = 1.0f;
		textures->u_v[3] = 0.0f;

		textures->u_v[4] = 1.0f;
		textures->u_v[5] = 1.0f;

		textures->u_v[6] = 0.0f;
		textures->u_v[7] = 1.0f;
	}

	return textures[index];
}

inline TextureRegion& Texture2D::operator [](int index)
{
	return getTextureRegion(index);
}

#endif