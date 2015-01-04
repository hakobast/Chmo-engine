
#ifndef OpenGLTesting_AssetManager_h
#define OpenGLTesting_AssetManager_h

#include <vector>
#include <map>
#include <string>

#include "Mesh.h"
#include "Material.h"
#include "GameObject.h"
#include "imageloader.h"
#include "smart_pointer.h"

struct ModelDescriptor
{
	std::string matfile;
	std::vector<std::string> meshNames;
	std::map<std::string, std::string> meshMaterials;
};

std::vector<GameObject*> LoadModel(const char* modelfile, const char* materialfile);
std::vector<smart_pointer<Mesh>> LoadMesh(const char* filename, ModelDescriptor* descriptor = NULL);
std::vector<smart_pointer<Material>> LoadMtl(const char* filename);

void setVertexAttributes(smart_pointer<Mesh>& mesh, int subMesh,
	std::vector<Vector3>& v,
	std::vector<Vector2>& u,
	std::vector<Vector3>& n,
	std::vector<unsigned int>& vIndices,
	std::vector<unsigned int>& uIndices,
	std::vector<unsigned int>& nIndices);
#endif