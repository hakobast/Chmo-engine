
#include <iostream>
#include "TextureTiled.h"

TextureTiled::TextureTiled(const char* filename, int rows, int columns, int tilesCount, bool generateMipmaps)
:Texture2D(filename,generateMipmaps), rows(rows), columns(columns), tiles_count(tilesCount)
{
	textures = new TextureRegion[tilesCount];

	float tile_w = (float)width / columns;
	float tile_h = (float)height / rows;
	float r = 0, c = 0;

	for (int i = 0; i < tilesCount; i++)
	{
		r = i / columns;
		c = i % columns;

/*([6],[7])----------([4],[5])
		   |		|
		   |		|
		   |		|
  ([0],[1])----------([2],[3])*/
		textures[i].u_v[0] = c*tile_w/width; 
		textures[i].u_v[1] = (rows-1-r)*tile_h/height;

		textures[i].u_v[2] = (c+1)*tile_w/width;
		textures[i].u_v[3] = (rows - 1 - r)*tile_h/height;

		textures[i].u_v[4] = (c+1)*tile_w/width;
		textures[i].u_v[5] = (rows-r)*tile_h/height;

		textures[i].u_v[6] = c*tile_w/width;
		textures[i].u_v[7] = (rows - r)*tile_h/height;
	}
}

TextureTiled::~TextureTiled()
{
	std::cout << "TextureTiled: ~~~deleted~~~" << std::endl;
}