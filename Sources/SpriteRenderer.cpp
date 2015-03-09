
#include "GL_LIBS.h"

#include <iostream>
#include "SpriteRenderer.h"
#include "Transform.h"
#include "ScreenSystem.h"
#include "ShaderProgram.h"

GLfloat meterPerPixel;
GLfloat w_range = 1, h_range = 1;

SpriteRenderer::~SpriteRenderer()
{
	cout << "SpriteRenderer:: ~~~deleted~~~ " << endl;
}

smart_pointer<ShaderProgram> shaderProgram;

void SpriteRenderer::Create()
{
	//TODO move this calculation to Camera
	//GLfloat h = 2 * tan(45.0f*(3.1413f / 180) / 2);
	//GLfloat w = ((GLfloat)800 / 600)*h;

	GLfloat width = ScreenSystem::getWidth();
	GLfloat height = ScreenSystem::getHeight();

	meterPerPixel = 1.0f/100.0f;

	shaderProgram = smart_pointer<ShaderProgram>(new ShaderProgram());
	shaderProgram->loadShaderFromFile(GL_VERTEX_SHADER_ARB, "C:/Program Files (x86)/OpenGL Shader Designer/My/Diffuse.vert");
	shaderProgram->loadShaderFromFile(GL_FRAGMENT_SHADER_ARB, "C:/Program Files (x86)/OpenGL Shader Designer/My/Diffuse.frag");
	shaderProgram->createAndLinkProgram();
}

void SpriteRenderer::Init()
{
	setTextureFrame(frame);

	getMainMaterial()->color_ambient.set(1.0f, 1.0f, 1.0f);
	getMainMaterial()->color_diffuse.set(1.0f, 1.0f, 1.0f);
	getMainMaterial()->color_specular.set(1.0f, 1.0f, 1.0f);
	getMainMaterial()->shininess = 0.0f;

}

float time = 0.0f;
void SpriteRenderer::Update()
{
	getTransform()->applyTransformation();
	
	smart_pointer<Texture2D>& mainTexture = getMainTexture();
	if (mainTexture.isEmpty())
		return;
	
	getMainMaterial()->bind();
	shaderProgram->bind();

	//int my_vec3_location = glGetUniformLocationARB(shaderProgram->getProgram(), "mainColor");
	//glUniform4fARB(my_vec3_location, 1.0f, 1.0f, 1.0f, 1.0f);

	//int time_loc = glGetUniformLocationARB(shaderProgram->getProgram(), "time");
	//glUniform1fARB(time_loc, time);

	//time += 0.01f;

	w_range = 3.0f;
	h_range = 3.0f;
	glBegin(GL_QUADS);
	{
		glNormal3f(0.0f, 0.0f, 1.0f);

		glTexCoord2fv((*mainTexture)[frame][0]);glVertex3f(-w_range, -h_range, 0.0f);

		glTexCoord2fv((*mainTexture)[frame][2]);glVertex3f(w_range, -h_range, 0.0f);

		glTexCoord2fv((*mainTexture)[frame][4]);glVertex3f(w_range, h_range, 0.0f);

		glTexCoord2fv((*mainTexture)[frame][6]);glVertex3f(-w_range, h_range, 0.0f);
	}
	glEnd();

	shaderProgram->unbind();
	getMainMaterial()->unbind();
}

void SpriteRenderer::setTextureFrame(int frame)
{
	this->frame = frame;
	
	smart_pointer<Texture2D>& txt = getMainTexture();
	
	TextureRegion& region = txt->getTextureRegion(frame);
	float width = (region.u_v[2] - region.u_v[0])*txt->width;
	float height = (region.u_v[5] - region.u_v[1])*txt->height;
	
	//printf("Width: %0.0f Height: %0.0f\n", width, height);
	if (!txt.isEmpty())
	{
		w_range = meterPerPixel*width;
		h_range = meterPerPixel*height;
		//printf("w_range: %f h_range: %f\n", w_range, h_range);
		//GLfloat ratio = (GLfloat)width / height;
		//
		//if (width <= height)
		//{
		//	w_range = meterPerPixel*width*ratio;
		//	h_range = meterPerPixel*height;
		//}
		//else
		//{
		//	w_range = meterPerPixel*width;;
		//	h_range = meterPerPixel*height/ratio;
		//}
			
		//std::cout << "RATIO: " << ratio << std::endl;
		//std::cout << "W: " << w_range << " H: " << h_range << std::endl;
	}
}
