#include <GL\glut.h>
#include <iostream>
#include "SpriteRenderer.h"
#include "Transform.h"

GLfloat meterPerPixel;
GLfloat w_range, h_range;

SpriteRenderer::~SpriteRenderer()
{
	cout << "SpriteRenderer:: ~~~deleted~~~ " << endl;
}

void SpriteRenderer::Create()
{
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
	//cout << "Renderer: Updated():" << endl;
	if (texture == NULL)
		return;

	getTransform()->applyTransformation();

	glEnable(GL_TEXTURE_2D);

	texture->bindTexture();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor4fv(color[0]);

	glBegin(GL_QUADS);
	{
		glTexCoord2fv((*texture)[frame][0]);
		glVertex3f(-w_range, -h_range, 0.0f);

		glTexCoord2fv((*texture)[frame][2]);
		glVertex3f(w_range, -h_range, 0.0f);

		glTexCoord2fv((*texture)[frame][4]);
		glVertex3f(w_range, h_range, 0.0f);

		glTexCoord2fv((*texture)[frame][6]);
		glVertex3f(-w_range, h_range, 0.0f);
	}
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void SpriteRenderer::setTexture(Texture2D* txt, int frame)
{
	texture = txt;
	this->frame = frame;

	//make pixel perfect
	GLfloat ratio = texture->width / texture->height;
	if (texture->width <= texture->height)
	{
		w_range = meterPerPixel*texture->width;
		h_range = meterPerPixel*texture->height / ratio;
	}
	else
	{
		w_range = meterPerPixel*texture->width*ratio;
		h_range = meterPerPixel*texture->height;
	}
}