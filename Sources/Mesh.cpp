
#include "Mesh.h"

Mesh::Mesh()
{
	std::cout << "Mesh created" << std::endl;
	setSubMeshCount(1);
}

Mesh::~Mesh()
{
	std::cout << "~Mesh: DONT FORGET DELETE VERTICES" << std::endl;
}