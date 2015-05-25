#ifndef MESH_H
#define MESH_H

#include <vector>
#include "Utils.h"
#include "Enums.h"
#include "../Extras/Vectors.h"
#include "../Extras/smart_pointer.h"
#include "../Debug/Logger.h"

class GLMeshDrawer;

class Mesh :public RemovableObject
{
friend class MeshRenderer;

	struct SubMesh
	{
		std::vector<Vector3>		vertices;	GLenum vertexVBOUsage;
		std::vector<Vector2>		texCoords;	GLenum texCoordVBOUsage;
		std::vector<Vector3>		normals;	GLenum normalVBOUsage;
		std::vector<Vector3>		tangent;	GLenum tangentVBOUsage;
		std::vector<Vector3>		bitangent;	GLenum bitangentVBOUsage;
		std::vector<unsigned int>	indices;	GLenum indexVBOUsage;
	};

public:
	~Mesh();
	Mesh(const Mesh& other);
	Mesh(GLenum drawingMode = GL_TRIANGLES, DataUsage dataUsage = DataUsage::VBO);

	void setVertices	(std::vector<Vector3>*		vertices,	int submesh = 0, GLenum VBOUsage = GL_STATIC_DRAW);
	void setTexCoords	(std::vector<Vector2>*		texCoords,	int submesh = 0, GLenum VBOUsage = GL_STATIC_DRAW);
	void setNormals		(std::vector<Vector3>*		normals,	int submesh = 0, GLenum VBOUsage = GL_STATIC_DRAW);
	void setTangents	(std::vector<Vector3>*		tangent,	int submesh = 0, GLenum VBOUsage = GL_STATIC_DRAW);
	void setBitangents	(std::vector<Vector3>*		bitangent,	int submesh = 0, GLenum VBOUsage = GL_STATIC_DRAW);
	void setIndices		(std::vector<unsigned int>*	indices,	int submesh = 0, GLenum VBOUsage = GL_STATIC_DRAW);

	std::vector<Vector3>		getVertices	(int submesh = 0) const;
	std::vector<Vector2>		getTexCoords(int submesh = 0) const;
	std::vector<Vector3>		getNormals	(int submesh = 0) const;
	std::vector<Vector3>		getTangent	(int submesh = 0) const;
	std::vector<Vector3>		getBitangent(int submesh = 0) const;
	std::vector<unsigned int>	getIndices	(int submesh = 0) const;

	void setVertexIndex		(GLuint index, int submesh = 0);
	void setTexCoordIndex	(GLuint index, int submesh = 0);
	void setNormalIndex		(GLuint index, int submesh = 0);
	void setTangentIndex	(GLuint index, int submesh = 0);
	void setBitangentIndex	(GLuint index, int submesh = 0);

	void setSubMeshCount(int count);
	int  getSubMeshCount() const;
	void updateMeshData(bool isDataReadable);
	void clear();
private:
	std::vector<SubMesh*> subMeshes_;
	std::vector<GLMeshDrawer*> submeshesDrawers_;
	const GLenum drawingMode_;
	const DataUsage dataUsage_;
	int sharesCount_;

	void draw(int submesh);
};

inline int Mesh::getSubMeshCount() const
{
	return subMeshes_.size();
}

inline std::vector<Vector3> Mesh::getVertices(int submesh) const
{
	if (submesh < 0 || submesh >= getSubMeshCount())
	{
		Logger::PrintWarning("Error in Mesh::getVertices. Invalid Argument \n");
		return std::vector<Vector3>();
	}

	return subMeshes_[submesh]->vertices;
}

inline std::vector<Vector2> Mesh::getTexCoords(int submesh) const
{
	if (submesh < 0 || submesh >= getSubMeshCount())
	{
		Logger::PrintWarning("Error in Mesh::getTexCoords. Invalid Argument \n");
		return std::vector<Vector2>();
	}

	return subMeshes_[submesh]->texCoords;
}

inline std::vector<Vector3> Mesh::getNormals(int submesh) const
{
	if (submesh < 0 || submesh >= getSubMeshCount())
	{
		Logger::PrintWarning("Error in Mesh::getNormals. Invalid Argument \n");
		return std::vector<Vector3>();
	}

	return subMeshes_[submesh]->normals;
}

inline std::vector<Vector3> Mesh::getTangent(int submesh) const
{
	if (submesh < 0 || submesh >= getSubMeshCount())
	{
		Logger::PrintWarning("Error in Mesh::getTangent. Invalid Argument \n");
		return std::vector<Vector3>();
	}

	return subMeshes_[submesh]->tangent;
}

inline std::vector<Vector3> Mesh::getBitangent(int submesh) const
{
	if (submesh < 0 || submesh >= getSubMeshCount())
	{
		Logger::PrintWarning("Error in Mesh::getBitangent. Invalid Argument \n");
		return std::vector<Vector3>();
	}

	return subMeshes_[submesh]->bitangent;
}

inline std::vector<unsigned int> Mesh::getIndices(int submesh) const
{
	if (submesh < 0 || submesh >= getSubMeshCount())
	{
		Logger::PrintWarning("Error in Mesh::getIndices. Invalid Argument \n");
		return std::vector<unsigned int>();
	}
	return subMeshes_[submesh]->indices;
}

#endif