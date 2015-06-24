#version 110

uniform mat4 ModelViewProjectionMatrix;
uniform mat4 ModelViewMatrix;

attribute vec4 InVertex;

void main()
{
	gl_Position = ModelViewProjectionMatrix*InVertex;
}