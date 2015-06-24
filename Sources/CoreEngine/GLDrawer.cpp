
#include "../Extras/GLUtils.h"
#include "../Debug/Logger.h"
#include "GLDrawer.h"

GLDrawer::~GLDrawer()
{
	if (vertexAttribute_.bufferId != 0)	 glDeleteBuffers(1, &vertexAttribute_.bufferId);
	if (texCoordAttribute_.bufferId != 0)  glDeleteBuffers(1, &texCoordAttribute_.bufferId);
	if (normalAttribute_.bufferId != 0)	 glDeleteBuffers(1, &normalAttribute_.bufferId);
	if (tangentAttribute_.bufferId != 0)	 glDeleteBuffers(1, &tangentAttribute_.bufferId);
	if (bitangentAttribute_.bufferId != 0) glDeleteBuffers(1, &bitangentAttribute_.bufferId);
	if (indexAttribute_.bufferId != 0)	 glDeleteBuffers(1, &indexAttribute_.bufferId);

	std::map<int, GLVertexAttribute*>::iterator iter = customAttributes_.begin();
	for (iter = customAttributes_.begin(); iter != customAttributes_.end(); iter++)
	{
		GLVertexAttribute* attribute = iter->second;
		if (attribute->bufferId != 0)
			glDeleteBuffers(1, &attribute->bufferId);

		delete attribute;
	}
}

GLDrawer::GLDrawer(GLenum drawingMode, DataUsage dataUsage)
:drawingMode(drawingMode), dataUsage(dataUsage)
{
#ifdef GL_ES_VERSION_2_0
	hasVBOSupport_ = true;
	hasVAOSupport_ = isExtensionSupported("OES_vertex_array_object");
#else
	hasVBOSupport_ = isVBOSupported();
	hasVAOSupport_ = true;
#endif

	if (dataUsage == VBO)
	{
		if (!hasVBOSupport_ && hasVAOSupport_)
			dataUsage = VAO;
	}
	else if (dataUsage == VAO)
	{
		if (!hasVAOSupport_ && hasVBOSupport_)
			dataUsage = VBO;
	}
}

void GLDrawer::draw()
{
	if (dataUsage == NONE || vertexAttribute_.count <= 0)
		return;

	if (dataUsage == VBO)
	{
		if (isDirty())
			updateBuffers();

		std::map<int, GLVertexAttribute*>::iterator iter = customAttributes_.begin();
		for (iter = customAttributes_.begin(); iter != customAttributes_.end(); iter++)
		{
			GLVertexAttribute* attribute = iter->second;
			if (attribute->count > 0)
			{
				glEnableVertexAttribArray(attribute->index);
				glBindBuffer(GL_ARRAY_BUFFER, attribute->bufferId);
				glVertexAttribPointer(attribute->index, attribute->size, attribute->valueType, attribute->isNormalized, 0, 0);
			}
		}

		if (texCoordAttribute_.count > 0)
		{
			glEnableVertexAttribArray(texCoordAttribute_.index);
			glBindBuffer(GL_ARRAY_BUFFER, texCoordAttribute_.bufferId);
			glVertexAttribPointer(texCoordAttribute_.index, texCoordAttribute_.size, GL_FLOAT, texCoordAttribute_.isNormalized, 0, 0);
		}

		if (normalAttribute_.count > 0)
		{
			glEnableVertexAttribArray(normalAttribute_.index);
			glBindBuffer(GL_ARRAY_BUFFER, normalAttribute_.bufferId);
			glVertexAttribPointer(normalAttribute_.index, normalAttribute_.size, GL_FLOAT, normalAttribute_.isNormalized, 0, 0);
		}

		if (tangentAttribute_.count > 0)
		{
			glEnableVertexAttribArray(tangentAttribute_.index);
			glBindBuffer(GL_ARRAY_BUFFER, tangentAttribute_.bufferId);
			glVertexAttribPointer(tangentAttribute_.index, tangentAttribute_.size, GL_FLOAT, tangentAttribute_.isNormalized, 0, 0);
		}

		if (bitangentAttribute_.count > 0)
		{
			glEnableVertexAttribArray(bitangentAttribute_.index);
			glBindBuffer(GL_ARRAY_BUFFER, bitangentAttribute_.bufferId);
			glVertexAttribPointer(bitangentAttribute_.index, bitangentAttribute_.size, GL_FLOAT, bitangentAttribute_.isNormalized, 0, 0);
		}

		glEnableVertexAttribArray(vertexAttribute_.index);
		glBindBuffer(GL_ARRAY_BUFFER, vertexAttribute_.bufferId);
		glVertexAttribPointer(vertexAttribute_.index, vertexAttribute_.size, GL_FLOAT, vertexAttribute_.isNormalized, 0, 0);

		if (indexAttribute_.count > 0)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexAttribute_.bufferId);
			glDrawElements(drawingMode, indexAttribute_.count, GL_UNSIGNED_INT, 0);
		}
		else
		{
			glDrawArrays(drawingMode, 0, vertexAttribute_.count);
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	else if (dataUsage == VAO)
	{
		std::map<int, GLVertexAttribute*>::iterator iter = customAttributes_.begin();
		for (iter = customAttributes_.begin(); iter != customAttributes_.end(); iter++)
		{
			GLVertexAttribute* attribute = iter->second;
			if (attribute->count > 0)
			{
				glEnableVertexAttribArray(attribute->index);
				glVertexAttribPointer(attribute->index, attribute->size, attribute->valueType, attribute->isNormalized, 0, attribute->data);
			}
		}

		if (texCoordAttribute_.count > 0)
		{
			glEnableVertexAttribArray(texCoordAttribute_.index);
			glVertexAttribPointer(texCoordAttribute_.index, texCoordAttribute_.size, GL_FLOAT, texCoordAttribute_.isNormalized, 0, texCoordAttribute_.data);
		}

		if (normalAttribute_.count > 0)
		{
			glEnableVertexAttribArray(normalAttribute_.index);
			glVertexAttribPointer(normalAttribute_.index, normalAttribute_.size, GL_FLOAT, normalAttribute_.isNormalized, 0, normalAttribute_.data);
		}

		if (tangentAttribute_.count > 0)
		{
			glEnableVertexAttribArray(tangentAttribute_.index);
			glVertexAttribPointer(tangentAttribute_.index, tangentAttribute_.size, GL_FLOAT, tangentAttribute_.isNormalized, 0, tangentAttribute_.data);
		}

		if (bitangentAttribute_.count > 0)
		{
			glEnableVertexAttribArray(bitangentAttribute_.index);
			glVertexAttribPointer(bitangentAttribute_.index, bitangentAttribute_.size, GL_FLOAT, bitangentAttribute_.isNormalized, 0, bitangentAttribute_.data);
		}

		glEnableVertexAttribArray(vertexAttribute_.index);
		glVertexAttribPointer(vertexAttribute_.index, vertexAttribute_.size, GL_FLOAT, vertexAttribute_.isNormalized, 0, vertexAttribute_.data);

		if (indexAttribute_.count > 0)
		{
			glDrawElements(drawingMode, indexAttribute_.count, GL_UNSIGNED_INT, indexAttribute_.data);
		}
		else
		{
			glDrawArrays(drawingMode, 0, vertexAttribute_.count);
		}
	}

	if (vertexAttribute_.count > 0)		glDisableVertexAttribArray(vertexAttribute_.index);
	if (texCoordAttribute_.count > 0)	glDisableVertexAttribArray(texCoordAttribute_.index);
	if (normalAttribute_.count > 0)		glDisableVertexAttribArray(normalAttribute_.index);
	if (tangentAttribute_.count > 0)	glDisableVertexAttribArray(tangentAttribute_.index);
	if (bitangentAttribute_.count > 0)	glDisableVertexAttribArray(bitangentAttribute_.index);

	std::map<int, GLVertexAttribute*>::iterator iter = customAttributes_.begin();
	for (iter = customAttributes_.begin(); iter != customAttributes_.end(); iter++)
	{
		GLVertexAttribute* attribute = iter->second;
		if (attribute->count > 0)
		{
			glDisableVertexAttribArray(attribute->index);
		}
	}
}

void GLDrawer::updateBuffers()
{
	if (vertexAttribute_.isDirty)
	{
		if (vertexAttribute_.bufferId == 0)
		{
			glGenBuffers(1, &vertexAttribute_.bufferId);
			glBindBuffer(GL_ARRAY_BUFFER, vertexAttribute_.bufferId);
			glBufferData(GL_ARRAY_BUFFER, vertexAttribute_.count * vertexAttribute_.size * sizeof(GLfloat), vertexAttribute_.data, vertexAttribute_.VBOUsage);
		}
		else
		{
			glBindBuffer(GL_ARRAY_BUFFER, vertexAttribute_.bufferId);
			glBufferSubData(GL_ARRAY_BUFFER, 0, vertexAttribute_.count * vertexAttribute_.size * sizeof(GLfloat), vertexAttribute_.data);
		}

		vertexAttribute_.isDirty = false;
	}

	if (texCoordAttribute_.isDirty)
	{
		if (texCoordAttribute_.bufferId == 0)
		{
			glGenBuffers(1, &texCoordAttribute_.bufferId);
			glBindBuffer(GL_ARRAY_BUFFER, texCoordAttribute_.bufferId);
			glBufferData(GL_ARRAY_BUFFER, texCoordAttribute_.count * texCoordAttribute_.size * sizeof(GLfloat), texCoordAttribute_.data, texCoordAttribute_.VBOUsage);
		}
		else
		{
			glBindBuffer(GL_ARRAY_BUFFER, texCoordAttribute_.bufferId);
			glBufferSubData(GL_ARRAY_BUFFER, 0, texCoordAttribute_.count * texCoordAttribute_.size * sizeof(GLfloat), texCoordAttribute_.data);
		}

		texCoordAttribute_.isDirty = false;
	}

	if (normalAttribute_.isDirty)
	{
		if (normalAttribute_.bufferId == 0)
		{
			glGenBuffers(1, &normalAttribute_.bufferId);
			glBindBuffer(GL_ARRAY_BUFFER, normalAttribute_.bufferId);
			glBufferData(GL_ARRAY_BUFFER, normalAttribute_.count * normalAttribute_.size * sizeof(GLfloat), normalAttribute_.data, normalAttribute_.VBOUsage);
		}
		else
		{
			glBindBuffer(GL_ARRAY_BUFFER, normalAttribute_.bufferId);
			glBufferSubData(GL_ARRAY_BUFFER, 0, normalAttribute_.count * normalAttribute_.size * sizeof(GLfloat), normalAttribute_.data);
		}

		normalAttribute_.isDirty = false;
	}

	if (tangentAttribute_.isDirty)
	{
		if (tangentAttribute_.bufferId == 0)
		{
			glGenBuffers(1, &tangentAttribute_.bufferId);
			glBindBuffer(GL_ARRAY_BUFFER, tangentAttribute_.bufferId);
			glBufferData(GL_ARRAY_BUFFER, tangentAttribute_.count * tangentAttribute_.size * sizeof(GLfloat), tangentAttribute_.data, tangentAttribute_.VBOUsage);
		}
		else
		{
			glBindBuffer(GL_ARRAY_BUFFER, tangentAttribute_.bufferId);
			glBufferSubData(GL_ARRAY_BUFFER, 0, tangentAttribute_.count * tangentAttribute_.size * sizeof(GLfloat), tangentAttribute_.data);
		}

		tangentAttribute_.isDirty = false;
	}

	if (bitangentAttribute_.isDirty)
	{
		if (bitangentAttribute_.bufferId == 0)
		{
			glGenBuffers(1, &bitangentAttribute_.bufferId);
			glBindBuffer(GL_ARRAY_BUFFER, bitangentAttribute_.bufferId);
			glBufferData(GL_ARRAY_BUFFER, bitangentAttribute_.count * bitangentAttribute_.size * sizeof(GLfloat), bitangentAttribute_.data, bitangentAttribute_.VBOUsage);
		}
		else
		{
			glBindBuffer(GL_ARRAY_BUFFER, bitangentAttribute_.bufferId);
			glBufferSubData(GL_ARRAY_BUFFER, 0, bitangentAttribute_.count * bitangentAttribute_.size * sizeof(GLfloat), bitangentAttribute_.data);
		}

		bitangentAttribute_.isDirty = false;
	}

	if (indexAttribute_.isDirty)
	{
		if (indexAttribute_.bufferId == 0)
		{
			glGenBuffers(1, &indexAttribute_.bufferId);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexAttribute_.bufferId);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexAttribute_.count * sizeof(GLuint), indexAttribute_.data, indexAttribute_.VBOUsage);
		}
		else
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexAttribute_.bufferId);
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indexAttribute_.count * sizeof(GLuint), indexAttribute_.data);
		}

		indexAttribute_.isDirty = false;
	}

	std::map<int, GLVertexAttribute*>::iterator iter = customAttributes_.begin();
	for (iter = customAttributes_.begin(); iter != customAttributes_.end(); iter++)
	{
		GLVertexAttribute* attribute = iter->second;
		if (attribute->isDirty)
		{
			if (attribute->bufferId == 0)
			{
				glGenBuffers(1, &attribute->bufferId);
				glBindBuffer(GL_ARRAY_BUFFER, attribute->bufferId);
				glBufferData(GL_ARRAY_BUFFER, attribute->count * attribute->size * attribute->valueBytes, attribute->data, attribute->VBOUsage);
			}
			else
			{
				glBindBuffer(GL_ARRAY_BUFFER, attribute->bufferId);
				glBufferSubData(GL_ARRAY_BUFFER, 0, attribute->count * attribute->size * attribute->valueBytes, attribute->data);
			}
		}
	}
}

void GLDrawer::setVertexData(GLsizei size, GLboolean normalized, GLuint count, GLfloat* data, GLenum VBOUsage)
{
	if (count*size != vertexAttribute_.count*vertexAttribute_.size || VBOUsage != vertexAttribute_.VBOUsage)
	{
		if (vertexAttribute_.bufferId != 0)
		{
			glDeleteBuffers(1, &vertexAttribute_.bufferId);
			vertexAttribute_.bufferId = 0;
		}
	}

	vertexAttribute_.size = size;
	vertexAttribute_.isNormalized = normalized;
	vertexAttribute_.count = count;
	vertexAttribute_.data = data;
	vertexAttribute_.VBOUsage = VBOUsage;
	vertexAttribute_.isDirty = vertexAttribute_.size*vertexAttribute_.count > 0;
}

void GLDrawer::setTexCoordData(GLsizei size, GLboolean normalized, GLuint count, GLfloat* data, GLenum VBOUsage)
{
	if (count*size != texCoordAttribute_.count*texCoordAttribute_.size || VBOUsage != texCoordAttribute_.VBOUsage)
	{
		if (texCoordAttribute_.bufferId != 0)
		{
			glDeleteBuffers(1, &texCoordAttribute_.bufferId);
			texCoordAttribute_.bufferId = 0;
		}
	}

	texCoordAttribute_.size = size;
	texCoordAttribute_.isNormalized = normalized;
	texCoordAttribute_.count = count;
	texCoordAttribute_.data = data;
	texCoordAttribute_.VBOUsage = VBOUsage;
	texCoordAttribute_.isDirty = texCoordAttribute_.size*texCoordAttribute_.count > 0;
}

void GLDrawer::setTangentData(GLsizei size, GLboolean normalized, GLuint count, GLfloat* data, GLenum VBOUsage)
{
	if (count*size != tangentAttribute_.count*tangentAttribute_.size || VBOUsage != tangentAttribute_.VBOUsage)
	{
		if (tangentAttribute_.bufferId != 0)
		{
			glDeleteBuffers(1, &tangentAttribute_.bufferId);
			tangentAttribute_.bufferId = 0;
		}
	}

	tangentAttribute_.size = size;
	tangentAttribute_.isNormalized = normalized;
	tangentAttribute_.count = count;
	tangentAttribute_.data = data;
	tangentAttribute_.VBOUsage = VBOUsage;
	tangentAttribute_.isDirty = tangentAttribute_.size*tangentAttribute_.count > 0;
}

void GLDrawer::setBitangentData(GLsizei size, GLboolean normalized, GLuint count, GLfloat* data, GLenum VBOUsage)
{
	if (count*size != bitangentAttribute_.count*bitangentAttribute_.size || VBOUsage != bitangentAttribute_.VBOUsage)
	{
		if (bitangentAttribute_.bufferId != 0)
		{
			glDeleteBuffers(1, &bitangentAttribute_.bufferId);
			bitangentAttribute_.bufferId = 0;
		}
	}

	bitangentAttribute_.size = size;
	bitangentAttribute_.isNormalized = normalized;
	bitangentAttribute_.count = count;
	bitangentAttribute_.data = data;
	bitangentAttribute_.VBOUsage = VBOUsage;
	bitangentAttribute_.isDirty = bitangentAttribute_.size*bitangentAttribute_.count > 0;
}

void GLDrawer::setNormalData(GLboolean normalized, GLuint count, GLfloat* data, GLenum VBOUsage)
{
	if (count != normalAttribute_.count || VBOUsage != normalAttribute_.VBOUsage)
	{
		if (normalAttribute_.bufferId != 0)
		{
			glDeleteBuffers(1, &normalAttribute_.bufferId);
			normalAttribute_.bufferId = 0;
		}
	}

	normalAttribute_.size = 3;
	normalAttribute_.isNormalized = normalized;
	normalAttribute_.count = count;
	normalAttribute_.data = data;
	normalAttribute_.VBOUsage = VBOUsage;
	normalAttribute_.isDirty = normalAttribute_.size*normalAttribute_.count > 0;
}

void GLDrawer::setIndexData(GLuint count, GLuint* data, GLenum VBOUsage)
{
	if (count != indexAttribute_.count || VBOUsage != indexAttribute_.VBOUsage)
	{
		if (indexAttribute_.bufferId != 0)
		{
			glDeleteBuffers(1, &indexAttribute_.bufferId);
			indexAttribute_.bufferId = 0;
		}
	}

	indexAttribute_.size = 1;
	indexAttribute_.count = count;
	indexAttribute_.data = data;
	indexAttribute_.VBOUsage = VBOUsage;
	indexAttribute_.isDirty = indexAttribute_.count > 0;
}

void GLDrawer::setCustomAttribute(int id, GLuint index, GLsizei size, GLuint count, GLsizeiptr valueBytes, GLenum valueType, void* data, GLenum VBOUsage)
{
	GLVertexAttribute* attribute = NULL;
	std::map<int, GLVertexAttribute*>::iterator iter = customAttributes_.find(id);
	if (iter != customAttributes_.end())
	{
		attribute = iter->second;
		if (count*size != attribute->count*attribute->size || VBOUsage != attribute->VBOUsage)
		{
			if (attribute->bufferId != 0)
			{
				glDeleteBuffers(1, &attribute->bufferId);
				attribute->bufferId = 0;
			}
		}
	}

	if (attribute == NULL) // attribute not found, creating new
	{
		attribute = new GLVertexAttribute;
	}

	attribute->size = size;
	attribute->count = count;
	attribute->data = data;
	attribute->index = index;
	attribute->valueBytes = valueBytes;
	attribute->valueType = valueType;
	attribute->VBOUsage = VBOUsage;
	attribute->isDirty = attribute->size*attribute->count > 0;

	if (iter == customAttributes_.end())
	{
		customAttributes_.insert(std::pair<int, GLVertexAttribute*>(id, attribute));
	}
}