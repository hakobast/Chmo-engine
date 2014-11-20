#include <GL\glut.h>
#include <iostream>
#include "Renderer.h"
#include "Transform.h"

Renderer::~Renderer()
{
	cout << "Renderer:: ~~~deleted~~~ " << endl;
}

void Renderer::Init()
{
	cout << "Renderer: Init(): " << endl;
}

void Renderer::Update()
{
	//cout << "Renderer: Updated(): " << endl;
	
	glPushMatrix();
	transform->applyTransformation();

	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	glVertex3f(1.0f, 0.0f, -20.0f);
	glVertex3f(0.0f, 1.0f, -20.0f);
	glVertex3f(-1.0f, 0.0f, -20.0f);
	glEnd();

	glPopMatrix();
}