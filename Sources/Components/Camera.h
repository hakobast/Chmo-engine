#ifndef CAMERA_H
#define CAMERA_H

#include "../CoreEngine/LIBS.h"
#include "../Extras/Matrix4.h"
#include "../CoreEngine/ActiveComponent.h"
#include "../CoreEngine/Component.h"
#include "../Extras/Vectors.h"
#include "../CoreEngine/Transform.h"
#include "../Systems/ScreenSystem.h"


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
	float _fovy = 60.0f;
	float orthoSize_ = 5;
	float _zNear = 0.1f;
	float _zFar = 1000.0f;
	Vector2 halfSize_;
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

	void setFOVY(GLfloat fovy);
	void setProjectionMode(ProjectionMode mode);
	void setOrthoSize(GLfloat size);

	ProjectionMode	getProjectionMode();
	float			getFOVY();
	float			getOrthoSize();
	Vector2			getHalfSize();
	Matrix4&		getProjectionMatrix();
	void			getViewMatrix(Matrix4& viewMatrix);

	void ScreenToWorldPoint(Vector2& screen, Vector3& world);

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

inline float Camera::getFOVY()
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

inline float Camera::getOrthoSize()
{
	return orthoSize_;
}

inline Vector2 Camera::getHalfSize()
{
	return halfSize_;
}

inline void Camera::setOrthoSize(GLfloat size)
{
	orthoSize_ = size;
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

	Vector3 pos = tr->getPosition();
	translationMatrix.setColumn(3, new GLfloat[3]{-pos[0], -pos[1], -pos[2]}, 3);

	Matrix4::MultiplyMatrices(rotationMatrix, translationMatrix, viewMatrix);
}

inline void Camera::ScreenToWorldPoint(Vector2& screen, Vector3& world)
{
	if (projectionMode_ == ORTHOGRAPHIC)
	{
		int width = ScreenSystem::getWidth();
		int height = ScreenSystem::getHeight();

		Vector3 position = getTransform()->getPosition();

		world.x = position.x - halfSize_.x + 2 * halfSize_.x* screen.x / width;
		world.y = position.y - halfSize_.y + 2 * halfSize_.y* (height - screen.y) / height;
	}

	//TODO calc it for projection mode
}

#endif