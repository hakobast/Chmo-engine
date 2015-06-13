
#include "Enemy.h"

void Enemy::Init()
{
	transform_ = getTransform();
}

void Enemy::Update()
{
	if (isMoving_)
	{
		transform_->TranslateUp(speed*GameTime::DeltaTime());

		Vector2 rect = Camera::main->getHalfSize()*1.3f;
		Camera::main->getTransform()->getPosition(camPos_);
		transform_->getPosition(pos_);

		if (pos_.x > camPos_.x + rect.x ||
			pos_.x < camPos_.x - rect.x ||
			pos_.y > camPos_.y + rect.y ||
			pos_.y < camPos_.y - rect.y)
		{
			isMoving_ = false;
			pool_->add(this);
		}
	}
}

void Enemy::setDirection(Vector3 dir)
{
	getTransform()->SetRotation(atan2f(dir.y, dir.x)*180.0f / 3.141592f - 90, 0.0f, 0.0f, 1.0f);
	isMoving_ = true;
}
