#ifndef EngineTesting_TextureAtlas_h
#define EngineTesting_TextureAtlas_h

#include <string>
#include "Texture2D.h"
#include "TextureRegion.h"

class TextureAtlas:public Texture2D
{
public:
	TextureAtlas(const char*filename, int regions[],int textures_count);
	~TextureAtlas();
	const int txt_count;
};
#endif