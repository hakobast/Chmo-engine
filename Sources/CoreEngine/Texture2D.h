#ifndef EngineTesting_Texture2D_h
#define EngineTesting_Texture2D_h

#include <string>
#include <map>

#include "LIBS.h"
#include "../Extras/smart_pointer.h"
#include "TextureRegion.h"

//TODO implement anisotrop filtering for all platforms
//TODO implement pixel reading functionality for all platforms
class Texture2D : public RemovableObject
{
private:
	bool pixelsSet = false;
	GLenum texture_min_filter;
	GLenum texture_mag_filter;
	GLenum texture_wrap_s = GL_REPEAT;
	GLenum texture_wrap_t = GL_REPEAT;
	GLfloat anisotroplevel = 1.0f;

protected:
	TextureRegion* textures = NULL;
	GLuint texture_id;
	int frameCount = 1;
public:
	const int width;
	const int height;
	const bool generateMipmaps;
	const GLenum internalFormat;
	const GLenum format;
	const GLenum dataType;

	Texture2D(int width, int height, 
		bool generateMipmaps = false,
		GLenum internalFormat = GL_RGB,
		GLenum format = GL_RGB,
		GLenum dataType = GL_UNSIGNED_BYTE );

	Texture2D(const GLvoid*pixels,
		int width, int height,
		bool generateMipmaps = false,
		GLenum internalFormat = GL_RGB,
		GLenum format = GL_RGB,
		GLenum dataType = GL_UNSIGNED_BYTE);

	Texture2D(const GLvoid*pixels,
		int region[],
		int width, int height,
		bool generateMipmaps = false,
		GLenum internalFormat = GL_RGB,
		GLenum format = GL_RGB,
		GLenum dataType = GL_UNSIGNED_BYTE);

	virtual ~Texture2D();
	int getFrameCount();
	void setPixels(const GLvoid * pixels);
	char* getPixels();
	char* getPixels(GLint x, GLint y, GLint _width, GLint _height);
	void bindTexture();
	void unbindTexture();
	void setFilterMode(GLenum minFilter, GLenum magFilter);
	void setWrapmode(GLenum wrap_s, GLenum wrap_t);
	void setAnisoFiltering(bool enabled);

	TextureRegion*const getTextureRegion(int index = 0);
};

inline void Texture2D::bindTexture()
{
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

inline TextureRegion*const Texture2D::getTextureRegion(int index)
{
	if (index >= frameCount)
		return NULL;

	if (textures == NULL)
	{
		textures = new TextureRegion[1];
		textures->uv[0] = 0.0f;
		textures->uv[1] = 0.0f;

		textures->uv[2] = 1.0f;
		textures->uv[3] = 0.0f;

		textures->uv[4] = 1.0f;
		textures->uv[5] = 1.0f;

		textures->uv[6] = 0.0f;
		textures->uv[7] = 1.0f;
	}

	return &textures[index];
}
#endif