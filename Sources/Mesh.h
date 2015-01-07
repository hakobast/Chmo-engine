#ifndef EngineTesting_Mesh_h
#define EngineTesting_Mesh_h

#include <vector>
#include "Vectors.h"
#include "smart_pointer.h"

class SubMesh : public RemovableObject
{
public:
	std::vector<Vector3> vertices;
	std::vector<Vector2> uvs;
	std::vector<Vector3> normals;
	std::vector<unsigned int> indices;
};

class Mesh:public RemovableObject
{
private:
	std::vector<smart_pointer<SubMesh>> submeshes;
public:
	Mesh();
	~Mesh();
	std::vector<Vector3> getVertices(int submesh = 0);
	std::vector<Vector2> getUVs(int submesh = 0);
	std::vector<Vector3> getNormals(int submesh = 0);
	std::vector<unsigned int> getIndices(int submesh = 0);
	void setVertices(std::vector<Vector3>,int submesh = 0);
	void setUVs(std::vector<Vector2>, int submesh = 0);
	void setNormals(std::vector<Vector3>, int submesh = 0);
	void setIndices(std::vector<unsigned int>, int submesh = 0);
	int getSubMeshCount();
	void setSubMeshCount(int count);
	void clear();
	std::string name;
};

inline int Mesh::getSubMeshCount()
{
	return submeshes.size();
}

inline void Mesh::setSubMeshCount(int count)
{
	if (submeshes.size() < count)
		submeshes.resize(count, smart_pointer<SubMesh>(new SubMesh));
	else
		submeshes.resize(count);
}

inline std::vector<Vector3> Mesh::getVertices(int submesh)
{
	return submeshes[submesh]->vertices;
}

inline std::vector<Vector2> Mesh::getUVs(int submesh)
{
	return submeshes[submesh]->uvs;
}

inline std::vector<Vector3> Mesh::getNormals(int submesh)
{
	return submeshes[submesh]->normals;
}

inline std::vector<unsigned int> Mesh::getIndices(int submesh)
{
	return submeshes[submesh]->indices;
}

inline void Mesh::setVertices(std::vector<Vector3> vertices, int submesh)
{
	submeshes[submesh]->vertices = vertices;
}

inline void Mesh::setUVs(std::vector<Vector2> uvs, int submesh)
{
	submeshes[submesh]->uvs = uvs;
}

inline void Mesh::setNormals(std::vector<Vector3> normals, int submesh)
{
	submeshes[submesh]->normals = normals;
}

inline void Mesh::setIndices(std::vector<unsigned int> indices, int submesh)
{
	submeshes[submesh]->indices = indices;
}

inline void Mesh::clear()
{
	for (smart_pointer<SubMesh> m : submeshes)
	{
		m->vertices.clear();
		m->uvs.clear();
		m->normals.clear();
		m->indices.clear();
	}
}

#endif