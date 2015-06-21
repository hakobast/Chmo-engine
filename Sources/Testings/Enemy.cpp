
#include "Enemy.h"
#include "Collider2D.h"
#include "CollisionManager.h"

void Enemy::Init()
{
	transform_ = getTransform();
}

void Enemy::Update()
{
	transform_->TranslateUp(speed*GameTime::DeltaTime());

	Vector2 rect = Camera::main->getHalfSize()*1.1f;
	Camera::main->getTransform()->getPosition(camPos_);
	transform_->getPosition(pos_);

	if (pos_.x > camPos_.x + rect.x)
		pos_.x = camPos_.x - rect.x;
	else if (pos_.x < camPos_.x - rect.x)
		pos_.x = camPos_.x + rect.x;

	if (pos_.y > camPos_.y + rect.y)
		pos_.y = camPos_.y - rect.y;
	else if (pos_.y < camPos_.y - rect.y)
		pos_.y = camPos_.y + rect.y;

	transform_->setPosition(pos_);
}

void Enemy::setDirection(Vector3 dir)
{
	getTransform()->SetRotation(atan2f(dir.y, dir.x)*Math::RadToDeg - 90, 0.0f, 0.0f, 1.0f);
}