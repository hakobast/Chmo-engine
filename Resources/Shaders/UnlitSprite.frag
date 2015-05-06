
uniform vec4 Color;
uniform sampler2D mainTexture;

varying vec2 OutTexCoord0;

void main()
{
//	vec4 c = vec4(1.0,1.0,1.0,1.0);
//	gl_FragColor = texture2D(mainTexture,gl_TexCoord[0].st)*Color;
	gl_FragColor = texture2D(mainTexture,OutTexCoord0)*Color;
}
