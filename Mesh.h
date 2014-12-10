#ifndef EngineTesting_Mesh_h
#define EngineTesting_Mesh_h

#include <vector>
#include "Vectors.h"
#include "smart_pointer.h"

class Mesh:public RemovableObject
{
private:
	std::vector<Vector3> vertices;
	std::vector<Vector2> uvs;
	std::vector<Vector3> normals;
	std::vector<unsigned int> indices;

public:
	Mesh();
	~Mesh();
	std::vector<Vector3>& getVertices();
	std::vector<Vector2>& getUVs();
	std::vector<Vector3>& getNormals();
	std::vector<unsigned int>& getIndices();
	void clear();
};

inline std::vector<Vector3>& Mesh::getVertices()
{
	return vertices;
}

inline std::vector<Vector2>& Mesh::getUVs()
{
	return uvs;
}

inline std::vector<Vector3>& Mesh::getNormals()
{
	return normals;
}

inline std::vector<unsigned int>& Mesh::getIndices()
{
	return indices;
}

inline void Mesh::clear()
{
	vertices.clear();
	uvs.clear();
	normals.clear();
	indices.clear();
}

#endif