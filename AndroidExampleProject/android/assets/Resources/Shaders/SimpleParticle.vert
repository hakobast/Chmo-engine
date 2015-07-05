#version 100

uniform mat4 ModelViewProjectionMatrix;
uniform mat4 ModelViewMatrix;

uniform float count;
uniform float size;
uniform float time;
uniform float speed;

attribute vec4 InVertex;
attribute float index;

#define DEG_TO_RAD 3.141592/180.0

void main()
{
	vec4 pos = InVertex;
	
	float angleInRads =  index*360.0/count*DEG_TO_RAD;
	pos.x = (speed/10.0)*time*cos(angleInRads);
	pos.y = (speed/10.0)*time*sin(angleInRads);
	
	gl_Position = ModelViewProjectionMatrix*pos;
	gl_PointSize = size;
}