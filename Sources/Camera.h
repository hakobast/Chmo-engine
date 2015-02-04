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
	void Create();
	void Init();
	void Update();
	void ApplyCameraChanges();
	void OnEnable();
public:
	void ApplyTransformation();
	ProjectionMode getProjectionMode();
	void setProjectionMode(ProjectionMode mode);
	GLfloat getFOVY();
	void setFOVY(GLfloat fovy);
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


#endif