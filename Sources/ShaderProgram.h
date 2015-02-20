
#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "GL_LIBS.h"
#include "smart_pointer.h"

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

#endif