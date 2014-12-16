#include <GL\glut.h>
#include <iostream>
#include "SpriteRenderer.h"
#include "Transform.h"

GLfloat meterPerPixel;
GLfloat w_range = 1, h_range = 1;

SpriteRenderer::~SpriteRenderer()
{
	cout << "SpriteRenderer:: ~~~deleted~~~ " << endl;
}

void SpriteRenderer::Create()
{
	renderSystem->sortComponents();

	//TODO move this calculation to Camera
	GLfloat h = 2 * tan(45.0f*(3.1413f / 180) / 2);
	GLfloat w = ((GLfloat)800 / 600)*h;

	meterPerPixel = w / 800.0f;
}

void SpriteRenderer::Init()
{

}

void SpriteRenderer::Update()
{
	smart_pointer<Texture2D>& mainTexture = getMainTexture();

	if (mainTexture.isEmpty())
		return;
	
	getTransform()->applyTransformation();

	glEnable(GL_TEXTURE_2D);

	getMainMaterial()->apply();

	glBegin(GL_QUADS);
	{
		glNormal3f(0.0f, 0.0f, 1.0f);
		
		glTexCoord2fv((*mainTexture)[frame][0]);
		glVertex3f(-w_range, -h_range, 0.0f);

		glTexCoord2fv((*mainTexture)[frame][2]);
		glVertex3f(w_range, -h_range, 0.0f);

		glTexCoord2fv((*mainTexture)[frame][4]);
		glVertex3f(w_range, h_range, 0.0f);

		glTexCoord2fv((*mainTexture)[frame][6]);
		glVertex3f(-w_range, h_range, 0.0f);
	}
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void SpriteRenderer::setTextureFrame(int frame)
{
	this->frame = frame;
	w_range = 0.3f;
	h_range = 0.3f;
	/*diffuseMaterial->texture_diffuse = txt;

	this->frame = frame;

	//make pixel perfect
	GLfloat ratio = txt->width / txt->height;
	if (txt->width <= txt->height)
	{
		w_range = meterPerPixel*txt->width;
		h_range = meterPerPixel*txt->height / ratio;
	}
	else
	{
		w_range = meterPerPixel*txt->width*ratio;
		h_range = meterPerPixel*txt->height;
	}*/
}