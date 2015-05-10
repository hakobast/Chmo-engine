#ifndef EngineTesting_Mesh_h
#define EngineTesting_Mesh_h

#include <vector>
#include "Utils.h"
#include "../Extras/Vectors.h"
#include "../Extras/smart_pointer.h"

class Mesh:public RemovableObject
{
friend class MeshRenderer;

	class SubMesh : public RemovableObject
	{
		friend class Mesh;
		friend class MeshRenderer;

		GLboolean _updateVertices = 0;
		GLboolean _updateTexCoords = 0;
		GLboolean _updateNormals = 0;
		GLboolean _updateIndices = 0;

		GLuint vertex_buffer_id = 0;
		GLuint uv_buffer_id = 0;
		GLuint normal_buffer_id = 0;
		GLuint index_buffer_id = 0;

		GLuint vertex_count = 0;
		GLuint uv_count = 0;
		GLuint normal_count = 0;
		GLuint index_count = 0;

		std::vector<Vector3> vertices;
		std::vector<Vector2> uvs;
		std::vector<Vector3> normals;
		std::vector<unsigned int> indices;

		inline GLboolean _updateVBO()
		{
			return _updateVertices || _updateTexCoords || _updateNormals || _updateIndices;
		}
	};

private:
	GLenum vboUsage_ = GL_STATIC_DRAW;
	int sharesCount_ = 0;
	std::vector<smart_pointer<SubMesh>> submeshes_;
	void genBuffers(int submesh = 0);
	void deleteAllBuffers(int submesh = 0);
	void draw(int sumbmesh = 0);
public:
	Mesh(const Mesh& other);
	Mesh();
	~Mesh();
	std::vector<Vector3> getVertices(int submesh = 0) const;
	std::vector<Vector2> getUVs(int submesh = 0) const ;
	std::vector<Vector3> getNormals(int submesh = 0) const;
	std::vector<unsigned int> getIndices(int submesh = 0) const;
	void setVertices(std::vector<Vector3>,int submesh = 0);
	void setUVs(std::vector<Vector2>, int submesh = 0);
	void setNormals(std::vector<Vector3>, int submesh = 0);
	void setIndices(std::vector<unsigned int>, int submesh = 0);
	int getSubMeshCount() const;
	void setSubMeshCount(int count);
	void setVBOUsage(GLenum usage);
	void clear();
	std::string name;
};

inline int Mesh::getSubMeshCount() const
{
	return submeshes_.size();
}

inline void Mesh::setSubMeshCount(int count)
{
	if (count > (int)submeshes_.size()) // adding new submeshes
		submeshes_.resize(count, smart_pointer<SubMesh>(new SubMesh));
	else 
	{
		//removing submeshes
		while (count < (int)submeshes_.size())
		{
			deleteAllBuffers(submeshes_.size() - 1);
			submeshes_.pop_back();
		}
	}
}

inline void Mesh::setVBOUsage(GLenum usage)
{
	vboUsage_ = usage;
}

#endif