
#include "GameController.h"
#include "FPSCounter.cpp"
#include "CollisionManager.h"
#include "BoxCollider2D.h"
#include "ShipController.h"
#include "EnemyManager.h"
#include "Weapon.h"
#include "Ship.h"

void GameController::Init()
{
	GameObject* camerObj = new GameObject("Camera");
	Camera* camera = camerObj->addComponent<Camera>();
	camera->setProjectionMode(ProjectionMode::ORTHOGRAPHIC);
	camera->setOrthoSize(5.0f);
	camera->setFOVY(60.0f);

	camerObj->addComponent<FPSCounter>();
	camerObj->getTransform()->setPosition(Vector3(0.0f, 0.0f, 10.0f));

	collisionManager_ = (new GameObject("CollisionManager"))->addComponent<CollisionManager>();
	enemyManager_ = (new GameObject("EnemySpawner"))->addComponent<EnemyManager>();

	collisionManager_->setEnabled(false);
	enemyManager_->setEnabled(false);

	startGame();
}

void GameController::Update()
{
	if (Input::IsKeyDownNow(e))
	{
		Logger::Print("END GAME\n");
		endGame();
	}

	if (Input::IsKeyDownNow(s))
	{
		Logger::Print("START GAME\n");
		startGame();
	}
}

void GameController::startGame()
{
	if (!isGameStarted_)
	{
		collisionManager_->setEnabled(true);
		enemyManager_->setEnabled(true);

		switch (spaceShipType)
		{
		case STANDART:
			createStandartSpaceship();
			break;
		case COOL:
			createCoolSpaceship();
			break;
		}

		isGameStarted_ = true;
	}
}

void GameController::endGame()
{
	if (isGameStarted_)
	{
		collisionManager_->setEnabled(false);
		enemyManager_->clearEnemies();
		enemyManager_->setEnabled(false);

		GameObject::FindComponent<ShipController>()->getGameObject()->destroy();

		isGameStarted_ = false;
	}
}

void GameController::restartGame()
{
	if (isGameStarted_)
	{
		endGame();
		startGame();
	}
}

void GameController::createCoolSpaceship()
{
	std::vector<Vector3> points;
	points.push_back(Vector3(0.03f, 0.6f, 0.0f));
	points.push_back(Vector3(0.03f, 0.71f, 0.0f));
	points.push_back(Vector3(0.1f, 0.7f, 0.0f));
	points.push_back(Vector3(0.2f, 0.4f, 0.0f));
	points.push_back(Vector3(0.5f, 0.1f, 0.0f));
	points.push_back(Vector3(0.5f, -0.3f, 0.0f));
	points.push_back(Vector3(0.3f, -0.5f, 0.0f));
	points.push_back(Vector3(0.25f, -0.7f, 0.0f));
	points.push_back(Vector3(0.15f, -0.8f, 0.0f));
	points.push_back(Vector3(0.1f, -0.6f, 0.0f));

	points.push_back(Vector3(-0.1f, -0.6f, 0.0f));
	points.push_back(Vector3(-0.15f, -0.8f, 0.0f));
	points.push_back(Vector3(-0.25f, -0.7f, 0.0f));
	points.push_back(Vector3(-0.3f, -0.5f, 0.0f));
	points.push_back(Vector3(-0.5f, -0.3f, 0.0f));
	points.push_back(Vector3(-0.5f, 0.1f, 0.0f));
	points.push_back(Vector3(-0.2f, 0.4f, 0.0f));
	points.push_back(Vector3(-0.1f, 0.7f, 0.0f));

	points.push_back(Vector3(-0.03f, 0.71f, 0.0f));
	points.push_back(Vector3(-0.03f, 0.6f, 0.0f));
	points.push_back(Vector3(0.03f, 0.6f, 0.0f));

	GameObject* obj = new GameObject("CoolSpaceship");
	obj->addComponent<ShipController>();
	BoxCollider2D* collider = obj->addComponent<BoxCollider2D>();
	Ship* ship = obj->addComponent<Ship>();

	smart_pointer<Material> mat =
		AssetManager::LoadMaterial("Unlit", "Resources/Shaders/UnlitLine.vert", "Resources/Shaders/UnlitLine.frag");

	LineRenderer* lineRend = obj->addComponent<LineRenderer>();
	lineRend->setMainMaterial(mat);
	lineRend->setPointsCount(points.size());
	lineRend->setPoints(&points);
	lineRend->setColor(Color::PURPLE());
	lineRend->setWidth(2.0f);

	ship->addWeapon(new Weapon(Color::YELLOW()), Vector3(-0.3f, -0.2f, 0.0f), Vector3::UP);
	ship->addWeapon(new Weapon(Color::YELLOW()), Vector3(0.3f, -0.2f, 0.0f), Vector3::UP);
	ship->addWeapon(new Weapon(Color::RED()), Vector3(0.0f, 0.5f, 0.0f), Vector3::UP);

	collider->size = Vector2(1.2f, 1.4f);
}

void GameController::createStandartSpaceship()
{
	std::vector<Vector3> points;
	points.push_back(Vector3(-0.2f, -0.15f, 0.0f));
	points.push_back(Vector3(0.0f, 0.15f, 0.0f));
	points.push_back(Vector3(0.2f, -0.15f, 0.0f));

	GameObject* obj = new GameObject("StandartSpaceship");
	obj->addComponent<ShipController>();
	Ship* ship = obj->addComponent<Ship>();
	BoxCollider2D* collider = obj->addComponent<BoxCollider2D>();

	smart_pointer<Material> mat =
		AssetManager::LoadMaterial("Unlit", "Resources/Shaders/UnlitLine.vert", "Resources/Shaders/UnlitLine.frag");

	LineRenderer* lineRend = obj->addComponent<LineRenderer>();
	lineRend->setMainMaterial(mat);
	lineRend->setPointsCount(points.size());
	lineRend->setPoints(&points);
	lineRend->setColor(Color::GREEN());
	lineRend->setWidth(2.0f);

	ship->addWeapon(new Weapon(Color::RED()), Vector3(0.0f, 0.5f, 0.0f), Vector3::UP);

	collider->size = Vector2(0.5f, 0.3f);
}