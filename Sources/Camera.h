#ifndef CAMERA_H
#define CAMERA_H

#include "GL_LIBS.h"

#include "ActiveComponent.h"

enum ProjectionMode
{
	Perspective,
	Orthographic
};

class Camera : public ActiveComponent
{
friend class ScreenSystem;

private:
	ProjectionMode projectionMode_ = Perspective;
	GLfloat fovy_ = 60.0f;
	GLfloat orthoSize_ = 5;
	GLfloat zNear_ = 0.1f;
	GLfloat zFar_ = 1000.0f;
	void Create();
	void Init();
	void Update();
	void ApplyCameraChanges();
	void OnEnable();
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
	return fovy_;
}

inline void Camera::setFOVY(GLfloat fovy)
{
	fovy_ = fovy;
	if (projectionMode_ == Perspective)
	{
		ApplyCameraChanges();
	}
}

inline GLfloat Camera::getOrthoSize()
{
	return orthoSize_;
}

inline void Camera::setOrthoSize(GLfloat size)
{
	orthoSize_ = size;
	if (projectionMode_ == Orthographic)
	{
		ApplyCameraChanges();
	}
}


#endif