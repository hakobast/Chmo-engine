
#include <iostream>

#include "TextureAtlas.h"

/*
regions: 
u1,v1,
u2,v2,
u3,v3,
u4,v4
Un,Vn
*/

TextureAtlas::TextureAtlas(const GLvoid*pixels,
	int width, int height,
	int* regions, int textures_count,
	bool generateMipmaps,
	GLenum internalFormat,
	GLenum format,
	GLenum dataType)
	:Texture2D(pixels, width, height, generateMipmaps, internalFormat, format, dataType), txt_count(textures_count)
{
	frameCount = textures_count;
	textures = new TextureRegion[textures_count];

	float x1 = 0.0f, x2 = 0.0f,y1 = 0.0f,y2 = 0.0f;
	for (int r = 0; r < textures_count; r++)
	{
		x1 = (float)regions[r*4 + 0] / width;
		y1 = (float)regions[r*4 + 1] / height;
		x2 = (float)regions[r*4 + 2] / width;
		y2 = (float)regions[r*4 + 3] / height;

/*([6],[7])----------([4],[5])
		   |		|
		   |		|
		   |		|
 ([0],[1]) ----------([2],[3])*/
		textures[r].u_v[0] = x1;
		textures[r].u_v[1] = y1;

		textures[r].u_v[2] = x2;
		textures[r].u_v[3] = y1;

		textures[r].u_v[4] = x2;
		textures[r].u_v[5] = y2;

		textures[r].u_v[6] = x1;
		textures[r].u_v[7] = y2;
	}
}

TextureAtlas::~TextureAtlas()
{
	std::cout << "TextureAtlas ~~~deleted~~~" << std::endl;
}