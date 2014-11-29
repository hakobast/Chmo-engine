#ifndef EngineTesting_TextureTiled_h
#define EngineTesting_TextureTiled_h

#include <string>
#include "Texture2D.h"
#include "TextureRegion.h"

class TextureTiled :public Texture2D
{
public:
	TextureTiled(const char*filename, int rows,int columns, int tilesCount);
	~TextureTiled();
	const int tiles_count;
private:
	int rows;
	int columns;
};

#endif