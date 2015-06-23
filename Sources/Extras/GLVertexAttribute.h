#ifndef GL_VERTEX_ATTRIBUTE_H
#define GL_VERTEX_ATTRIBUTE_H

#include "../CoreEngine/LIBS.h"

struct GLVertexAttribute
{
	void* data;
	GLuint count = 0;
	GLuint size = 0;	
	GLuint bufferId = 0;
	GLuint index = 0;
	GLboolean isNormalized;
	GLsizeiptr valueBytes;
	GLenum valueType;
	GLenum VBOUsage;
	bool isDirty = false;
};

#endif