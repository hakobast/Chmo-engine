
#include <iostream>

#include "EngineInclude.h"
#include "../../../Sources/Extras/GLUtils.h"
#include "ShipController.h"
#include "Weapon.h"
#include "EnemySpawner.h"
#include "Ship.h"

class HelloEngine : public GameLogic
{
public:
	void createSimpleSpaceship()
	{
		GameObject* obj = new GameObject("Spaceship");
		obj->addComponent<ShipController>();
		Ship* ship = obj->addComponent<Ship>();

		smart_pointer<Material> mat =
			AssetManager::LoadMaterial("Unlit", "Resources/Shaders/UnlitLine.vert", "Resources/Shaders/UnlitLine.frag");

 		LineRenderer* lineRend = obj->addComponent<LineRenderer>();
 		lineRend->setMainMaterial(mat);
 		lineRend->setColor(Color::GREEN);

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

 		lineRend->setPointsCount(points.size());
 		lineRend->setPoints(&points);
		
		ship->addWeapon(new Weapon(Color::RED), Vector3(-0.3f, -0.2f, 0.0f), Vector3::UP);
		ship->addWeapon(new Weapon(Color::RED), Vector3(0.3f, -0.2f, 0.0f), Vector3::UP);
		ship->addWeapon(new Weapon(Color::PURPLE), Vector3(0.0f, 0.5f, 0.0f), Vector3::UP);
	}

	void Init()
	{
		GameObject* camerObj = new GameObject("Camera");
		Camera* camera = camerObj->addComponent<Camera>();
		camera->setProjectionMode(ProjectionMode::ORTHOGRAPHIC);
		camera->setOrthoSize(5.0f);
		camerObj->getTransform()->setPosition(Vector3(0.0f, 0.0f, 10.0f));

 		GameObject* enemySpawner = new GameObject("EnemySpawner");
 		enemySpawner->addComponent<EnemySpawner>();

		createSimpleSpaceship();
	}

	float time = 0;
	int frames = 0;
	void Update()
	{
		time += GameTime::DeltaTime();
		frames++;
		if (time >= 1)
		{
			Logger::PrintWarning("FPS %d", frames);
			frames = 0;
			time = 0;
		}
	}
};