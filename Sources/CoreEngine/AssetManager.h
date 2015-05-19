
#ifndef OpenGLTesting_AssetManager_h
#define OpenGLTesting_AssetManager_h

#include <vector>
#include <map>
#include <string>

#include "Mesh.h"
#include "Material.h"
#include "GameObject.h"
#include "Texture2D.h"
#include "TextureAtlas.h"
#include "TextureTiled.h"
#include "../Extras/smart_pointer.h"

struct ModelDescriptor
{
	std::string matfile;
	std::vector<std::string> meshNames;
	std::map<std::string, std::string> meshMaterials;
};

class AssetManager
{
public:
	static void Initialize();
	static void Deinitialize();
};

std::vector<GameObject*> LoadModel(const char* modelfile, const char* materialfile);
std::vector<smart_pointer<Mesh>> LoadMesh(const char* filename, ModelDescriptor* descriptor = NULL);
std::vector<smart_pointer<Material>> LoadMtl(const char* filename);

smart_pointer<Texture2D> LoadTexture(const char* filename,
									bool generateMipmaps = false,
									bool custom = false,
									GLenum internalFormat = GL_RGB,
									GLenum format = GL_RGB,
									GLenum dataType = GL_UNSIGNED_BYTE);

smart_pointer<Texture2D> LoadTextureAtlas(const char* filename,
											int* regions, int textures_count,
											bool generateMipmaps = false,
											bool custom = false,
											GLenum internalFormat = GL_RGB,
											GLenum format = GL_RGB,
											GLenum dataType = GL_UNSIGNED_BYTE);

smart_pointer<Texture2D> LoadTextureTiled(const char* filename,
											int rows, int columns, int tilesCount,
											bool generateMipmaps = false,
											bool custom = false,
											GLenum internalFormat = GL_RGB,
											GLenum format = GL_RGB,
											GLenum dataType = GL_UNSIGNED_BYTE);

#endif