
#ifndef OpenGLTesting_AssetManager_h
#define OpenGLTesting_AssetManager_h

#include <vector>
#include <map>
#include <string>

#include "FreeImage.h"

#include "Mesh.h"
#include "Material.h"
#include "GameObject.h"
#include "smart_pointer.h"
#include "Texture2D.h"
#include "TextureAtlas.h"
#include "TextureTiled.h"

struct ModelDescriptor
{
	std::string matfile;
	std::vector<std::string> meshNames;
	std::map<std::string, std::string> meshMaterials;
};

struct TXT_DATA
{
	unsigned int width = 0;
	unsigned int height = 0;
	FREE_IMAGE_FORMAT imgFormat = FIF_UNKNOWN;
	BYTE* data = NULL;
};

std::vector<GameObject*> LoadModel(const char* modelfile, const char* materialfile);
std::vector<smart_pointer<Mesh>> LoadMesh(const char* filename, ModelDescriptor* descriptor = NULL);
std::vector<smart_pointer<Material>> LoadMtl(const char* filename);

smart_pointer<Texture2D> LoadTexture(const char* filename,
									bool generateMipmaps = false,
									bool custom = false,
									GLenum internalFormat = GL_RGB,
									GLenum format = GL_BGR_EXT,
									GLenum dataType = GL_UNSIGNED_BYTE);

smart_pointer<Texture2D> LoadTextureAtlas(const char* filename,
											int* regions, int textures_count,
											bool generateMipmaps = false,
											bool custom = false,
											GLenum internalFormat = GL_RGB,
											GLenum format = GL_BGR_EXT,
											GLenum dataType = GL_UNSIGNED_BYTE);

smart_pointer<Texture2D> LoadTextureTiled(const char* filename,
											int rows, int columns, int tilesCount,
											bool generateMipmaps = false,
											bool custom = false,
											GLenum internalFormat = GL_RGB,
											GLenum format = GL_BGR_EXT,
											GLenum dataType = GL_UNSIGNED_BYTE);

void LoadTextureData(const char* filename, FIBITMAP* fibitmap, FREE_IMAGE_FORMAT* format);

void setVertexAttributes(smart_pointer<Mesh>& mesh, int subMesh,
	std::vector<Vector3>& v,
	std::vector<Vector2>& u,
	std::vector<Vector3>& n,
	std::vector<unsigned int>& vIndices,
	std::vector<unsigned int>& uIndices,
	std::vector<unsigned int>& nIndices);
#endif