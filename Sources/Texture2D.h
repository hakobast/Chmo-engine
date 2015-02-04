#ifndef EngineTesting_Texture2D_h
#define EngineTesting_Texture2D_h

#include <string>
#include <map>

#include "GL_LIBS.h"

#include "smart_pointer.h"
#include "TextureRegion.h"

class Texture2D:public RemovableObject
{
private:
	bool pixelsSet = false;
protected:
	TextureRegion* textures;
	GLuint texture_id;
	int frameCount = 1;
public:
	const int width;
	const int height;
	const bool generateMipmaps;
	const GLenum internalFormat;
	const GLenum format;
	const GLenum dataType;

	GLenum texture_min_filter;
	GLenum texture_mag_filter;
	GLenum texture_wrap_s = GL_REPEAT;
	GLenum texture_wrap_t = GL_REPEAT;

	//TODO add image format parameter
	Texture2D(int width, int height, 
		bool generateMipmaps = false,
		GLenum internalFormat = GL_RGB,
		GLenum format = GL_BGR_EXT,
		GLenum dataType = GL_UNSIGNED_BYTE );

	Texture2D(const GLvoid*pixels,
		int width, int height,
		bool generateMipmaps = false,
		GLenum internalFormat = GL_RGB,
		GLenum format = GL_BGR_EXT,
		GLenum dataType = GL_UNSIGNED_BYTE);

	Texture2D(const GLvoid*pixels,
		int region[],
		int width, int height,
		bool generateMipmaps = false,
		GLenum internalFormat = GL_RGB,
		GLenum format = GL_BGR_EXT,
		GLenum dataType = GL_UNSIGNED_BYTE);

//	Texture2D(const char*filename, bool generateMipmaps = false);

	virtual ~Texture2D();
	int getFrameCount();
	void setPixels(const GLvoid * pixels);
	char* getPixels();
	char* getPixels(GLint x, GLint y, GLint _width, GLint _height);
	void bindTexture();
	void unbindTexture();
	TextureRegion&const getTextureRegion(int index = 0);
	TextureRegion&const operator [](int index);
};

inline void Texture2D::bindTexture()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,texture_min_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture_mag_filter);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture_wrap_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture_wrap_t);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, texture_id);
}

inline void Texture2D::unbindTexture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

inline int Texture2D::getFrameCount()
{
	return frameCount;
}

inline TextureRegion&const Texture2D::getTextureRegion(int index)
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

inline TextureRegion&const Texture2D::operator [](int index)
{
	return getTextureRegion(index);
}

#endif