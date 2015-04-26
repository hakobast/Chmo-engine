
#include "Camera.h"
#include "../CoreEngine/LIBS.h"
#include "../CoreEngine/Transform.h"
#include "../Systems/ScreenSystem.h"

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
 
 	viewMatrix[0] = Right[0];
 	viewMatrix[4] = Right[1]; 
 	viewMatrix[8] = Right[2];
 	viewMatrix[12] = 0.0f;
 
 	viewMatrix[1] = Up[0];
 	viewMatrix[5] = Up[1];
 	viewMatrix[9] = Up[2];
 	viewMatrix[13] = 0.0f;
 
 	viewMatrix[2] = Forward[0];
 	viewMatrix[6] = Forward[1];
 	viewMatrix[10] = Forward[2];
 	viewMatrix[14] = 0.0f;
 
	viewMatrix[3] = 0.0f;// tr->Location[0];
	viewMatrix[7] = 0.0f;// tr->Location[1];
	viewMatrix[11] = 0.0f;// tr->Location[2];
 	viewMatrix[15] = 1.0f;

	//viewMatrix = tr->getMatrix();
	
	glMultMatrixf(&viewMatrix[0]);

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
			//projectionMatrix = Matrix4::setOrthoFrustum(-_orthoSize, _orthoSize, -_orthoSize / ratio, _orthoSize / ratio, _zNear, _zFar);
		else
			//projectionMatrix = Matrix4::setOrthoFrustum(-_orthoSize*ratio, _orthoSize*ratio, -_orthoSize, _orthoSize, _zNear, _zFar);
			glOrtho(-_orthoSize*ratio, _orthoSize*ratio, -_orthoSize, _orthoSize, _zNear, _zFar);
	}
	else
	{
		//projectionMatrix = Matrix4::setFrustum(_fovy, ratio, _zNear, _zFar);
		gluPerspective(_fovy, ratio, _zNear, _zFar);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//printf("RESIZE %d,%d\n", width, height);
}