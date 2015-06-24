
#include <math.h>
#include "Enemy.h"
#include "EnemyManager.h"
#include "EnemyParticle.h"
#include "CircleCollider2D.h"
#include "CollisionManager.h"

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

void EnemyManager::Init()
{
	setEnemyGenParams({ { 0.7f, 1.5f } }, { { 0.3f, 0.6f } }, { { 0.1, 0.7f } }, { { 1, 6 } });
	for (int i = 0; i < poolInitialSize_; i++) 
		release(createEnemy());
}

void EnemyManager::Update()
{
	t_ += GameTime::DeltaTime();
	if (t_ > enemySpawnInterval_)
	{
		spawnEnemy();
		t_ = 0;
	}

	//checking enemy collision and sending collision event to opponents
	for (size_t i = 0, len = enemies_.size(); i < len; i++)
	{
		Collider2D* enemyCollider = enemies_[i]->getGameObject()->getComponent<Collider2D>();
		if (enemyCollider->getGameObject()->isActive())
		{
			collisions_.clear();
			CollisionManager::GetInstance().getPotentialCollisions(enemyCollider, &collisions_);
			for (Collider2D* collider : collisions_)
			{
				if (!enemyCollider->isEnabled() || !collider->isEnabled())
					break;

				if (enemyCollider != collider && collider->getName() != "Enemy" && enemyCollider->hasCollision(collider))
				{
					collider->getGameObject()->sendAction("Collision", enemyCollider);
					OnEnemyCollision(enemies_[i], collider);
				}
			}
		}
	}
}

void EnemyManager::setEnemyGenParams(fRange speed, fRange radius, fRange step, iRange count)
{
	speed_ = speed;
	radius_ = radius;
	step_ = step;
	count_ = count;
}

Enemy* EnemyManager::get()
{
	Enemy* enemy = SimplePool::get();
	//Logger::Print("GET ENemy\n");
	if (enemy != NULL)
	{
		enemy->getGameObject()->setActive(true);
		enemy->isSeperated = false;
		CollisionManager::GetInstance().addCollider(enemy->getGameObject()->getComponent<Collider2D>());
	}

	return enemy;
}

void EnemyManager::release(Enemy* enemy)
{
	if (enemy != NULL)
	{
		//Logger::Print("Release ENemy\n");
		enemy->getGameObject()->setActive(false);
		CollisionManager::GetInstance().removeCollider(enemy->getGameObject()->getComponent<Collider2D>());

		enemy->isSeperated = false;
		SimplePool::release(enemy);
	}
}

void EnemyManager::clearEnemies()
{
	for (Enemy* enemy : enemies_)
		release(enemy);
}

Enemy* EnemyManager::createEnemy()
{
	GameObject* obj = new GameObject("Enemy");
	CircleCollider2D* collider = obj->addComponent<CircleCollider2D>();
	LineRenderer* lineRend = obj->addComponent<LineRenderer>();
	Enemy* enemy = obj->addComponent<Enemy>();

	smart_pointer<Material> mat =
		AssetManager::LoadMaterial("Unlit", "Resources/Shaders/UnlitLine.vert", "Resources/Shaders/UnlitLine.frag");

	lineRend->setMainMaterial(mat);
	lineRend->setWidth(2.0f);
	enemies_.push_back(enemy);

	return enemy;
}

Enemy* EnemyManager::spawnEnemy()
{
	Enemy* enemy = get();
	if (enemy == NULL)
	{
		Logger::Print("EnemySpawner:: Create new Enemy\n");
		SimplePool::release(createEnemy());
		//release(createEnemy());
		enemy = get();
	}
	randomizeEnemy(enemy);

	return enemy;
}

void EnemyManager::randomizeEnemy(Enemy* enemy)
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
	} while (p < Math::Pi2);
	
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

	enemy->speed = Math::Random(speed_[0], speed_[1]);
	enemy->getTransform()->setPosition(point);
	enemy->setDirection(dir);
}

void EnemyManager::OnEnemyCollision(Enemy* enemy, Collider2D* other)
{
//	Logger::Print("OnEnemyCollision %s\n", other->getName().c_str());
	if (other->getName() == "Bullet")
	{
		if (enemy->isSeperated) //instantiate particles
		{
			GameObject* obj = new GameObject("EnemyParticle");
			obj->addComponent<EnemyParticle>()->setColor(enemy->getGameObject()->getComponent<LineRenderer>()->getColor());
			obj->getTransform()->setPosition(enemy->getTransform()->getPosition());
		}
		else // instantiate small enemies
		{
			//keeping normal values
			fRange r = radius_;
			fRange s = speed_;
			fRange st = step_;
			iRange c = count_;

			//setting values for small enemy generation
			//#TODO keep values as constants in header file
			setEnemyGenParams({ { 2.0f, 2.5f } }, { { 0.1f, 0.3f } }, { { 0.1, 0.7f } }, { { 1, 6 } });

			int count = Math::Random(1, 3);
			Enemy* newEnemy = NULL;
			for (int i = 0; i < count; i++)
			{
				newEnemy = spawnEnemy();
				newEnemy->getTransform()->setPosition(enemy->getTransform()->getPosition() + 
					Vector3(Math::Random(-0.3f, 0.3f), Math::Random(-0.3f, 0.3f), 0.0f));
				newEnemy->isSeperated = true;
			}

			//restoring normal values
			setEnemyGenParams(s, r, st, c); 
		}
	}
	release(enemy);
}