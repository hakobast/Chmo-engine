
#include "Light.h"

void Light::Create()
{
	v = new GLfloat[4];
}

void Light::Init()
{
/*
	glEnable(GL_LIGHT0 + _light);
	setLightType(DIRECTIONAL);
	setAmbient(_color_ambient);
	setDiffuse(_color_diffuse);*/
}

void Light::Update()
{
	
	glPushMatrix();
		getTransform()->applyTransformation();
		glDisable(GL_LIGHTING);
		glColor3f(1.0f, 0.0f, 1.0f);
		glutSolidCone(0.1f, 0.2f, 10.0f, 10.0f);
		glEnable(GL_LIGHTING);
		
		switch (_type)
		{
		case DIRECTIONAL:
		{
			Vector3 dir = getTransform()->Forward();
			v[0] = dir.x; v[1] = dir.y; v[2] = dir.z; v[3] = 0.0f;
			glLightfv(GL_LIGHT0 + _light, GL_POSITION, v);
			break;
		}
		case POSITIONAL:
		{
			v[0] = 0.0f; v[1] = 0.0f; v[2] = 0.0f; v[3] = 1.0f;
			glLightfv(GL_LIGHT0 + _light, GL_POSITION, v);
			break;
		}
		case SPOT:
		{
			v[0] = 0.0f; v[1] = 0.0f; v[2] = 0.0f; v[3] = 1.0f;
			glLightfv(GL_LIGHT0 + _light, GL_POSITION, v);

			Vector3 dir = getTransform()->Forward();
			v[0] = -dir.x; v[1] = -dir.y; v[2] = -dir.z; v[3] = 0.0f;
			glLightfv(GL_LIGHT0 + _light, GL_SPOT_DIRECTION, v);
		}
			break;
		}
	glPopMatrix();
}

void Light::OnEnable()
{
	glEnable(GL_LIGHT0 + _light);
}

void Light::OnDisable()
{
	glDisable(GL_LIGHT0 + _light);
}

void Light::OnDestroy()
{
	delete[] v;
}