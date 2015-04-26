#ifndef EngineTesting_TextureAtlas_h
#define EngineTesting_TextureAtlas_h

#include <string>
#include "Texture2D.h"
#include "TextureRegion.h"

class TextureAtlas:public Texture2D
{
public:
	TextureAtlas(const GLvoid*pixels,
		int width, int height,
		int* regions, int textures_count,
		bool generateMipmaps = false,
		GLenum internalFormat = GL_RGB,
		GLenum format = GL_RGBA,
		GLenum dataType = GL_UNSIGNED_BYTE);
	~TextureAtlas();
	const int txt_count;
};
#endif