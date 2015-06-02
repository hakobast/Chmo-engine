
#include <iostream>

#include "../Extras/GLUtils.h"
#include "Texture2D.h"

Texture2D::Texture2D(int width, int height,
	bool generateMipmaps,
	GLenum internalFormat,
	GLenum format,
	GLenum dataType)
	:width(width), height(height), generateMipmaps(generateMipmaps), internalFormat(internalFormat), format(format), dataType(dataType)
{
	glGenTextures(1, &texture_id);
	//glBindTexture(GL_TEXTURE_2D, texture_id);
	if (generateMipmaps)
	{
		//gluBuild2DMipmaps(GL_TEXTURE_2D, 4, this->width, this->height, GL_RGB, GL_UNSIGNED_BYTE, pixels);
		texture_min_filter = GL_NEAREST_MIPMAP_LINEAR;
		texture_mag_filter = GL_LINEAR_MIPMAP_LINEAR;
	}
	else
	{
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
		texture_min_filter = GL_NEAREST;
		texture_mag_filter = GL_LINEAR;
	}

	glBindTexture(GL_TEXTURE_2D, texture_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture_min_filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture_mag_filter);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture_wrap_s);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture_wrap_t);

	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture2D::Texture2D(const GLvoid* pixels,
	int width, int height,
	bool generateMipmaps,
	GLenum internalFormat,
	GLenum format,
	GLenum dataType)
:Texture2D(width, height, generateMipmaps, internalFormat, format, dataType)
{
	setPixels(pixels);
}

Texture2D::Texture2D(const GLvoid* pixels,
	int region[],
	int width, int height,
	bool generateMipmaps,
	GLenum internalFormat,
	GLenum format,
	GLenum dataType)
	:Texture2D(width, height, generateMipmaps, internalFormat, format, dataType)
{
	setPixels(pixels);

	textures = new TextureRegion[1];

	textures[0].uv[0] = (float)region[0] / width;
	textures[0].uv[1] = (float)region[1] / height;

	textures[0].uv[2] = (float)region[2] / width;
	textures[0].uv[3] = (float)region[1] / height;

	textures[0].uv[4] = (float)region[2] / width;
	textures[0].uv[5] = (float)region[3] / height;

	textures[0].uv[6] = (float)region[0] / width;
	textures[0].uv[7] = (float)region[3] / height;
}

Texture2D::~Texture2D()
{
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glDeleteTextures(1, &texture_id);
	delete[] textures;
}

void Texture2D::setPixels(const GLvoid* pixels)
{
	glBindTexture(GL_TEXTURE_2D, texture_id);
	if (pixelsSet)
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, this->width, this->height, format, dataType, pixels);
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, this->width, this->height, 0, format, dataType, pixels);
		pixelsSet = true;
	}

	if (generateMipmaps)
	{
		//gluBuild2DMipmaps(GL_TEXTURE_2D, 4, this->width, this->height, format, dataType, pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
}

char* Texture2D::getPixels(GLint x, GLint y, GLint _width, GLint _height)
{
	return NULL;
}

char* Texture2D::getPixels()
{
	return getPixels(0, 0, width, height);
}

inline void Texture2D::setFilterMode(GLenum minFilter, GLenum magFilter)
{
	texture_min_filter = minFilter;
	texture_mag_filter = magFilter;

	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture_min_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture_mag_filter);
	glBindTexture(GL_TEXTURE_2D, 0);
}

inline void Texture2D::setWrapmode(GLenum wrap_s, GLenum wrap_t)
{
	texture_wrap_s = wrap_s;
	texture_wrap_t = wrap_t;

	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture_wrap_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture_wrap_t);
	glBindTexture(GL_TEXTURE_2D, 0);
}

inline void Texture2D::setAnisoFiltering(bool enable)
{
	if (isExtensionSupported("GL_EXT_texture_filter_anisotropic"))
	{
		glBindTexture(GL_TEXTURE_2D, texture_id);
#if defined(_WIN32) || defined (__APPLE__)
		if (enable)
		{
			GLfloat max;
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, max);
		}
		else
		{
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1.0f);
		}
#endif
	}
}