
#include <iostream>
#include <vector>

#include "ShaderProgram.h"
#include "Utils.h"

ShaderProgram::ShaderProgram()
{
	_nShaders = 0;
	_shaders[VERTEX_SHADER] = 0;
	_shaders[FRAGMENT_SHADER] = 0;
	//_shaders[GEOMETRY_SHADER] = 0;
}

ShaderProgram::~ShaderProgram()
{
	deleteProgram();
	if (_shaders[VERTEX_SHADER] != 0)
		glDeleteShader(_shaders[VERTEX_SHADER]);
	if (_shaders[FRAGMENT_SHADER] != 0)
		glDeleteShader(_shaders[FRAGMENT_SHADER]);
// 	if (_shaders[GEOMETRY_SHADER] != 0)
// 		glDeleteShader(_shaders[GEOMETRY_SHADER]);
}

void ShaderProgram::loadShaderFromString(GLenum shader_type, const char* source)
{
	GLuint shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &source, NULL);

	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* infoLog = new GLchar[infoLogLength];
		glGetShaderInfoLog(shader, infoLogLength, NULL, infoLog);
		std::cerr << "Shader compile log: " << infoLog << std::endl;
		delete[] infoLog;
		return;
	}
	_nShaders++;

	if (shader_type == GL_VERTEX_SHADER)
		_shaders[VERTEX_SHADER] = shader;
	else if (shader_type == GL_FRAGMENT_SHADER)
		_shaders[FRAGMENT_SHADER] = shader;
// 	else if (shader_type == GL_GEOMETRY_SHADER)
// 		_shaders[GEOMETRY_SHADER] = shader;
	else
	{
		std::cerr << "Unknown type of shader";
		exit(0);
	}
}

void ShaderProgram::loadShaderFromFile(GLenum shader_type, const char* filename)
{
	loadShaderFromString(shader_type, loadFile(filename));
}

void ShaderProgram::createAndLinkProgram()
{
	_program = glCreateProgram();

	if (_shaders[VERTEX_SHADER] != 0)
		glAttachShader(_program, _shaders[VERTEX_SHADER]);
	if (_shaders[FRAGMENT_SHADER] != 0)
		glAttachShader(_program, _shaders[FRAGMENT_SHADER]);
// 	if (_shaders[GEOMETRY_SHADER] != 0)
// 		glAttachShader(_program, _shaders[GEOMETRY_SHADER]);

	glLinkProgram(_program);

	GLint status;
	glGetShaderiv(_program, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* infoLog = new GLchar[infoLogLength];
		glGetProgramInfoLog(_program, infoLogLength, NULL, infoLog);
		std::cerr << "Program link log: " << infoLog << std::endl;
		delete[] infoLog;
	}

	glDeleteShader(_shaders[VERTEX_SHADER]);
	glDeleteShader(_shaders[FRAGMENT_SHADER]);
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