#version 100

uniform mat4 ModelViewProjectionMatrix;
uniform mat4 ModelViewMatrix;

attribute vec4 InVertex;
attribute vec2 InTexCoord0;
attribute vec3 InNormal;

varying vec2 OutTexCoord0;

void main()
{
//	gl_TexCoord[0] = gl_MultiTexCoord0;
//	gl_Position = gl_ModelViewProjectionMatrix*gl_Vertex;
	
//	vec4 pos = ModelViewProjectionMatrix*InVertex;
	gl_Position = ModelViewProjectionMatrix*InVertex;
	OutTexCoord0 = InTexCoord0;
	
	//vec3 normal = vec3(ModelViewMatrix * vec4(InNormal, 0.0));
}