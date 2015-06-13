
#include "Bullet.h"
#include "Weapon.h"

Weapon::Weapon(Color bulletColor, float bulletSpeed)
{
	bulletColor_ = bulletColor;
	bulletSpeed_ = bulletSpeed;
	for (int i = 0; i < poolInitialSize_; i++)
		add(createBullet());
}

Bullet* Weapon::get()
{
	Bullet* bullet = SimplePool::get();
	if (bullet != NULL)
		bullet->getGameObject()->getComponent<LineRenderer>()->setEnabled(true);

	return bullet;
}

void Weapon::add(Bullet* bullet)
{
	if (bullet != NULL)
	{
		bullet->getGameObject()->getComponent<LineRenderer>()->setEnabled(false);
		bullet->pool_ = this;
		SimplePool::add(bullet);
	}
}

Bullet* Weapon::createBullet()
{
	GameObject* bulletObject = new GameObject("Bullet");
	Bullet* bullet = bulletObject->addComponent<Bullet>();
	LineRenderer* lineRend = bulletObject->addComponent<LineRenderer>();

 	smart_pointer<Material> mat =
 		AssetManager::LoadMaterial("Unlit", "Resources/Shaders/UnlitLine.vert", "Resources/Shaders/UnlitLine.frag");

	lineRend->setMainMaterial(mat);

	std::vector<Vector3> points;
	points.push_back(Vector3(0.0f, 0.2f, 0.0f));
	points.push_back(Vector3(0.0f, 0.0f, 0.0f));

	lineRend->setPointsCount(points.size());
	lineRend->setPoints(&points);
	lineRend->setColor(bulletColor_);

	bullet->speed = bulletSpeed_;

	return bullet;
}

void Weapon::fire()
{
	Bullet* bullet = get();
	if (bullet == NULL)
	{
		Logger::Print("Create new\n");
		add(createBullet());
		bullet = get();
	}

	bullet->getTransform()->setPosition(position);
	bullet->setDirection(currentDirection);
}