
#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <map>

#include "LIBS.h"
#include "../Extras/smart_pointer.h"
#include "../Extras/GLUtils.h"
#include "../Debug/Logger.h"

class UniformDesc
{
public:
	UniformDesc(const char* name, GLenum type) : type(type), name(name)
	{
		
	};

	const char* name;
	GLenum type;
};

class ShaderProgram : public RemovableObject
{
public:
	ShaderProgram(std::map<const char*,unsigned int> attributes);
	~ShaderProgram();
	void loadShaderFromString(GLenum shader_type, const char* source, int length);
	void createAndLinkProgram();
	void bind();
	void unbind();
	GLuint getProgram();
	const std::map<const char*, unsigned int> getAttributes() const;
	std::vector<UniformDesc> getUniforms(GLenum typeFilter = -1);
	GLint getUniformLocation(const char* name);
	GLint getAttributeLocation(const char* name);

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

	void setVertexAttrib1f(const char* name, GLfloat x);
	void setVertexAttrib2f(const char* name, GLfloat x, GLfloat y);
	void setVertexAttrib2fv(const char* name, const GLfloat* v);
	void setVertexAttrib3f(const char* name, GLfloat x, GLfloat y, GLfloat z);
	void setVertexAttrib3fv(const char* name, const GLfloat* v);
	void setVertexAttrib4f(const char* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	void setVertexAttrib4fv(const char* name, const GLfloat* v);

#ifdef GL_OPENGL
	void setVertexAttrib1d(const char* name, GLdouble x);
	void setVertexAttrib1dv(const char* name, const GLdouble* v);
	void setVertexAttrib1fv(const char* name, const GLfloat* v);
	void setVertexAttrib1s(const char* name, GLshort x);
	void setVertexAttrib1sv(const char* name, const GLshort* v);
	void setVertexAttrib2d(const char* name, GLdouble x, GLdouble y);
	void setVertexAttrib2dv(const char* name, const GLdouble* v);
	void setVertexAttrib2s(const char* name, GLshort x, GLshort y);
	void setVertexAttrib2sv(const char* name, const GLshort* v);
	void setVertexAttrib3d(const char* name, GLdouble x, GLdouble y, GLdouble z);
	void setVertexAttrib3dv(const char* name, const GLdouble* v);
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
	void setVertexAttrib4s(const char* name, GLshort x, GLshort y, GLshort z, GLshort w);
	void setVertexAttribPointer(const char* name, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
#endif

private:
	enum ShaderType{VERTEX_SHADER,FRAGMENT_SHADER,/*GEOMETRY_SHADER*/};
	std::map<const char*, unsigned int> attributes_;
	GLuint program_;
	GLuint shaders_[2];
};

inline GLuint ShaderProgram::getProgram()
{
	return program_;
}

inline void ShaderProgram::bind()
{
	glUseProgram(program_);
}

inline void ShaderProgram::unbind()
{
	glUseProgram(0);
}

inline const std::map<const char*, unsigned int> ShaderProgram::getAttributes() const
{
	return attributes_;
}

inline GLint ShaderProgram::getUniformLocation(const char* name)
{
	return glGetUniformLocation(program_, name);
}

inline GLint ShaderProgram::getAttributeLocation(const char* name)
{
	return glGetAttribLocation(program_, name);
}

inline void ShaderProgram::setUniform1f(const char* name, GLfloat v0)
{
	GLint location = getUniformLocation(name);
	bind();
	glUniform1f(location, v0);
	unbind();
}

inline void ShaderProgram::setUniform1fv(const char* name, GLsizei count, const GLfloat* value)
{
	GLint location = getUniformLocation(name);
	bind();
	glUniform1fv(location, count, value);
	unbind();
}

inline void ShaderProgram::setUniform1i(const char* name, GLint v0)
{
	GLint location = getUniformLocation(name);
	bind();
	glUniform1i(location, v0);
	unbind();
}

inline void ShaderProgram::setUniform1iv(const char* name, GLsizei count, const GLint* value)
{
	GLint location = getUniformLocation(name);
	bind();
	glUniform1iv(location, count, value);
	unbind();
}

inline void ShaderProgram::setUniform2f(const char* name, GLfloat v0, GLfloat v1)
{
	GLint location = getUniformLocation(name);
	bind();
	glUniform2f(location, v0, v1);
	unbind();
}

inline void ShaderProgram::setUniform2fv(const char* name, GLsizei count, const GLfloat* value)
{
	GLint location = getUniformLocation(name);
	bind();
	glUniform2fv(location, count, value);
	unbind();
}

inline void ShaderProgram::setUniform2i(const char* name, GLint v0, GLint v1)
{
	GLint location = getUniformLocation(name);
	bind();
	glUniform2i(location, v0, v1);
	unbind();
}

inline void ShaderProgram::setUniform2iv(const char* name, GLsizei count, const GLint* value)
{
	GLint location = getUniformLocation(name);
	bind();
	glUniform2iv(location, count, value);
	unbind();
}

inline void ShaderProgram::setUniform3f(const char* name, GLfloat v0, GLfloat v1, GLfloat v2)
{
	GLint location = getUniformLocation(name);
	bind();
	glUniform3f(location, v0, v1, v2);
	unbind();
}

inline void ShaderProgram::setUniform3fv(const char* name, GLsizei count, const GLfloat* value)
{
	GLint location = getUniformLocation(name);
	bind();
	glUniform3fv(location, count, value);
	unbind();
}

inline void ShaderProgram::setUniform3i(const char* name, GLint v0, GLint v1, GLint v2)
{
	GLint location = getUniformLocation(name);
	bind();
	glUniform3i(location, v0, v1, v2);
	unbind();
}

inline void ShaderProgram::setUniform3iv(const char* name, GLsizei count, const GLint* value)
{
	GLint location = getUniformLocation(name);
	bind();
	glUniform3iv(location, count, value);
	unbind();
}

inline void ShaderProgram::setUniform4f(const char* name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	GLint location = getUniformLocation(name);
	bind();
	glUniform4f(location, v0, v1, v2, v3);
	unbind();
}

inline void ShaderProgram::setUniform4fv(const char* name, GLsizei count, const GLfloat* value)
{
	GLint location = getUniformLocation(name);
	bind();
	glUniform4fv(location, count, value);
	unbind();
}

inline void ShaderProgram::setUniform4i(const char* name, GLint v0, GLint v1, GLint v2, GLint v3)
{
	GLint location = getUniformLocation(name);
	bind();
	glUniform4i(location, v0, v1, v2, v3);
	unbind();
}

inline void ShaderProgram::setUniform4iv(const char* name, GLsizei count, const GLint* value)
{
	GLint location = getUniformLocation(name);
	bind();
	glUniform4iv(location, count, value);
	unbind();
}

inline void ShaderProgram::setUniformMatrix2fv(const char* name, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	GLint location = getUniformLocation(name);
	bind();
	glUniformMatrix2fv(location, count, transpose, value);
	unbind();
}

inline void ShaderProgram::setUniformMatrix3fv(const char* name, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	GLint location = getUniformLocation(name);
	bind();
	glUniformMatrix3fv(location, count, transpose, value);
	unbind();
}

inline void ShaderProgram::setUniformMatrix4fv(const char* name, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	GLint location = getUniformLocation(name);
	bind();
	glUniformMatrix4fv(location, count, transpose, value);
	unbind();
}

/* ATTRIBUTES */
inline void ShaderProgram::setVertexAttrib1f(const char* name, GLfloat x)
{
	GLint location = getAttributeLocation(name);
	glVertexAttrib1f(location, x);
}

inline void ShaderProgram::setVertexAttrib2f(const char* name, GLfloat x, GLfloat y)
{
	GLint location = getAttributeLocation(name);
	glVertexAttrib2f(location, x, y);
}

inline void ShaderProgram::setVertexAttrib2fv(const char* name, const GLfloat* v)
{
	GLint location = getAttributeLocation(name);
	glVertexAttrib2fv(location, v);
}

inline void ShaderProgram::setVertexAttrib3f(const char* name, GLfloat x, GLfloat y, GLfloat z)
{
	GLint location = getAttributeLocation(name);
	glVertexAttrib3f(location, x, y, z);
}

inline void ShaderProgram::setVertexAttrib3fv(const char* name, const GLfloat* v)
{
	GLint location = getAttributeLocation(name);
	glVertexAttrib3fv(location, v);
}

#ifdef GL_OPENGL
inline void ShaderProgram::setVertexAttrib1d(const char* name, GLdouble x)
{
	GLint location = getAttributeLocation(name);
	glVertexAttrib1d(location, x);
}

inline void ShaderProgram::setVertexAttrib1dv(const char* name, const GLdouble* v)
{
	GLint location = getAttributeLocation(name);
	glVertexAttrib1dv(location, v);
}


inline void ShaderProgram::setVertexAttrib1fv(const char* name, const GLfloat* v)
{
	GLint location = getAttributeLocation(name);
	glVertexAttrib1fv(location, v);
}

inline void ShaderProgram::setVertexAttrib1s(const char* name, GLshort x)
{
	GLint location = getAttributeLocation(name);
	glVertexAttrib1s(location, x);
}

inline void ShaderProgram::setVertexAttrib1sv(const char* name, const GLshort* v)
{
	GLint location = getAttributeLocation(name);
	glVertexAttrib1sv(location, v);
}

inline void ShaderProgram::setVertexAttrib2d(const char* name, GLdouble x, GLdouble y)
{
	GLint location = getAttributeLocation(name);
	glVertexAttrib2d(location, x,y);
}

inline void ShaderProgram::setVertexAttrib2dv(const char* name, const GLdouble* v)
{
	GLint location = getAttributeLocation(name);
	glVertexAttrib2dv(location, v);
}

inline void ShaderProgram::setVertexAttrib2s(const char* name, GLshort x, GLshort y)
{
	GLint location = getAttributeLocation(name);
	glVertexAttrib2s(location, x, y);
}

inline void ShaderProgram::setVertexAttrib2sv(const char* name, const GLshort* v)
{
	GLint location = getAttributeLocation(name);
	glVertexAttrib2sv(location, v);
}

inline void ShaderProgram::setVertexAttrib3d(const char* name, GLdouble x, GLdouble y, GLdouble z)
{
	GLint location = getAttributeLocation(name);
	glVertexAttrib3d(location, x, y, z);
}

inline void ShaderProgram::setVertexAttrib3dv(const char* name, const GLdouble* v)
{
	GLint location = getAttributeLocation(name);
	glVertexAttrib3dv(location, v);
}

inline void ShaderProgram::setVertexAttrib3s(const char* name, GLshort x, GLshort y, GLshort z)
{
	GLint location = getAttributeLocation(name);
	glVertexAttrib3s(location, x, y, z);
}

inline void ShaderProgram::setVertexAttrib3sv(const char* name, const GLshort* v)
{
	GLint location = getAttributeLocation(name);
	glVertexAttrib3sv(location, v);
}

inline void ShaderProgram::setVertexAttrib4bv(const char* name, const GLbyte* v)
{
	GLint location = getAttributeLocation(name);
	glVertexAttrib4bv(location, v);
}

inline void ShaderProgram::setVertexAttrib4iv(const char* name, const GLint* v)
{
	GLint location = getAttributeLocation(name);
	glVertexAttrib4iv(location,v);
}

inline void ShaderProgram::setVertexAttrib4sv(const char* name, const GLshort* v)
{
	GLint location = getAttributeLocation(name);
	glVertexAttrib4sv(location, v);
}

inline void ShaderProgram::setVertexAttrib4ub(const char* name, GLubyte x, GLubyte y, GLubyte z, GLubyte w)
{
	GLint location = getAttributeLocation(name);
	glVertexAttrib4Nub(location, x, y, z, w);
}

inline void ShaderProgram::setVertexAttrib4ubv(const char* name, const GLubyte* v)
{
	GLint location = getAttributeLocation(name);
	glVertexAttrib4ubv(location, v);
}

inline void ShaderProgram::setVertexAttrib4uiv(const char* name, const GLuint* v)
{
	GLint location = getAttributeLocation(name);
	glVertexAttrib4uiv(location, v);	
}

inline void ShaderProgram::setVertexAttrib4usv(const char* name, const GLushort* v)
{
	GLint location = getAttributeLocation(name);
	glVertexAttrib4usv(location, v);
}

inline void ShaderProgram::setVertexAttrib4d(const char* name, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
	GLuint location = getAttributeLocation(name);
	glVertexAttrib4d(location, x, y, z, w);
}

inline void ShaderProgram::setVertexAttrib4dv(const char* name, const GLdouble* v)
{
	GLuint location = getAttributeLocation(name);
	glVertexAttrib4dv(location, v);
}

inline void ShaderProgram::setVertexAttrib4s(const char* name, GLshort x, GLshort y, GLshort z, GLshort w)
{
	GLuint location = getAttributeLocation(name);
	glVertexAttrib4s(location, x, y, z, w);
}

inline void ShaderProgram::setVertexAttribPointer(const char* name, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer)
{
	GLuint location = getAttributeLocation(name);
	glVertexAttribPointer(location, size, type, normalized, stride, pointer);
}
#endif

#endif