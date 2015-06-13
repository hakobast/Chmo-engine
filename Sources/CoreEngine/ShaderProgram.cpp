
#include <iostream>
#include <vector>

#include "../Debug/Logger.h"
#include "../Extras/GLUtils.h"
#include "ShaderProgram.h"
#include "Utils.h"

ShaderProgram::ShaderProgram(std::map<const char*, unsigned int> attributes) :attributes_(attributes)
{
	shaders_[VERTEX_SHADER] = 0;
	shaders_[FRAGMENT_SHADER] = 0;
	//_shaders[GEOMETRY_SHADER] = 0;
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(program_);
	program_ = -1;

// 	if (shaders_[VERTEX_SHADER] != 0)
// 		glDeleteShader(shaders_[VERTEX_SHADER]);
// 	if (shaders_[FRAGMENT_SHADER] != 0)
// 		glDeleteShader(shaders_[FRAGMENT_SHADER]);
// 	if (_shaders[GEOMETRY_SHADER] != 0)
// 		glDeleteShader(_shaders[GEOMETRY_SHADER]);
}

void ShaderProgram::loadShaderFromString(GLenum shader_type, const char* source, int length)
{
	GLint lengths[] = { length };
	
	GLuint shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &source, lengths);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* infoLog = new GLchar[infoLogLength];
		glGetShaderInfoLog(shader, infoLogLength, NULL, infoLog);
		Logger::PrintError("Shader compile log: %s", infoLog);
		
		delete[] infoLog;
		return;
	}

	if (shader_type == GL_VERTEX_SHADER)
		shaders_[VERTEX_SHADER] = shader;
	else if (shader_type == GL_FRAGMENT_SHADER)
		shaders_[FRAGMENT_SHADER] = shader;
// 	else if (shader_type == GL_GEOMETRY_SHADER)
// 		_shaders[GEOMETRY_SHADER] = shader;
}

void ShaderProgram::createAndLinkProgram()
{
	program_ = glCreateProgram();
	
	for (std::map<const char*, unsigned int>::iterator it = attributes_.begin(); it != attributes_.end(); it++)
		glBindAttribLocation(program_, it->second, it->first);

	if (shaders_[VERTEX_SHADER] != 0)
		glAttachShader(program_, shaders_[VERTEX_SHADER]);
	if (shaders_[FRAGMENT_SHADER] != 0)
		glAttachShader(program_, shaders_[FRAGMENT_SHADER]);
// 	if (_shaders[GEOMETRY_SHADER] != 0)
// 		glAttachShader(_program, _shaders[GEOMETRY_SHADER]);

	glLinkProgram(program_);

	GLint status;
	glGetProgramiv(program_, GL_LINK_STATUS, &status);

	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* infoLog = new GLchar[infoLogLength];
		glGetProgramInfoLog(program_, infoLogLength, NULL, infoLog);
		Logger::PrintError("Program link log: %s", infoLog);
		delete[] infoLog;
	}

	glDeleteShader(shaders_[VERTEX_SHADER]);
	glDeleteShader(shaders_[FRAGMENT_SHADER]);
	//glDeleteShader(_shaders[GEOMETRY_SHADER]);
}


std::vector<UniformDesc> ShaderProgram::getUniforms(GLenum typeFilter)
{
	std::vector<UniformDesc> uniforms;

	int total = -1;
	glGetProgramiv(getProgram(), GL_ACTIVE_UNIFORMS, &total);
	for (int i = 0; i < total; i++)
	{
		int name_len = -1, num = -1;
		GLenum type = GL_ZERO;
		char name[100];
		glGetActiveUniform(getProgram(), GLuint(i), sizeof(name)-1,
			&name_len, &num, &type, name);
		name[name_len] = 0;

		if (typeFilter == -1 || typeFilter == type)
			uniforms.push_back(UniformDesc(name, type));
	}

	return uniforms;
}