
#include <math.h>
#include "Enemy.h"
#include "EnemySpawner.h"
#include "CircleCollider2D.h"

Vector2 getRectanglePoint(int width, int height, Vector2 center, float angle)
{
	float r = height / 2 * sqrt(pow(sin(angle*DEG_TO_RAD), 2)) + width / 2 * sqrt(pow(cos(angle*DEG_TO_RAD), 2));

	Vector2 point(center.x + r*cos(angle*DEG_TO_RAD), center.x + r*sin(angle*DEG_TO_RAD));

	point.x = point.x < -width / 2 ? -width / 2 : (point.x > width / 2 ? width / 2 : point.x);
	point.y = point.y < -height / 2 ? -height / 2 : (point.y > height / 2 ? height / 2 : point.y);
	point.x += center.x;
	point.y += center.y;

	return point;
}

void EnemySpawner::Init()
{
	setRandomParams({ { 0.3f, 0.6f } }, { {0.1, 0.7f} }, { {1, 6} });
	for (int i = 0; i < poolInitialSize_; i++) 
		add(createEnemy());
}

void EnemySpawner::Update()
{
	t_ += GameTime::DeltaTime();
	if (t_ > enemySpawnInterval_)
	{
		spawnEnemy();
		t_ = 0;
	}

	if (Input::IsKeyDownNow(g))
	{
// 		Enemy* enemy = GameObject::FindComponent<Enemy>();
// 		if (enemy != NULL)
// 			enemy->pool_->add(enemy);
// 
// 		spawnEnemy();
	}
}

void EnemySpawner::setRandomParams(fRange radius, fRange step, iRange count)
{
	radius_ = radius;
	step_ = step;
	count_ = count;
}

Enemy* EnemySpawner::createEnemy()
{
	GameObject* obj = new GameObject("Enemy");
	obj->addComponent<CircleCollider2D>();
	LineRenderer* lineRend = obj->addComponent<LineRenderer>();
	Enemy* enemy = obj->addComponent<Enemy>();

	smart_pointer<Material> mat =
		AssetManager::LoadMaterial("Unlit", "Resources/Shaders/UnlitLine.vert", "Resources/Shaders/UnlitLine.frag");

	lineRend->setMainMaterial(mat);

	return enemy;
}

void EnemySpawner::spawnEnemy()
{
	Enemy* enemy = get();
	if (enemy == NULL)
	{
		Logger::Print("Create new\n");
		add(createEnemy());
		enemy = get();
	}

	randomizeEnemy(enemy);
}

void EnemySpawner::randomizeEnemy(Enemy* enemy)
{
	std::vector<Vector3> points;

	float p = 0.0f,rad = 0.0f,step = 0.0f, avRadius = 0.0f;
	int count = 0, i = 0;
	do 
	{
		if (count == 0)
		{
			rad = Math::Random(radius_[0], radius_[1]);
			avRadius += rad;
			i++;
			step = Math::Random(step_[0], step_[1]);
			count = Math::Random(count_[0], count_[1]);
		}

		points.push_back(Vector3(cos(p), sin(p),0.0f)*rad);

		count--;
		p += step;
	} while (p < 3.141592f*2);
	
	points.push_back(points[0]);

	LineRenderer* lineRend = enemy->getGameObject()->getComponent<LineRenderer>();
	lineRend->setPointsCount(points.size());
	lineRend->setPoints(&points);
	lineRend->setColor(Color(Math::Random(0.1f, 1.0f), Math::Random(0.3f, 1.0f), Math::Random(0.1f, 1.0f)));

	enemy->getGameObject()->getComponent<CircleCollider2D>()->radius = avRadius/i;

	Vector2 rect = Camera::main->getHalfSize();
	Vector3 camPos = Camera::main->getTransform()->getPosition();
	Vector3 point = getRectanglePoint((int)(rect.x * 2.5f), (int)(rect.y * 2.5f), camPos, (float)Math::Random(0, 360));
	Vector3 dir = (camPos - point).normalize() + Vector3(Math::Random(-1.0f, 1.0f), Math::Random(-1.0f, 1.0f), 0.0f).normalize();

	enemy->getTransform()->setPosition(point);
	enemy->setDirection(dir);
}

Enemy* EnemySpawner::get()
{
	Enemy* enemy = SimplePool::get();
	if (enemy != NULL)
	{
		enemy->getGameObject()->getComponent<LineRenderer>()->setEnabled(true);
		enemy->getGameObject()->getComponent<CircleCollider2D>()->setEnabled(true);
	}

	return enemy;
}

void EnemySpawner::add(Enemy* enemy)
{
	if (enemy != NULL)
	{
		enemy->getGameObject()->getComponent<LineRenderer>()->setEnabled(false);
		enemy->getGameObject()->getComponent<CircleCollider2D>()->setEnabled(false);
		enemy->pool_ = this;
		SimplePool::add(enemy);
	}
}