#ifndef GL_MESH_DRAWER_H
#define GL_MESH_DRAWER_H

#include <stdio.h>

#include "LIBS.h"
#include "Enums.h"

class GLMeshDrawer
{
public:
	~GLMeshDrawer();
	GLMeshDrawer(GLenum drawingMode, DataUsage dataUsage);

	const GLenum drawingMode;
	const DataUsage dataUsage;

	void setVertexData		(GLsizei size, GLboolean normalized, GLuint count, GLfloat* data, GLenum VBOUsage = GL_STATIC_DRAW);
	void setTexCoordData	(GLsizei size, GLboolean normalized, GLuint count, GLfloat* data, GLenum VBOUsage = GL_STATIC_DRAW);
	void setTangentData		(GLsizei size, GLboolean normalized, GLuint count, GLfloat* data, GLenum VBOUsage = GL_STATIC_DRAW);
	void setBitangentData	(GLsizei size, GLboolean normalized, GLuint count, GLfloat* data, GLenum VBOUsage = GL_STATIC_DRAW);
	void setNormalData					  (GLboolean normalized, GLuint count, GLfloat* data, GLenum VBOUsage = GL_STATIC_DRAW);
	void setIndexData		(GLuint count, GLuint* data, GLenum VBOUsage = GL_STATIC_DRAW);

	GLfloat* getVertexData();
	GLfloat* getTexCoordData();
	GLfloat* getNormalData();
	GLfloat* getTangentData();
	GLfloat* getBitangentData();
	GLuint*  getIndexData();

	GLuint getVertexCount()		const;
	GLuint getTexCoordCount()	const;
	GLuint getNormalCount()		const;
	GLuint getTangentCount()	const;
	GLuint getBitangentCount()	const;
	GLuint getIndicesCount()	const;

	void setVertexIndex		(GLuint index);
	void setTexCoordIndex	(GLuint index);
	void setNormalIndex		(GLuint index);
	void setTangentIndex	(GLuint index);
	void setBitangentIndex	(GLuint index);

	GLuint getVertexIndex();
	GLuint getTexCoordIndex();
	GLuint getNormalIndex();
	GLuint getTangentIndex();
	GLuint getBitangentIndex();

	void draw();
	void updateBuffers();
private:
	bool hasVAOSupport;
	bool hasVBOSupport;
	
	GLfloat* vertexData_;		GLuint vertexCount_;	GLuint vertexSize_;		GLuint vertexBufferId_;		GLuint vertexIndex_;		GLboolean vertexNormalized_;	GLenum vertexVBOUsage;		bool isVertexDirty_;
	GLfloat* texCoordData_;		GLuint texCoordCount_;	GLuint texCoordSize_;	GLuint texCoordBufferId_;	GLuint texCoordIndex_;		GLboolean texCoordNormalized_;	GLenum texCoordVBOUsage;	bool isTexCoordDirty_;
	GLfloat* normalData_;		GLuint normalCount_;	GLuint normalSize_;		GLuint normalBufferId_;		GLuint normalIndex_;		GLboolean normalNormalized_;	GLenum normalVBOUsage;		bool isNormalDirty_;
	GLfloat* tangentData_;		GLuint tangentCount_;	GLuint tangentSize_;	GLuint tangentBufferId_;	GLuint tangentIndex_;		GLboolean tangentNormalized_;	GLenum tangentVBOUsage;		bool isTangentDirty_;
	GLfloat* bitangentData_;	GLuint bitangentCount_; GLuint bitangentSize_;  GLuint bitangentBufferId_;	GLuint bitangentIndex_;		GLboolean bitangentNormalized_; GLenum bitangentVBOUsage;	bool isBitangentDirty_;
	GLuint*  indexData_;		GLuint indexCount_;		GLuint indexBufferId_;	GLenum indexVBOUsage;		bool isIndexDataReadable_;	GLboolean isIndexDirty_;

	bool isDirty();
};

inline bool GLMeshDrawer::isDirty()
{
	return isVertexDirty_ || isTexCoordDirty_ || isNormalDirty_ || isTangentDirty_ || isBitangentDirty_ || isIndexDirty_;
}

inline GLuint GLMeshDrawer::getVertexCount() const
{
	return vertexCount_;
}

inline GLuint GLMeshDrawer::getTexCoordCount() const
{
	return texCoordCount_;
}

inline GLuint GLMeshDrawer::getNormalCount() const
{
	return normalCount_;
}

inline GLuint GLMeshDrawer::getTangentCount() const
{
	return tangentCount_;
}

inline GLuint GLMeshDrawer::getBitangentCount() const
{
	return bitangentCount_;
}

inline GLfloat* GLMeshDrawer::getVertexData()
{
// 	if (vertexData_ == NULL)
// 		return NULL;
// 
// 	GLfloat* data = new GLfloat[vertexCount_*vertexSize_];
// 	memcpy(data, vertexData_, vertexCount_*vertexSize_*sizeof(GLfloat));
// 
// 	return data;

	return vertexData_;
}

inline GLfloat* GLMeshDrawer::getTexCoordData()
{
// 	if (texCoordData_ == NULL)
// 		return NULL;
// 
// 	GLfloat* data = new GLfloat[texCoordCount_*texCoordSize_];
// 	memcpy(data, texCoordData_, texCoordCount_*texCoordSize_*sizeof(GLfloat));
// 
// 	return data;

	return texCoordData_;
}

inline GLfloat* GLMeshDrawer::getNormalData()
{
// 	if (normalData_ == NULL)
// 		return NULL;
// 
// 	GLfloat* data = new GLfloat[normalCount_ * normalSize_];
// 	memcpy(data, normalData_, normalCount_ * normalSize_ * sizeof(GLfloat));

	return normalData_;
}

inline GLfloat* GLMeshDrawer::getTangentData()
{
// 	if (tangentData_ == NULL)
// 		return NULL;
// 
// 	GLfloat* data = new GLfloat[tangentCount_ * tangentSize_];
// 	memcpy(data, tangentData_, tangentCount_ * tangentSize_ * sizeof(GLfloat));

	return tangentData_;
}

inline GLfloat* GLMeshDrawer::getBitangentData()
{
// 	if (bitangentData_ == NULL)
// 		return NULL;
// setVertexAttribLocation
// 	GLfloat* data = new GLfloat[bitangentCount_ * bitangentSize_];
// 	memcpy(data, bitangentData_, bitangentCount_ * bitangentSize_ * sizeof(GLfloat));

	return bitangentData_;
}

inline GLuint* GLMeshDrawer::getIndexData()
{
// 	if (indexData_ == NULL)
// 		return NULL;
// 
// 	GLuint* data = new GLuint[indexCount_];
// 	memcpy(data, indexData_, indexCount_ * sizeof(GLuint));

	return indexData_;
}

inline void GLMeshDrawer::setVertexIndex(GLuint index)
{
	vertexIndex_ = index;
}

inline void GLMeshDrawer::setTexCoordIndex(GLuint index)
{
	texCoordIndex_ = index;
}

inline void GLMeshDrawer::setNormalIndex(GLuint index)
{
	normalIndex_ = index;
}

inline void GLMeshDrawer::setTangentIndex(GLuint index)
{
	tangentIndex_ = index;
}

inline void GLMeshDrawer::setBitangentIndex(GLuint index)
{
	bitangentIndex_ = index;
}

inline GLuint GLMeshDrawer::getVertexIndex()
{
	return vertexIndex_;
}

inline GLuint GLMeshDrawer::getTexCoordIndex()
{
	return texCoordIndex_;
}

inline GLuint GLMeshDrawer::getNormalIndex()
{
	return normalIndex_;
}

inline GLuint GLMeshDrawer::getTangentIndex()
{
	return tangentIndex_;
}

inline GLuint GLMeshDrawer::getBitangentIndex()
{
	return bitangentIndex_;
}

#endif