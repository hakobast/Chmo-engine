#version 100

uniform vec4 Color;
uniform sampler2D mainTexture;
uniform sampler2D secondTexture;


varying vec2 OutTexCoord0;

void main()
{	
	gl_FragColor = texture2D(mainTexture, OutTexCoord0)*Color;
	//gl_FragColor = texture2D(secondTexture, OutTexCoord0)*Color;
	
	
	
	//gl_FragColor = Color;
	//gl_FragColor = vec4(1.0,1.0,0.0,1.0);
}