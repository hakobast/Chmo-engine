
#include "Mesh.h"
#include "../Extras/GLUtils.h"
#include "../Debug/Logger.h"

#include "GLDrawer.h"

Mesh::~Mesh()
{
	clear();
}

Mesh::Mesh(const Mesh& other)
:drawingMode_(other.drawingMode_), dataUsage_(other.dataUsage_)
{
	setSubMeshCount(other.getSubMeshCount());

	for (int i = 0; i < getSubMeshCount(); i++)
	{
		if (other.subMeshes_[i]->vertices.size() > 0)
			setVertices(&other.subMeshes_[i]->vertices, i, other.subMeshes_[i]->vertexVBOUsage);
		setVertexIndex(other.submeshesDrawers_[i]->getVertexIndex());

		if (other.subMeshes_[i]->texCoords.size() > 0)
			setTexCoords(&other.subMeshes_[i]->texCoords, i, other.subMeshes_[i]->texCoordVBOUsage);
		setTexCoordIndex(other.submeshesDrawers_[i]->getTexCoordIndex());

		if (other.subMeshes_[i]->normals.size() > 0)
			setNormals(&other.subMeshes_[i]->normals, i, other.subMeshes_[i]->normalVBOUsage);
		setNormalIndex(other.submeshesDrawers_[i]->getNormalIndex());

		if (other.subMeshes_[i]->tangent.size() > 0)
			setTangents(&other.subMeshes_[i]->tangent, i, other.subMeshes_[i]->tangentVBOUsage);
		setTangentIndex(other.submeshesDrawers_[i]->getTangentIndex());

		if (other.subMeshes_[i]->bitangent.size() > 0)
			setBitangents(&other.subMeshes_[i]->bitangent, i, other.subMeshes_[i]->bitangentVBOUsage);
		setBitangentIndex(other.submeshesDrawers_[i]->getBitangentIndex());

		if (other.subMeshes_[i]->indices.size() > 0)
			setIndices(&other.subMeshes_[i]->indices, i, other.subMeshes_[i]->indexVBOUsage);
	}
}

Mesh::Mesh(GLenum drawingMode, DataUsage dataUsage) 
:drawingMode_(drawingMode), dataUsage_(dataUsage)
{

}

void Mesh::draw(int submesh)
{
	if (submesh >= 0 && submesh < getSubMeshCount())
		submeshesDrawers_[submesh]->draw();
}

void Mesh::setSubMeshCount(int count)
{
	if (count >= 0 && count < getSubMeshCount())
	{
		while (count != getSubMeshCount())
		{
			delete subMeshes_.back();		 subMeshes_.pop_back();
			delete submeshesDrawers_.back(); submeshesDrawers_.pop_back();
		}
	}
	else if ( count > getSubMeshCount())
	{
		while (count != getSubMeshCount())
		{
			subMeshes_.push_back(new SubMesh);

			GLDrawer* meshDrawer = new GLDrawer(drawingMode_, dataUsage_);

			//TEMP
			meshDrawer->setVertexIndex(0);
			meshDrawer->setTexCoordIndex(1);
			meshDrawer->setNormalIndex(2);
			meshDrawer->setTangentIndex(3);
			meshDrawer->setBitangentIndex(4);

			submeshesDrawers_.push_back(meshDrawer);
		}
	}
}

void Mesh::clear()
{
	for (GLDrawer* meshDrawer : submeshesDrawers_)
		delete meshDrawer;

	for (SubMesh* subMesh : subMeshes_)
		delete subMesh;
}

void Mesh::updateMeshData(bool isDataReadable)
{
	for (size_t i = 0, len = subMeshes_.size(); i < len; i++)
	{
		submeshesDrawers_[i]->updateBuffers();
		if (!isDataReadable && submeshesDrawers_[i]->dataUsage == VBO)
		{
			subMeshes_[i]->vertices.clear();
			subMeshes_[i]->texCoords.clear();
			subMeshes_[i]->normals.clear();
			subMeshes_[i]->tangent.clear();
			subMeshes_[i]->bitangent.clear();
			subMeshes_[i]->indices.clear();
		}
	}
}

void Mesh::setVertices(std::vector<Vector3>* vertices, int submesh, GLenum VBOUsage)
{
	if (submesh < 0 || submesh >= getSubMeshCount() || vertices->size() == 0)
	{
		Logger::PrintWarning("Error in Mesh::setVertices. Invalid Argument \n");
		return;
	}
	
	subMeshes_[submesh]->vertexVBOUsage = VBOUsage;
	subMeshes_[submesh]->vertices = *vertices;
	submeshesDrawers_[submesh]->setVertexData(3, false, vertices->size(), subMeshes_[submesh]->vertices[0].getPointer(), VBOUsage);
}

void Mesh::setTexCoords(std::vector<Vector2>* texCoords, int submesh, GLenum VBOUsage)
{
	if (submesh < 0 || submesh >= getSubMeshCount() || texCoords->size() == 0)
	{
		Logger::PrintWarning("Error in Mesh::setTexCoords. Invalid Argument \n");
		return;
	}

	subMeshes_[submesh]->texCoordVBOUsage = VBOUsage;
	subMeshes_[submesh]->texCoords = *texCoords;
	submeshesDrawers_[submesh]->setTexCoordData(2, false, texCoords->size(), subMeshes_[submesh]->texCoords[0].getPointer(), VBOUsage);
}

void Mesh::setNormals(std::vector<Vector3>* normals, int submesh, GLenum VBOUsage)
{
	if (submesh < 0 || submesh >= getSubMeshCount() || normals->size() == 0)
	{
		Logger::PrintWarning("Error in Mesh::setNormals. Invalid Argument \n");
		return;
	}

	subMeshes_[submesh]->normalVBOUsage = VBOUsage;
	subMeshes_[submesh]->normals = *normals;
	submeshesDrawers_[submesh]->setNormalData(true, normals->size(), (*normals)[0].getPointer(), VBOUsage);
}

void Mesh::setTangents(std::vector<Vector3>* tangent, int submesh, GLenum VBOUsage)
{
	if (submesh < 0 || submesh >= getSubMeshCount() || tangent->size() == 0)
	{
		Logger::PrintWarning("Error in Mesh::setTangents. Invalid Argument \n");
		return;
	}

	subMeshes_[submesh]->tangentVBOUsage = VBOUsage;
	subMeshes_[submesh]->tangent = *tangent;
	submeshesDrawers_[submesh]->setTangentData(3, false, tangent->size(), subMeshes_[submesh]->tangent[0].getPointer(), VBOUsage);
}

void Mesh::setBitangents(std::vector<Vector3>* bitangent, int submesh, GLenum VBOUsage)
{
	if (submesh < 0 || submesh >= getSubMeshCount() || bitangent->size() == 0)
	{
		Logger::PrintWarning("Error in Mesh::setBitangents. Invalid Argument \n");
		return;
	}

	subMeshes_[submesh]->bitangentVBOUsage = VBOUsage;
	subMeshes_[submesh]->bitangent = *bitangent;
	submeshesDrawers_[submesh]->setBitangentData(3, false, bitangent->size(), subMeshes_[submesh]->bitangent[0].getPointer(), VBOUsage);
}

void Mesh::setIndices(std::vector<unsigned int>* indices, int submesh, GLenum VBOUsage)
{
	if (submesh < 0 || submesh >= getSubMeshCount() || indices->size() == 0)
	{
		Logger::PrintWarning("Error in Mesh::setIndices. Invalid Argument \n");
		return;
	}

	subMeshes_[submesh]->indexVBOUsage = VBOUsage;
	subMeshes_[submesh]->indices = *indices;
	submeshesDrawers_[submesh]->setIndexData(indices->size(), subMeshes_[submesh]->indices.data(), VBOUsage);
}

inline void Mesh::setVertexIndex(GLuint index, int submesh)
{
	if (submesh < 0 || submesh >= getSubMeshCount())
	{
		Logger::PrintWarning("Error in Mesh::setVertexIndex. Invalid Argument \n");
		return;
	}

	submeshesDrawers_[submesh]->setVertexIndex(index);
}

inline void Mesh::setTexCoordIndex(GLuint index, int submesh)
{
	if (submesh < 0 || submesh >= getSubMeshCount())
	{
		Logger::PrintWarning("Error in Mesh::setTexCoordIndex. Invalid Argument \n");
		return;
	}

	submeshesDrawers_[submesh]->setTexCoordIndex(index);
}

inline void Mesh::setNormalIndex(GLuint index, int submesh)
{
	if (submesh < 0 || submesh >= getSubMeshCount())
	{
		Logger::PrintWarning("Error in Mesh::setNormalIndex. Invalid Argument \n");
		return;
	}

	submeshesDrawers_[submesh]->setNormalIndex(index);
}

inline void Mesh::setTangentIndex(GLuint index, int submesh)
{
	if (submesh < 0 || submesh >= getSubMeshCount())
	{
		Logger::PrintWarning("Error in Mesh::setTangentIndex. Invalid Argument \n");
		return;
	}

	submeshesDrawers_[submesh]->setTangentIndex(index);
}

inline void Mesh::setBitangentIndex(GLuint index, int submesh)
{
	if (submesh < 0 || submesh >= getSubMeshCount())
	{
		Logger::PrintWarning("Error in Mesh::setBitangentIndex. Invalid Argument \n");
		return;
	}

	submeshesDrawers_[submesh]->setBitangentIndex(index);
}