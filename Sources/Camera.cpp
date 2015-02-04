
#include "GL_LIBS.h"

#include "Camera.h"
#include "ScreenSystem.h"

void Camera::Create()
{

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

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (height == 0)
		height = 1;
	GLfloat ratio = (GLfloat)width / (GLfloat)height;

	if (projectionMode_ == Orthographic)
	{
		GLfloat range = 10.0f;
		if (width < height)
			glOrtho(-range, range, -range / ratio, range / ratio, -range, range);
		else
			glOrtho(-range*ratio, range*ratio, -range, range, -range, range);
	}
	else
	{
		gluPerspective(fovy_, ratio, 1.0f, 1000.0f);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//printf("RESIZE %d,%d\n", width, height);
}