#version 120

uniform mat4 ModelViewProjectionMatrix;
uniform mat4 ModelViewMatrix;

uniform int count;
uniform float size;
uniform float time;
uniform float speed;

attribute vec4 InVertex;
attribute float index;

#define DEG_TO_RAD 3.141592/180

void main()
{
	vec4 pos = InVertex;
	pos.x = (speed/10.0)*time*cos(index*360.0/count*DEG_TO_RAD);
	pos.y = (speed/10.0)*time*sin(index*360.0/count*DEG_TO_RAD);
	
	gl_Position = ModelViewProjectionMatrix*pos;
	gl_PointSize = size;
}