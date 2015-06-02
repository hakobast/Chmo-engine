
#include "Camera.h"
#include "../CoreEngine/LIBS.h"
#include "../Systems/ScreenSystem.h"
#include "../Debug/Logger.h"

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

void Camera::OnDestroy()
{
	if (main == this)
		main = NULL;
}

void Camera::ApplyCameraChanges()
{
	int width = ScreenSystem::getWidth();
	int height = ScreenSystem::getHeight();

	if (height == 0)
		height = 1;

	glViewport(0, 0, width, height);

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();

	GLfloat ratio = (GLfloat)width / (GLfloat)height;

	if (projectionMode_ == ORTHOGRAPHIC)
	{
		if (width <= height)
		{
			//glOrtho(-_orthoSize, _orthoSize, -_orthoSize / ratio, _orthoSize / ratio, _zNear, _zFar);
			projectionMatrix = Matrix4::setOrthoFrustum(-_orthoSize, _orthoSize, -_orthoSize / ratio, _orthoSize / ratio, _zNear, _zFar);
		}
		else
		{
			//glOrtho(-_orthoSize*ratio, _orthoSize*ratio, -_orthoSize, _orthoSize, _zNear, _zFar);
			projectionMatrix = Matrix4::setOrthoFrustum(-_orthoSize*ratio, _orthoSize*ratio, -_orthoSize, _orthoSize, _zNear, _zFar);
		}
	}
	else
	{
		//gluPerspective(_fovy, ratio, _zNear, _zFar);
		projectionMatrix = Matrix4::setFrustum(_fovy, ratio, _zNear, _zFar);
	}

 	//glMatrixMode(GL_MODELVIEW);
 	//glLoadIdentity();

	//printf("RESIZE %d,%d\n", width, height);
}