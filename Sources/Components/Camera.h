#ifndef CAMERA_H
#define CAMERA_H

#include "../CoreEngine/LIBS.h"
#include "../Extras/Matrix4.h"
#include "../CoreEngine/ActiveComponent.h"
#include "../CoreEngine/Component.h"
#include "../Extras/Vectors.h"
#include "../CoreEngine/Transform.h"


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
	void OnDestroy();
	Matrix4 rotationMatrix; 
	Matrix4 translationMatrix;
	Matrix4 projectionMatrix;

public:
	static Camera* main;
	ProjectionMode getProjectionMode();
	void setProjectionMode(ProjectionMode mode);
	GLfloat getFOVY();
	void setFOVY(GLfloat fovy);
	GLfloat getOrthoSize();
	void setOrthoSize(GLfloat size);
	Matrix4& getProjectionMatrix();
	void getViewMatrix(Matrix4& viewMatrix);
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

inline Matrix4& Camera::getProjectionMatrix()
{
	return projectionMatrix;
}

inline void Camera::getViewMatrix(Matrix4& viewMatrix)
{
	Transform* tr = getTransform();
	tr->getMatrix(rotationMatrix,true);

	rotationMatrix.makeTranspose();
	rotationMatrix[3] = 0.0f;
	rotationMatrix[7] = 0.0f;
	rotationMatrix[11] = 0.0f;
	rotationMatrix[15] = 1.0f;

	translationMatrix.setColumn(3, new GLfloat[3]{-tr->Location[0], -tr->Location[1], -tr->Location[2]}, 3);

	Matrix4::MultiplyMatrices(rotationMatrix, translationMatrix, viewMatrix);
}

#endif