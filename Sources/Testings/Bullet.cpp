
#include <math.h>
#include "Bullet.h"
#include "Weapon.h"

void Bullet::Init()
{
	transform_ = getTransform();
}

void Bullet::Update()
{
	if (isMoving_)
	{
		transform_->TranslateUp(speed*GameTime::DeltaTime());

		Vector2 rect = Camera::main->getHalfSize();
		Camera::main->getTransform()->getPosition(camPos_);
		transform_->getPosition(pos_);

		if (pos_.x > camPos_.x + rect.x ||
			pos_.x < camPos_.x - rect.x ||
			pos_.y > camPos_.y + rect.y ||
			pos_.y < camPos_.y - rect.y)
		{
			isMoving_ = false;
			pool_->release(this);
		}
	}
}

void Bullet::OnAction(std::string action, void*const data)
{
	if (action == "Collision")
	{
		isMoving_ = false;
		pool_->release(this);
	}
}

void Bullet::setDirection(Vector3 dir)
{
	getTransform()->SetRotation(atan2f(dir.y, dir.x)*180.0f / 3.141592f - 90, 0.0f, 0.0f, 1.0f);
	isMoving_ = true;
}