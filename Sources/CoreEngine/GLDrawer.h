#ifndef GL_DRAWER_H
#define GL_DRAWER_H

#include <stdio.h>

#include "LIBS.h"
#include "Enums.h"

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
	
	GLfloat* vertexData_;		GLuint vertexCount_ = 0;	GLuint vertexSize_;		GLuint vertexBufferId_;		GLuint vertexIndex_;		GLboolean vertexNormalized_;	GLenum vertexVBOUsage;		bool isVertexDirty_ = false;
	GLfloat* texCoordData_;		GLuint texCoordCount_ = 0;	GLuint texCoordSize_;	GLuint texCoordBufferId_;	GLuint texCoordIndex_;		GLboolean texCoordNormalized_;	GLenum texCoordVBOUsage;	bool isTexCoordDirty_ = false;
	GLfloat* normalData_;		GLuint normalCount_ = 0;	GLuint normalSize_;		GLuint normalBufferId_;		GLuint normalIndex_;		GLboolean normalNormalized_;	GLenum normalVBOUsage;		bool isNormalDirty_ = false;
	GLfloat* tangentData_;		GLuint tangentCount_ = 0;	GLuint tangentSize_;	GLuint tangentBufferId_;	GLuint tangentIndex_;		GLboolean tangentNormalized_;	GLenum tangentVBOUsage;		bool isTangentDirty_ = false;
	GLfloat* bitangentData_;	GLuint bitangentCount_ = 0; GLuint bitangentSize_;  GLuint bitangentBufferId_;	GLuint bitangentIndex_;		GLboolean bitangentNormalized_; GLenum bitangentVBOUsage;	bool isBitangentDirty_ = false;
	GLuint*  indexData_;		GLuint indexCount_ = 0;		GLuint indexBufferId_;	GLenum indexVBOUsage;		bool isIndexDataReadable_;	GLboolean isIndexDirty_;

	bool isDirty();
};

inline bool GLDrawer::isDirty()
{
	return isVertexDirty_ || isTexCoordDirty_ || isNormalDirty_ || isTangentDirty_ || isBitangentDirty_ || isIndexDirty_;
}

inline GLuint GLDrawer::getVertexCount() const
{
	return vertexCount_;
}

inline GLuint GLDrawer::getTexCoordCount() const
{
	return texCoordCount_;
}

inline GLuint GLDrawer::getNormalCount() const
{
	return normalCount_;
}

inline GLuint GLDrawer::getTangentCount() const
{
	return tangentCount_;
}

inline GLuint GLDrawer::getBitangentCount() const
{
	return bitangentCount_;
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

	return vertexData_;
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

	return texCoordData_;
}

inline GLfloat* GLDrawer::getNormalData()
{
// 	if (normalData_ == NULL)
// 		return NULL;
// 
// 	GLfloat* data = new GLfloat[normalCount_ * normalSize_];
// 	memcpy(data, normalData_, normalCount_ * normalSize_ * sizeof(GLfloat));

	return normalData_;
}

inline GLfloat* GLDrawer::getTangentData()
{
// 	if (tangentData_ == NULL)
// 		return NULL;
// 
// 	GLfloat* data = new GLfloat[tangentCount_ * tangentSize_];
// 	memcpy(data, tangentData_, tangentCount_ * tangentSize_ * sizeof(GLfloat));

	return tangentData_;
}

inline GLfloat* GLDrawer::getBitangentData()
{
// 	if (bitangentData_ == NULL)
// 		return NULL;
// setVertexAttribLocation
// 	GLfloat* data = new GLfloat[bitangentCount_ * bitangentSize_];
// 	memcpy(data, bitangentData_, bitangentCount_ * bitangentSize_ * sizeof(GLfloat));

	return bitangentData_;
}

inline GLuint* GLDrawer::getIndexData()
{
// 	if (indexData_ == NULL)
// 		return NULL;
// 
// 	GLuint* data = new GLuint[indexCount_];
// 	memcpy(data, indexData_, indexCount_ * sizeof(GLuint));

	return indexData_;
}

inline void GLDrawer::setVertexIndex(GLuint index)
{
	vertexIndex_ = index;
}

inline void GLDrawer::setTexCoordIndex(GLuint index)
{
	texCoordIndex_ = index;
}

inline void GLDrawer::setNormalIndex(GLuint index)
{
	normalIndex_ = index;
}

inline void GLDrawer::setTangentIndex(GLuint index)
{
	tangentIndex_ = index;
}

inline void GLDrawer::setBitangentIndex(GLuint index)
{
	bitangentIndex_ = index;
}

inline GLuint GLDrawer::getVertexIndex()
{
	return vertexIndex_;
}

inline GLuint GLDrawer::getTexCoordIndex()
{
	return texCoordIndex_;
}

inline GLuint GLDrawer::getNormalIndex()
{
	return normalIndex_;
}

inline GLuint GLDrawer::getTangentIndex()
{
	return tangentIndex_;
}

inline GLuint GLDrawer::getBitangentIndex()
{
	return bitangentIndex_;
}

#endif