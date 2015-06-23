#ifndef GL_DRAWER_H
#define GL_DRAWER_H

#include <stdio.h>
#include <map>

#include "LIBS.h"
#include "Enums.h"
#include "../Extras/GLVertexAttribute.h"

class GLDrawer
{
public:
	~GLDrawer();
	GLDrawer(GLenum drawingMode, DataUsage dataUsage);

	const GLenum drawingMode;
	const DataUsage dataUsage;

	void setVertexData		(GLsizei size, GLboolean normalized, GLuint count, GLfloat* data, GLenum VBOUsage = GL_STATIC_DRAW);
	void setTexCoordData	(GLsizei size, GLboolean normalized, GLuint count, GLfloat* data, GLenum VBOUsage = GL_STATIC_DRAW);
	void setTangentData		(GLsizei size, GLboolean normalized, GLuint count, GLfloat* data, GLenum VBOUsage = GL_STATIC_DRAW);
	void setBitangentData	(GLsizei size, GLboolean normalized, GLuint count, GLfloat* data, GLenum VBOUsage = GL_STATIC_DRAW);
	void setNormalData					  (GLboolean normalized, GLuint count, GLfloat* data, GLenum VBOUsage = GL_STATIC_DRAW);
	void setIndexData		(GLuint count, GLuint* data, GLenum VBOUsage = GL_STATIC_DRAW);

	void setAttributeData(int id, GLuint index, GLsizei size, GLuint count, GLsizeiptr valueBytes, GLenum valueType, void* data, GLenum VBOUsage = GL_STATIC_DRAW);

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

	const GLVertexAttribute*const getAttribute(int id) const;

	void draw();
	void updateBuffers();
private:
	GLVertexAttribute vertexAttribute_;
	GLVertexAttribute texCoordAttribute_;
	GLVertexAttribute normalAttribute_;
	GLVertexAttribute tangentAttribute_;
	GLVertexAttribute bitangentAttribute_;
	GLVertexAttribute indexAttribute_;
	std::map<int, GLVertexAttribute> customAttributes_;

	bool hasVAOSupport_;
	bool hasVBOSupport_;

	bool isDirty();
};

inline bool GLDrawer::isDirty()
{
	return vertexAttribute_.isDirty || texCoordAttribute_.isDirty || normalAttribute_.isDirty || tangentAttribute_.isDirty || bitangentAttribute_.isDirty || indexAttribute_.isDirty;
}

inline GLuint GLDrawer::getVertexCount() const
{
	return vertexAttribute_.count;
}

inline GLuint GLDrawer::getTexCoordCount() const
{
	return texCoordAttribute_.count;
}

inline GLuint GLDrawer::getNormalCount() const
{
	return normalAttribute_.count;
}

inline GLuint GLDrawer::getTangentCount() const
{
	return tangentAttribute_.count;
}

inline GLuint GLDrawer::getBitangentCount() const
{
	return bitangentAttribute_.count;
}

inline GLfloat* GLDrawer::getVertexData()
{
// 	if (vertexData_ == NULL)
// 		return NULL;
// 
// 	GLfloat* data = new GLfloat[vertexCount_*vertexSize_];
// 	memcpy(data, vertexData_, vertexCount_*vertexSize_*sizeof(GLfloat));
// 
// 	return data;

	return (GLfloat*)vertexAttribute_.data;
}

inline GLfloat* GLDrawer::getTexCoordData()
{
// 	if (texCoordData_ == NULL)
// 		return NULL;
// 
// 	GLfloat* data = new GLfloat[texCoordCount_*texCoordSize_];
// 	memcpy(data, texCoordData_, texCoordCount_*texCoordSize_*sizeof(GLfloat));
// 
// 	return data;

	return (GLfloat*)texCoordAttribute_.data;
}

inline GLfloat* GLDrawer::getNormalData()
{
// 	if (normalData_ == NULL)
// 		return NULL;
// 
// 	GLfloat* data = new GLfloat[normalCount_ * normalSize_];
// 	memcpy(data, normalData_, normalCount_ * normalSize_ * sizeof(GLfloat));

	return (GLfloat*)normalAttribute_.data;
}

inline GLfloat* GLDrawer::getTangentData()
{
// 	if (tangentData_ == NULL)
// 		return NULL;
// 
// 	GLfloat* data = new GLfloat[tangentCount_ * tangentSize_];
// 	memcpy(data, tangentData_, tangentCount_ * tangentSize_ * sizeof(GLfloat));

	return (GLfloat*)tangentAttribute_.data;
}

inline GLfloat* GLDrawer::getBitangentData()
{
// 	if (bitangentData_ == NULL)
// 		return NULL;
// setVertexAttribLocation
// 	GLfloat* data = new GLfloat[bitangentCount_ * bitangentSize_];
// 	memcpy(data, bitangentData_, bitangentCount_ * bitangentSize_ * sizeof(GLfloat));

	return (GLfloat*)bitangentAttribute_.data;
}

inline GLuint* GLDrawer::getIndexData()
{
// 	if (indexData_ == NULL)
// 		return NULL;
// 
// 	GLuint* data = new GLuint[indexCount_];
// 	memcpy(data, indexData_, indexCount_ * sizeof(GLuint));

	return (GLuint*)indexAttribute_.data;
}

inline void GLDrawer::setVertexIndex(GLuint index)
{
	vertexAttribute_.index = index;
}

inline void GLDrawer::setTexCoordIndex(GLuint index)
{
	texCoordAttribute_.index = index;
}

inline void GLDrawer::setNormalIndex(GLuint index)
{
	normalAttribute_.index = index;
}

inline void GLDrawer::setTangentIndex(GLuint index)
{
	tangentAttribute_.index = index;
}

inline void GLDrawer::setBitangentIndex(GLuint index)
{
	bitangentAttribute_.index = index;
}

inline GLuint GLDrawer::getVertexIndex()
{
	return vertexAttribute_.index;
}

inline GLuint GLDrawer::getTexCoordIndex()
{
	return texCoordAttribute_.index;
}

inline GLuint GLDrawer::getNormalIndex()
{
	return normalAttribute_.index;
}

inline GLuint GLDrawer::getTangentIndex()
{
	return tangentAttribute_.index;
}

inline GLuint GLDrawer::getBitangentIndex()
{
	return bitangentAttribute_.index;
}

inline const GLVertexAttribute*const GLDrawer::getAttribute(int id) const
{
	std::map<int, GLVertexAttribute>::const_iterator iter = customAttributes_.find(id);
	if (iter != customAttributes_.end())
		return &iter->second;

	return NULL;
}

#endif