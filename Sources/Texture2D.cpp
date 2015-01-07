
#include <iostream>

//TEMP this is temp library for load bmp
//TODO integrate crossplatform image load plugin with multiple format support
#include "imageloader.h"

#include "Texture2D.h"

Texture2D::Texture2D(const char* filename, bool generateMipmaps)
:file_name(filename)
{
	Image* image = loadBMP(filename);
	
	if (image != NULL)
	{
		width = image->width;
		height = image->height;
		
		glGenTextures(1, &texture_id);
		glBindTexture(GL_TEXTURE_2D, texture_id);
		if (generateMipmaps)
		{
			gluBuild2DMipmaps(GL_TEXTURE_2D, 4, image->width, image->height, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
			texture_min_filter = GL_NEAREST_MIPMAP_LINEAR;
			texture_mag_filter = GL_LINEAR_MIPMAP_LINEAR;
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
			texture_min_filter = GL_NEAREST;
			texture_mag_filter = GL_LINEAR;
		}

		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else
		std::cout << "Texture2D: Error occurred while reading file: " << filename << std::endl;

	delete image;
}

Texture2D::Texture2D(const char*filename, int region[], bool generateMipmaps)
:Texture2D(filename,generateMipmaps)
{
	textures = new TextureRegion[1];

	textures[0].u_v[0] = (float)region[0] / width;
	textures[0].u_v[1] = (float)region[1] / height;

	textures[0].u_v[2] = (float)region[2] / width;
	textures[0].u_v[3] = (float)region[1] / height;

	textures[0].u_v[4] = (float)region[2] / width;
	textures[0].u_v[5] = (float)region[3] / height;

	textures[0].u_v[6] = (float)region[0] / width;
	textures[0].u_v[7] = (float)region[3] / height;
}

Texture2D::~Texture2D()
{
	std::cout << "Texture2D ~~~deleted~~~" << std::endl;
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glDeleteTextures(1, &texture_id);
	delete[] textures;
}