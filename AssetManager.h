
#ifndef OpenGLTesting_AssetManager_h
#define OpenGLTesting_AssetManager_h

#include <vector>

#include "Mesh.h"
#include "Material.h"
#include "imageloader.h"

void LoadObj(const char* filename, Mesh* mesh);
std::vector<Material*> LoadMtl(const char* filename);

#endif