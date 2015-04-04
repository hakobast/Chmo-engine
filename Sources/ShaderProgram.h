
#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "GL_LIBS.h"
#include "smart_pointer.h"

class UniformDesc
{
public:
	UniformDesc(const char* name, GLenum type): type(type)
	{
		strcpy(this->name, name);
	};

	char name[100];
	GLenum type;
};

class ShaderProgram : public RemovableObject
{
public:
	ShaderProgram();
	~ShaderProgram();
	void loadShaderFromString(GLenum shader_type, const char* source);
	void loadShaderFromFile(GLenum shader_type, const char* filename);
	void createAndLinkProgram();
	void bind();
	void unbind();
	GLuint getProgram();
	void deleteProgram();
	std::vector<UniformDesc> getUniforms(GLenum typeFilter = -1);
	GLuint getUniformLocation(const char* name);
	GLuint getAttributeLocation(const char* name);

	void setUniform1f(const char* name, GLfloat v0);
	void setUniform1fv(const char* name, GLsizei count, const GLfloat* value);
	void setUniform1i(const char* name, GLint v0);
	void setUniform1iv(const char* name, GLsizei count, const GLint* value);
	void setUniform2f(const char* name, GLfloat v0, GLfloat v1);
	void setUniform2fv(const char* name, GLsizei count, const GLfloat* value);
	void setUniform2i(const char* name, GLint v0, GLint v1);
	void setUniform2iv(const char* name, GLsizei count, const GLint* value);
	void setUniform3f(const char* name, GLfloat v0, GLfloat v1, GLfloat v2);
	void setUniform3fv(const char* name, GLsizei count, const GLfloat* value);
	void setUniform3i(const char* name, GLint v0, GLint v1, GLint v2);
	void setUniform3iv(const char* name, GLsizei count, const GLint* value);
	void setUniform4f(const char* name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
	void setUniform4fv(const char* name, GLsizei count, const GLfloat* value);
	void setUniform4i(const char* name, GLint v0, GLint v1, GLint v2, GLint v3);
	void setUniform4iv(const char* name, GLsizei count, const GLint* value);
	void setUniformMatrix2fv(const char* name, GLsizei count, GLboolean transpose, const GLfloat* value);
	void setUniformMatrix3fv(const char* name, GLsizei count, GLboolean transpose, const GLfloat* value);
	void setUniformMatrix4fv(const char* name, GLsizei count, GLboolean transpose, const GLfloat* value);

	void setVertexAttrib1d(const char* name, GLdouble x);
	void setVertexAttrib1dv(const char* name, const GLdouble* v);
	void setVertexAttrib1f(const char* name, GLfloat x);
	void setVertexAttrib1fv(const char* name, const GLfloat* v);
	void setVertexAttrib1s(const char* name, GLshort x);
	void setVertexAttrib1sv(const char* name, const GLshort* v);
	void setVertexAttrib2d(const char* name, GLdouble x, GLdouble y);
	void setVertexAttrib2dv(const char* name, const GLdouble* v);
	void setVertexAttrib2f(const char* name, GLfloat x, GLfloat y);
	void setVertexAttrib2fv(const char* name, const GLfloat* v);
	void setVertexAttrib2s(const char* name, GLshort x, GLshort y);
	void setVertexAttrib2sv(const char* name, const GLshort* v);
	void setVertexAttrib3d(const char* name, GLdouble x, GLdouble y, GLdouble z);
	void setVertexAttrib3dv(const char* name, const GLdouble* v);
	void setVertexAttrib3f(const char* name, GLfloat x, GLfloat y, GLfloat z);
	void setVertexAttrib3fv(const char* name, const GLfloat* v);
	void setVertexAttrib3s(const char* name, GLshort x, GLshort y, GLshort z);
	void setVertexAttrib3sv(const char* name, const GLshort* v);
	void setVertexAttrib4bv(const char* name, const GLbyte* v);
	void setVertexAttrib4iv(const char* name, const GLint* v);
	void setVertexAttrib4sv(const char* name, const GLshort* v);
	void setVertexAttrib4ub(const char* name, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
	void setVertexAttrib4ubv(const char* name, const GLubyte* v);
	void setVertexAttrib4uiv(const char* name, const GLuint* v);
	void setVertexAttrib4usv(const char* name, const GLushort* v);
	void setVertexAttrib4d(const char* name, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
	void setVertexAttrib4dv(const char* name, const GLdouble* v);
	void setVertexAttrib4f(const char* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	void setVertexAttrib4fv(const char* name, const GLfloat* v);
	void setVertexAttrib4s(const char* name, GLshort x, GLshort y, GLshort z, GLshort w);
	void setVertexAttribPointer(const char* name, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);

private:
	enum ShaderType{VERTEX_SHADER,FRAGMENT_SHADER,GEOMETRY_SHADER};
	GLuint _program;
	int _nShaders;
	GLuint _shaders[3];
};

inline GLuint ShaderProgram::getProgram()
{
	return _program;
}

inline void ShaderProgram::deleteProgram()
{
	glDeleteObjectARB(_program);
	_program = -1;
}

inline void ShaderProgram::bind()
{
	glUseProgramObjectARB(_program);
}

inline void ShaderProgram::unbind()
{
	glUseProgramObjectARB(0);
}

inline GLuint ShaderProgram::getUniformLocation(const char* name)
{
	return glGetUniformLocationARB(_program, name);
}

inline GLuint ShaderProgram::getAttributeLocation(const char* name)
{
	return glGetAttribLocationARB(_program, name);
}

inline void ShaderProgram::setUniform1f(const char* name, GLfloat v0)
{
	GLuint location = getUniformLocation(name);
	bind();
	glUniform1fARB(location, v0);
	unbind();
}

inline void ShaderProgram::setUniform1fv(const char* name, GLsizei count, const GLfloat* value)
{
	GLuint location = getUniformLocation(name);
	bind();
	glUniform1fvARB(location, count, value);
	unbind();
}

inline void ShaderProgram::setUniform1i(const char* name, GLint v0)
{
	GLuint location = getUniformLocation(name);
	bind();
	glUniform1iARB(location, v0);
	unbind();
}

inline void ShaderProgram::setUniform1iv(const char* name, GLsizei count, const GLint* value)
{
	GLuint location = getUniformLocation(name);
	bind();
	glUniform1ivARB(location, count, value);
	unbind();
}

inline void ShaderProgram::setUniform2f(const char* name, GLfloat v0, GLfloat v1)
{
	GLuint location = getUniformLocation(name);
	bind();
	glUniform2fARB(location, v0, v1);
	unbind();
}

inline void ShaderProgram::setUniform2fv(const char* name, GLsizei count, const GLfloat* value)
{
	GLuint location = getUniformLocation(name);
	bind();
	glUniform2fvARB(location, count, value);
	unbind();
}

inline void ShaderProgram::setUniform2i(const char* name, GLint v0, GLint v1)
{
	GLuint location = getUniformLocation(name);
	bind();
	glUniform2iARB(location, v0, v1);
	unbind();
}

inline void ShaderProgram::setUniform2iv(const char* name, GLsizei count, const GLint* value)
{
	GLuint location = getUniformLocation(name);
	bind();
	glUniform2ivARB(location, count, value);
	unbind();
}

inline void ShaderProgram::setUniform3f(const char* name, GLfloat v0, GLfloat v1, GLfloat v2)
{
	GLuint location = getUniformLocation(name);
	bind();
	glUniform3fARB(location, v0, v1, v2);
	unbind();
}

inline void ShaderProgram::setUniform3fv(const char* name, GLsizei count, const GLfloat* value)
{
	GLuint location = getUniformLocation(name);
	bind();
	glUniform3fvARB(location, count, value);
	unbind();
}

inline void ShaderProgram::setUniform3i(const char* name, GLint v0, GLint v1, GLint v2)
{
	GLuint location = getUniformLocation(name);
	bind();
	glUniform3iARB(location, v0, v1, v2);
	unbind();
}

inline void ShaderProgram::setUniform3iv(const char* name, GLsizei count, const GLint* value)
{
	GLuint location = getUniformLocation(name);
	bind();
	glUniform3ivARB(location, count, value);
	unbind();
}

inline void ShaderProgram::setUniform4f(const char* name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	GLuint location = getUniformLocation(name);
	bind();
	glUniform4fARB(location, v0, v1, v2, v3);
	unbind();
}

inline void ShaderProgram::setUniform4fv(const char* name, GLsizei count, const GLfloat* value)
{
	GLuint location = getUniformLocation(name);
	bind();
	glUniform4fvARB(location, count, value);
	unbind();
}

inline void ShaderProgram::setUniform4i(const char* name, GLint v0, GLint v1, GLint v2, GLint v3)
{
	GLuint location = getUniformLocation(name);
	bind();
	glUniform4iARB(location, v0, v1, v2, v3);
	unbind();
}

inline void ShaderProgram::setUniform4iv(const char* name, GLsizei count, const GLint* value)
{
	GLuint location = getUniformLocation(name);
	bind();
	glUniform4ivARB(location, count, value);
	unbind();
}

inline void ShaderProgram::setUniformMatrix2fv(const char* name, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	GLuint location = getUniformLocation(name);
	bind();
	glUniformMatrix2fvARB(location, count, transpose, value);
	unbind();
}

inline void ShaderProgram::setUniformMatrix3fv(const char* name, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	GLuint location = getUniformLocation(name);
	bind();
	glUniformMatrix3fvARB(location, count, transpose, value);
	unbind();
}

inline void ShaderProgram::setUniformMatrix4fv(const char* name, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	GLuint location = getUniformLocation(name);
	bind();
	glUniformMatrix4fvARB(location, count, transpose, value);
	unbind();
}

/* ATTRIBUTES */
inline void ShaderProgram::setVertexAttrib1d(const char* name, GLdouble x)
{
	GLuint location = getAttributeLocation(name);
	glVertexAttrib1dARB(location, x);
}

inline void ShaderProgram::setVertexAttrib1dv(const char* name, const GLdouble* v)
{
	GLuint location = getAttributeLocation(name);
	glVertexAttrib1dvARB(location, v);
}

inline void ShaderProgram::setVertexAttrib1f(const char* name, GLfloat x)
{
	GLuint location = getAttributeLocation(name);
	glVertexAttrib1fARB(location, x);
}

inline void ShaderProgram::setVertexAttrib1fv(const char* name, const GLfloat* v)
{
	GLuint location = getAttributeLocation(name);
	glVertexAttrib1fvARB(location, v);
}

inline void ShaderProgram::setVertexAttrib1s(const char* name, GLshort x)
{
	GLuint location = getAttributeLocation(name);
	glVertexAttrib1sARB(location, x);
}

inline void ShaderProgram::setVertexAttrib1sv(const char* name, const GLshort* v)
{
	GLuint location = getAttributeLocation(name);
	glVertexAttrib1svARB(location, v);
}

inline void ShaderProgram::setVertexAttrib2d(const char* name, GLdouble x, GLdouble y)
{
	GLuint location = getAttributeLocation(name);
	glVertexAttrib2dARB(location, x,y);
}

inline void ShaderProgram::setVertexAttrib2dv(const char* name, const GLdouble* v)
{
	GLuint location = getAttributeLocation(name);
	glVertexAttrib2dvARB(location, v);
}

inline void ShaderProgram::setVertexAttrib2f(const char* name, GLfloat x, GLfloat y)
{
	GLuint location = getAttributeLocation(name);
	glVertexAttrib2fARB(location, x, y);
}

inline void ShaderProgram::setVertexAttrib2fv(const char* name, const GLfloat* v)
{
	GLuint location = getAttributeLocation(name);
	glVertexAttrib2fvARB(location, v);
}

inline void ShaderProgram::setVertexAttrib2s(const char* name, GLshort x, GLshort y)
{
	GLuint location = getAttributeLocation(name);
	glVertexAttrib2sARB(location, x, y);
}

inline void ShaderProgram::setVertexAttrib2sv(const char* name, const GLshort* v)
{
	GLuint location = getAttributeLocation(name);
	glVertexAttrib2svARB(location, v);
}

inline void ShaderProgram::setVertexAttrib3d(const char* name, GLdouble x, GLdouble y, GLdouble z)
{
	GLuint location = getAttributeLocation(name);
	glVertexAttrib3dARB(location, x, y, z);
}

inline void ShaderProgram::setVertexAttrib3dv(const char* name, const GLdouble* v)
{
	GLuint location = getAttributeLocation(name);
	glVertexAttrib3dvARB(location, v);
}

inline void ShaderProgram::setVertexAttrib3f(const char* name, GLfloat x, GLfloat y, GLfloat z)
{
	GLuint location = getAttributeLocation(name);
	glVertexAttrib3fARB(location, x, y, z);
}

inline void ShaderProgram::setVertexAttrib3fv(const char* name, const GLfloat* v)
{
	GLuint location = getAttributeLocation(name);
	glVertexAttrib3fvARB(location, v);
}

inline void ShaderProgram::setVertexAttrib3s(const char* name, GLshort x, GLshort y, GLshort z)
{
	GLuint location = getAttributeLocation(name);
	glVertexAttrib3sARB(location, x, y, z);
}

inline void ShaderProgram::setVertexAttrib3sv(const char* name, const GLshort* v)
{
	GLuint location = getAttributeLocation(name);
	glVertexAttrib3svARB(location, v);
}

inline void ShaderProgram::setVertexAttrib4bv(const char* name, const GLbyte* v)
{
	GLuint location = getAttributeLocation(name);
	glVertexAttrib4bvARB(location, v);
}

inline void ShaderProgram::setVertexAttrib4iv(const char* name, const GLint* v)
{
	GLuint location = getAttributeLocation(name);
	glVertexAttrib4ivARB(location,v);
}

inline void ShaderProgram::setVertexAttrib4sv(const char* name, const GLshort* v)
{
	GLuint location = getAttributeLocation(name);
	glVertexAttrib4svARB(location, v);
}

inline void ShaderProgram::setVertexAttrib4ub(const char* name, GLubyte x, GLubyte y, GLubyte z, GLubyte w)
{
	GLuint location = getAttributeLocation(name);
	glVertexAttrib4NubARB(location, x, y, z, w);
}

inline void ShaderProgram::setVertexAttrib4ubv(const char* name, const GLubyte* v)
{
	GLuint location = getAttributeLocation(name);
	glVertexAttrib4ubvARB(location, v);
}

inline void ShaderProgram::setVertexAttrib4uiv(const char* name, const GLuint* v)
{
	GLuint location = getAttributeLocation(name);
	glVertexAttrib4uivARB(location, v);	
}

inline void ShaderProgram::setVertexAttrib4usv(const char* name, const GLushort* v)
{
	GLuint location = getAttributeLocation(name);
	glVertexAttrib4usvARB(location, v);
}

inline void ShaderProgram::setVertexAttrib4d(const char* name, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
	GLuint location = getAttributeLocation(name);
	glVertexAttrib4dARB(location, x, y, z, w);
}

inline void ShaderProgram::setVertexAttrib4dv(const char* name, const GLdouble* v)
{
	GLuint location = getAttributeLocation(name);
	glVertexAttrib4dvARB(location, v);
}

inline void ShaderProgram::setVertexAttrib4f(const char* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	GLuint location = getAttributeLocation(name);
	glVertexAttrib4fARB(location, x, y, z, w);
}

inline void ShaderProgram::setVertexAttrib4fv(const char* name, const GLfloat* v)
{
	GLuint location = getAttributeLocation(name);
	glVertexAttrib4fvARB(location, v);
}

inline void ShaderProgram::setVertexAttrib4s(const char* name, GLshort x, GLshort y, GLshort z, GLshort w)
{
	GLuint location = getAttributeLocation(name);
	glVertexAttrib4sARB(location, x, y, z, w);
}

inline void ShaderProgram::setVertexAttribPointer(const char* name, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer)
{
	GLuint location = getAttributeLocation(name);
	glVertexAttribPointerARB(location, size, type, normalized, stride, pointer);
}

#endif