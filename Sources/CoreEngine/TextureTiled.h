#ifndef EngineTesting_TextureTiled_h
#define EngineTesting_TextureTiled_h

#include <string>
#include "Texture2D.h"
#include "TextureRegion.h"

class TextureTiled :public Texture2D
{
public:
	//TextureTiled(const char*filename, int rows, int columns, int tilesCount, bool generateMipmaps = false);
	TextureTiled(const GLvoid*pixels,
		int width, int height,
		int rows, int columns, int tilesCount,
		bool generateMipmaps = false,
		GLenum internalFormat = GL_RGB,
		GLenum format = GL_RGBA,
		GLenum dataType = GL_UNSIGNED_BYTE);
	
	~TextureTiled();
	const int tiles_count;
private:
	int rows;
	int columns;
};

#endif