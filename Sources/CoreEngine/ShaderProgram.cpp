
#include <iostream>
#include <vector>

#include "../Debug/Logger.h"
#include "../Extras/GLUtils.h"
#include "ShaderProgram.h"
#include "Utils.h"

ShaderProgram::ShaderProgram(std::map<const char*, unsigned int> attributes) :attributes_(attributes)
{
	shaders_[VERTEX_SHADER] = 0;	shaderSources[VERTEX_SHADER] = 0;
	shaders_[FRAGMENT_SHADER] = 0;	shaderSources[FRAGMENT_SHADER] = 0;
	//_shaders[GEOMETRY_SHADER] = 0;
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(program_);
	program_ = -1;

	if (shaderSources[VERTEX_SHADER] != NULL)
		delete shaderSources[VERTEX_SHADER];
	if (shaderSources[FRAGMENT_SHADER] != NULL)
		delete shaderSources[FRAGMENT_SHADER];
}

void ShaderProgram::loadShaderFromString(GLenum shader_type, const char* source, int length)
{	
	GLuint shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &source, &length);
	glCompileShader(shader);
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		
		if (infoLogLength > 0)
		{
			GLchar* infoLog = new GLchar[infoLogLength];
			glGetShaderInfoLog(shader, infoLogLength, NULL, infoLog);
			Logger::PrintError("Shader compilation log: %s\n", infoLog);

			delete[] infoLog;
		}
		else
		{
			Logger::PrintError("Shader compilation error\n");
		}

		glDeleteShader(shader);
		return;
	}

	if (shader_type == GL_VERTEX_SHADER)
	{
		shaders_[VERTEX_SHADER] = shader;
		shaderSources[VERTEX_SHADER] = new char[length];
		sourceLengths[VERTEX_SHADER] = length;
		memcpy(shaderSources[VERTEX_SHADER], source, length);
	}
	else if (shader_type == GL_FRAGMENT_SHADER)
	{
		shaders_[FRAGMENT_SHADER] = shader;
		shaderSources[FRAGMENT_SHADER] = new char[length];
		sourceLengths[FRAGMENT_SHADER] = length;
		memcpy(shaderSources[FRAGMENT_SHADER], source, length);
	}
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
		if (infoLogLength > 1)
		{
			GLchar* infoLog = new GLchar[infoLogLength];
			glGetProgramInfoLog(program_, infoLogLength, NULL, infoLog);
			Logger::PrintError("Program linking log: %s\n", infoLog);

			delete[] infoLog;
		}
		else
		{
			Logger::PrintError("Program linking error\n");
		}

		glDeleteProgram(program_);
	}

	glDeleteShader(shaders_[VERTEX_SHADER]);
	glDeleteShader(shaders_[FRAGMENT_SHADER]);
	//glDeleteShader(_shaders[GEOMETRY_SHADER]);
}


std::vector<UniformDesc> ShaderProgram::getUniforms(GLenum typeFilter) const
{
	std::vector<UniformDesc> uniforms;

	int total = -1;
	glGetProgramiv(getProgram(), GL_ACTIVE_UNIFORMS, &total);
	for (int i = 0; i < total; i++)
	{
		int name_len = -1, num = -1;
		GLenum type = GL_ZERO;
		char name[100];
		glGetActiveUniform(getProgram(), GLuint(i), sizeof(name)-1, &name_len, &num, &type, name);
		name[name_len] = 0;

		if (typeFilter == -1 || typeFilter == type)
			uniforms.push_back(UniformDesc(name, type));
	}

	return uniforms;
}