
#include "../Extras/GLUtils.h"
#include "../Debug/Logger.h"
#include "GLMeshDrawer.h"

GLMeshDrawer::~GLMeshDrawer()
{
	if (vertexBufferId_ != 0)	 glDeleteBuffers(1, &vertexBufferId_);
	if (texCoordBufferId_ != 0)  glDeleteBuffers(1, &texCoordBufferId_);
	if (normalBufferId_ != 0)	 glDeleteBuffers(1, &normalBufferId_);
	if (tangentBufferId_ != 0)	 glDeleteBuffers(1, &tangentBufferId_);
	if (bitangentBufferId_ != 0) glDeleteBuffers(1, &bitangentBufferId_);
	if (indexBufferId_ != 0)	 glDeleteBuffers(1, &indexBufferId_);
}

GLMeshDrawer::GLMeshDrawer(GLenum drawingMode, DataUsage dataUsage)
:drawingMode(drawingMode), dataUsage(dataUsage)
{
#ifdef GL_ES_VERSION_2_0
	hasVBOSupport = true;
	hasVAOSupport = isExtensionSupported("OES_vertex_array_object");
#else
	hasVBOSupport = isVBOSupported();
	hasVAOSupport = true;
#endif

	if (dataUsage == VBO)
	{
		if (!hasVBOSupport && hasVAOSupport)
			dataUsage = VAO;
	}
	else if (dataUsage == VAO)
	{
		if (!hasVAOSupport && hasVBOSupport)
			dataUsage = VBO;
	}
}

void GLMeshDrawer::draw()
{
	if (dataUsage == NONE)
		return;

	if (dataUsage == VBO)
	{
		if (isDirty())
			updateBuffers();

		if (texCoordCount_ > 0)
		{
			glEnableVertexAttribArray(texCoordIndex_);
			glBindBuffer(GL_ARRAY_BUFFER, texCoordBufferId_);
			glVertexAttribPointer(texCoordIndex_, texCoordSize_, GL_FLOAT, texCoordNormalized_, 0, 0);
		}

		if (normalCount_ > 0)
		{
			glEnableVertexAttribArray(normalIndex_);
			glBindBuffer(GL_ARRAY_BUFFER, normalBufferId_);
			glVertexAttribPointer(normalIndex_, normalSize_, GL_FLOAT, normalNormalized_, 0, 0);
		}

		if (tangentCount_ > 0)
		{
			glEnableVertexAttribArray(tangentIndex_);
			glBindBuffer(GL_ARRAY_BUFFER, tangentBufferId_);
			glVertexAttribPointer(tangentIndex_, tangentSize_, GL_FLOAT, tangentNormalized_, 0, 0);
		}

		if (bitangentCount_ > 0)
		{
			glEnableVertexAttribArray(bitangentIndex_);
			glBindBuffer(GL_ARRAY_BUFFER, bitangentBufferId_);
			glVertexAttribPointer(bitangentIndex_, bitangentSize_, GL_FLOAT, bitangentNormalized_, 0, 0);
		}

		glEnableVertexAttribArray(vertexIndex_);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId_);
		glVertexAttribPointer(vertexIndex_, vertexSize_, GL_FLOAT, vertexNormalized_, 0, 0);

		if (indexCount_ > 0)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId_);
			glDrawElements(drawingMode, indexCount_, GL_UNSIGNED_INT, 0);
		}
		else
		{
			glDrawArrays(drawingMode, 0, vertexCount_);
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	else if (dataUsage == VAO)
	{
		if (texCoordCount_ > 0)
		{
			glEnableVertexAttribArray(texCoordIndex_);
			glVertexAttribPointer(texCoordIndex_, texCoordSize_, GL_FLOAT, texCoordNormalized_, 0, texCoordData_);
		}

		if (normalCount_ > 0)
		{
			glEnableVertexAttribArray(normalIndex_);
			glVertexAttribPointer(normalIndex_, normalSize_, GL_FLOAT, normalNormalized_, 0, normalData_);
		}

		if (tangentCount_ > 0)
		{
			glEnableVertexAttribArray(tangentIndex_);
			glVertexAttribPointer(tangentIndex_, tangentSize_, GL_FLOAT, tangentNormalized_, 0, tangentData_);
		}

		if (bitangentCount_ > 0)
		{
			glEnableVertexAttribArray(bitangentIndex_);
			glVertexAttribPointer(bitangentIndex_, bitangentSize_, GL_FLOAT, bitangentNormalized_, 0, bitangentData_);
		}

		glEnableVertexAttribArray(vertexIndex_);
		glVertexAttribPointer(vertexIndex_, vertexSize_, GL_FLOAT, vertexNormalized_, 0, vertexData_);

		if (indexCount_ > 0)
		{
			glDrawElements(drawingMode, indexCount_, GL_UNSIGNED_INT, indexData_);
		}
		else
		{
			glDrawArrays(drawingMode, 0, vertexCount_);
		}
	}

	if (vertexCount_ > 0)		glDisableVertexAttribArray(vertexIndex_);
	if (texCoordCount_ > 0)		glDisableVertexAttribArray(texCoordIndex_);
	if (normalCount_ > 0)		glDisableVertexAttribArray(normalIndex_);
	if (tangentCount_ > 0)		glDisableVertexAttribArray(tangentIndex_);
	if (bitangentCount_ > 0)	glDisableVertexAttribArray(bitangentIndex_);
}

void GLMeshDrawer::updateBuffers()
{
	if (isVertexDirty_)
	{
		if (vertexBufferId_ == 0)
		{
			glGenBuffers(1, &vertexBufferId_);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId_);
			glBufferData(GL_ARRAY_BUFFER, vertexCount_ * vertexSize_ * sizeof(GLfloat), vertexData_, vertexVBOUsage);
		}
		else
		{
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId_);
			glBufferSubData(GL_ARRAY_BUFFER, 0, vertexCount_ * vertexSize_ * sizeof(GLfloat), vertexData_);
		}

		isVertexDirty_ = false;
	}

	if (isTexCoordDirty_)
	{
		if (texCoordBufferId_ == 0)
		{
			glGenBuffers(1, &texCoordBufferId_);
			glBindBuffer(GL_ARRAY_BUFFER, texCoordBufferId_);
			glBufferData(GL_ARRAY_BUFFER, texCoordCount_ * texCoordSize_ * sizeof(GLfloat), texCoordData_, texCoordVBOUsage);
		}
		else
		{
			glBindBuffer(GL_ARRAY_BUFFER, texCoordBufferId_);
			glBufferSubData(GL_ARRAY_BUFFER, 0, texCoordCount_ * texCoordSize_ * sizeof(GLfloat), texCoordData_);
		}

		isTexCoordDirty_ = false;
	}

	if (isNormalDirty_)
	{
		if (vertexBufferId_ == 0)
		{
			glGenBuffers(1, &vertexBufferId_);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId_);
			glBufferData(GL_ARRAY_BUFFER, vertexCount_ * vertexSize_ * sizeof(GLfloat), vertexData_, vertexVBOUsage);
		}
		else
		{
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId_);
			glBufferSubData(GL_ARRAY_BUFFER, 0, vertexCount_ * vertexSize_ * sizeof(GLfloat), vertexData_);
		}

		isNormalDirty_ = false;
	}

	if (isTangentDirty_)
	{
		if (tangentBufferId_ == 0)
		{
			glGenBuffers(1, &tangentBufferId_);
			glBindBuffer(GL_ARRAY_BUFFER, tangentBufferId_);
			glBufferData(GL_ARRAY_BUFFER, tangentCount_ * tangentSize_ * sizeof(GLfloat), tangentData_, tangentVBOUsage);
		}
		else
		{
			glBindBuffer(GL_ARRAY_BUFFER, tangentBufferId_);
			glBufferSubData(GL_ARRAY_BUFFER, 0, tangentCount_ * tangentSize_ * sizeof(GLfloat), tangentData_);
		}

		isTangentDirty_ = false;
	}

	if (isBitangentDirty_)
	{
		if (bitangentBufferId_ == 0)
		{
			glGenBuffers(1, &bitangentBufferId_);
			glBindBuffer(GL_ARRAY_BUFFER, bitangentBufferId_);
			glBufferData(GL_ARRAY_BUFFER, bitangentCount_ * bitangentSize_ * sizeof(GLfloat), bitangentData_, bitangentVBOUsage);
		}
		else
		{
			glBindBuffer(GL_ARRAY_BUFFER, bitangentBufferId_);
			glBufferSubData(GL_ARRAY_BUFFER, 0, bitangentCount_ * bitangentSize_ * sizeof(GLfloat), bitangentData_);
		}

		isBitangentDirty_ = false;
	}

	if (isIndexDirty_)
	{
		if (indexBufferId_ == 0)
		{
			glGenBuffers(1, &indexBufferId_);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId_);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount_ * sizeof(GLuint), indexData_, indexVBOUsage);
		}
		else
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId_);
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indexCount_ * sizeof(GLuint), indexData_);
		}

		isIndexDirty_= false;
	}
}

void GLMeshDrawer::setVertexData(GLsizei size, GLboolean normalized, GLuint count, GLfloat* data, GLenum VBOUsage)
{
	if (count*size != vertexCount_*vertexSize_ || VBOUsage != vertexVBOUsage)
	{
		if (vertexBufferId_ != 0)
		{
			glDeleteBuffers(1, &vertexBufferId_);
			vertexBufferId_ = 0;
		}
	}

	vertexSize_ = size;
	vertexNormalized_ = normalized;
	vertexCount_ = count;
	vertexData_ = data;
	vertexVBOUsage = VBOUsage;
	isVertexDirty_ = true;
}

void GLMeshDrawer::setTexCoordData(GLsizei size, GLboolean normalized, GLuint count, GLfloat* data, GLenum VBOUsage)
{
	if (count*size != texCoordCount_*texCoordSize_ || VBOUsage != texCoordVBOUsage)
	{
		if (texCoordBufferId_ != 0)
		{
			glDeleteBuffers(1, &texCoordBufferId_);
			texCoordBufferId_ = 0;
		}
	}

	texCoordSize_ = size;
	texCoordNormalized_ = normalized;
	texCoordCount_ = count;
	texCoordData_ = data;
	texCoordVBOUsage = VBOUsage;
	isTexCoordDirty_ = true;
}

void GLMeshDrawer::setTangentData(GLsizei size, GLboolean normalized, GLuint count, GLfloat* data, GLenum VBOUsage)
{
	if (count*size != tangentCount_*tangentSize_ || VBOUsage != tangentVBOUsage)
	{
		if (tangentBufferId_ != 0)
		{
			glDeleteBuffers(1, &tangentBufferId_);
			tangentBufferId_ = 0;
		}
	}

	tangentSize_ = size;
	tangentNormalized_ = normalized;
	tangentCount_ = count;
	tangentData_ = data;
	tangentVBOUsage = VBOUsage;
	isTangentDirty_ = true;
}

void GLMeshDrawer::setBitangentData(GLsizei size, GLboolean normalized, GLuint count, GLfloat* data, GLenum VBOUsage)
{
	if (count*size != bitangentCount_*bitangentSize_ || VBOUsage != bitangentVBOUsage)
	{
		if (bitangentBufferId_ != 0)
		{
			glDeleteBuffers(1, &bitangentBufferId_);
			bitangentBufferId_ = 0;
		}
	}

	bitangentSize_ = size;
	bitangentNormalized_ = normalized;
	bitangentCount_ = count;
	bitangentData_ = data;
	bitangentVBOUsage = VBOUsage;
	isBitangentDirty_ = true;
}

void GLMeshDrawer::setNormalData(GLboolean normalized, GLuint count, GLfloat* data, GLenum VBOUsage)
{
	normalSize_ = 3;
	if (count*normalSize_ != normalCount_*normalSize_ || VBOUsage != normalVBOUsage)
	{
		if (normalBufferId_ != 0)
		{
			glDeleteBuffers(1, &normalBufferId_);
			normalBufferId_ = 0;
		}
	}

	normalNormalized_ = normalized;
	normalCount_ = count;
	normalData_ = data;
	normalVBOUsage = VBOUsage;
	isNormalDirty_ = true;
}

void GLMeshDrawer::setIndexData(GLuint count, GLuint* data, GLenum VBOUsage)
{
	if (count != indexCount_ || VBOUsage != indexVBOUsage)
	{
		if (indexBufferId_ != 0)
		{
			glDeleteBuffers(1, &indexBufferId_);
			indexBufferId_ = 0;
		}
	}

	indexCount_ = count;
	indexData_ = data;
	indexVBOUsage = VBOUsage;
	isIndexDirty_ = true;
}