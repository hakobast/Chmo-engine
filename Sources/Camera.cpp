
#include "GL_LIBS.h"

#include "Camera.h"
#include "ScreenSystem.h"

Camera* Camera::main = NULL;

void Camera::Create()
{
	if (main == NULL)
		main = this;
}

void Camera::Init()
{
	ApplyCameraChanges();
}

void Camera::Update()
{
	
}

void Camera::OnEnable()
{
	ApplyCameraChanges();
}

void Camera::ApplyTransformation()
{
	Transform* tr = getTransform();
	Vector3 Up = tr->Up();
	Vector3 Forward = tr->Forward();
	Vector3 Right = Up.cross(Forward);

	Matrix4 transpose;
	transpose[0] = Right[0];
	transpose[4] = Right[1]; 
	transpose[8] = Right[2];
	transpose[12] = 0.0f;

	transpose[1] = Up[0];
	transpose[5] = Up[1];
	transpose[9] = Up[2];
	transpose[13] = 0.0f;

	transpose[2] = Forward[0];
	transpose[6] = Forward[1];
	transpose[10] = Forward[2];
	transpose[14] = 0.0f;

	transpose[3] = 0.0f;
	transpose[7] = 0.0f;
	transpose[11] = 0.0f;
	transpose[15] = 1.0f;

	glMultMatrixf(&transpose[0]);

	glTranslatef(-tr->Location[0], -tr->Location[1], -tr->Location[2]);
}

void Camera::ApplyCameraChanges()
{
	int width = ScreenSystem::getWidth();
	int height = ScreenSystem::getHeight();

	if (height == 0)
		height = 1;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	GLfloat ratio = (GLfloat)width / (GLfloat)height;

	if (projectionMode_ == ORTHOGRAPHIC)
	{
		if (width <= height)
			glOrtho(-_orthoSize, _orthoSize, -_orthoSize / ratio, _orthoSize / ratio, _zNear, _zFar);
		else
			glOrtho(-_orthoSize*ratio, _orthoSize*ratio, -_orthoSize, _orthoSize, _zNear, _zFar);
	}
	else
	{
		gluPerspective(_fovy, ratio, _zNear, _zFar);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//printf("RESIZE %d,%d\n", width, height);
}