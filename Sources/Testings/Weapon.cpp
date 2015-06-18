
#include "Bullet.h"
#include "Weapon.h"
#include "BoxCollider2D.h"
#include "CollisionSystem.h"

Weapon::~Weapon()
{
	for (Bullet* bullet : bullets_)
	{
		if (bullet->isEnabled())
			release(bullet);

		bullet->getGameObject()->destroy();
	}
}

Weapon::Weapon(Color bulletColor, float bulletSpeed)
{
	bulletColor_ = bulletColor;
	bulletSpeed_ = bulletSpeed;
	bulletMat_ = AssetManager::LoadMaterial("Unlit", "Resources/Shaders/UnlitLine.vert", "Resources/Shaders/UnlitLine.frag");
	for (int i = 0; i < poolInitialSize_; i++)
		release(createBullet());
}

Bullet* Weapon::get()
{
	Bullet* bullet = SimplePool::get();
	if (bullet != NULL)
	{
		bullet->getGameObject()->setActive(true);
		CollisionSystem::GetInstance().addCollider(bullet->getGameObject()->getComponent<Collider2D>());
	}

	return bullet;
}

void Weapon::release(Bullet* bullet)
{
	if (bullet != NULL)
	{
		bullet->getGameObject()->setActive(false);
		CollisionSystem::GetInstance().removeCollider(bullet->getGameObject()->getComponent<Collider2D>());

		bullet->pool_ = this;
		SimplePool::release(bullet);
	}
}

Bullet* Weapon::createBullet()
{
	GameObject* bulletObject = new GameObject("Bullet");
	Bullet* bullet = bulletObject->addComponent<Bullet>();
	LineRenderer* lineRend = bulletObject->addComponent<LineRenderer>();
	BoxCollider2D* collider = bulletObject->addComponent<BoxCollider2D>();

	lineRend->setMainMaterial(bulletMat_);

	std::vector<Vector3> points;
	points.push_back(Vector3(0.0f, 0.1f, 0.0f));
	points.push_back(Vector3(0.0f, -0.1f, 0.0f));

	lineRend->setPointsCount(points.size());
	lineRend->setPoints(&points);
	lineRend->setColor(bulletColor_);

	collider->size = Vector2(0.05f, 0.2f);
	bullet->speed = bulletSpeed_;

	bullets_.push_back(bullet);

	return bullet;
}

void Weapon::fire()
{
	Bullet* bullet = get();
	if (bullet == NULL)
	{
		Logger::Print("Weapon:: Create new Bullet\n");
		release(createBullet());
		bullet = get();
	}

	bullet->getTransform()->setPosition(position);
	bullet->setDirection(currentDirection);
}