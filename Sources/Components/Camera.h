#ifndef CAMERA_H
#define CAMERA_H

#include "../CoreEngine/LIBS.h"
#include "../Extras/Matrix4.h"
#include "../CoreEngine/ActiveComponent.h"
#include "../CoreEngine/Component.h"


enum ProjectionMode
{
	PERSPECTIVE,
	ORTHOGRAPHIC
};

class Camera : public ActiveComponent
{
friend class ScreenSystem;

private:
	ProjectionMode projectionMode_ = PERSPECTIVE;
	GLfloat _fovy = 60.0f;
	GLfloat _orthoSize = 5;
	GLfloat _zNear = 0.1f;
	GLfloat _zFar = 1000.0f;
	void Create();
	void Init();
	void Update();
	void ApplyCameraChanges();
	void OnEnable();
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;

public:
	static Camera* main;
	void ApplyTransformation();
	ProjectionMode getProjectionMode();
	void setProjectionMode(ProjectionMode mode);
	GLfloat getFOVY();
	void setFOVY(GLfloat fovy);
	GLfloat getOrthoSize();
	void setOrthoSize(GLfloat size);
};

inline ProjectionMode Camera::getProjectionMode()
{
	return projectionMode_;
}

inline void Camera::setProjectionMode(ProjectionMode mode)
{
	if (projectionMode_ != mode)
	{
		projectionMode_ = mode;
		ApplyCameraChanges();
	}
}

inline GLfloat Camera::getFOVY()
{
	return _fovy;
}

inline void Camera::setFOVY(GLfloat fovy)
{
	_fovy = fovy;
	if (projectionMode_ == PERSPECTIVE)
	{
		ApplyCameraChanges();
	}
}

inline GLfloat Camera::getOrthoSize()
{
	return _orthoSize;
}

inline void Camera::setOrthoSize(GLfloat size)
{
	_orthoSize = size;
	if (projectionMode_ == ORTHOGRAPHIC)
	{
		ApplyCameraChanges();
	}
}


#endif