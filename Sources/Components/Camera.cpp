
#include "Camera.h"
#include "../CoreEngine/LIBS.h"
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

	float ratio = (float)width / height;

	if (projectionMode_ == ORTHOGRAPHIC)
	{
		if (width <= height)
		{
			halfSize_.x = orthoSize_;
			halfSize_.y = orthoSize_ / ratio;
			projectionMatrix = Matrix4::setOrthoFrustum(-halfSize_.x, halfSize_.x, -halfSize_.y, halfSize_.y, _zNear, _zFar);
		}
		else
		{
			halfSize_.x = orthoSize_*ratio;
			halfSize_.y = orthoSize_;
			projectionMatrix = Matrix4::setOrthoFrustum(-halfSize_.x, halfSize_.x, -halfSize_.y, halfSize_.y, _zNear, _zFar);
		}
	}
	else
	{
		projectionMatrix = Matrix4::setFrustum(_fovy, ratio, _zNear, _zFar);
	}
}