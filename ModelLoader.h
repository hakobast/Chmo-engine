#ifndef EngineTesting_ModelLoader_h
#define EngineTesting_ModelLoader_h

#include "Mesh.h"
#include "Material.h"

class ModelLoader
{
public:
	static std::vector<smart_pointer<Material>> LoadMtl(const char* filename);
	static void LoadObj(const char* filename, smart_pointer<Mesh>& mesh);
};

#endif