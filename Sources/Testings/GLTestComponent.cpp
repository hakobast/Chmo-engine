
#include <iostream>

#include "FPSCounter.cpp"

#include "EngineInclude.h"
#include "Collider2D.h"
#include "CollisionUtils.h"
#include "CollisionManager.h"

using namespace std;

class GLTestComponent : public GameLogic
{
public:
	CollisionManager* collisionSystem;
	Collider2D* first;
	Collider2D* second;

	~GLTestComponent()
	{
		cout << "GLTestComponent:: ~~~deleted~~~" << endl;
	}

	smart_pointer<Texture2D> textureTransparent;
	void Create()
	{
		textureTransparent = LoadTexture("Resources/vtr.bmp");

		//cout << "GLTestComponent:: Create" << endl;
	}

	void Init()
	{
		//std::cout << "GL TEST INITED" << std::endl;
	}

	void Update()
	{
		if (first && Input::IsKeyDownNow(l))
		{
			Logger::Print("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			std::vector<Collider2D*> colliders;
			collisionSystem->getColliders(&colliders);
			for (Collider2D* coll : colliders)
				coll->getGameObject()->getComponent<SpriteRenderer>()->setColor(Color::WHITE);

			colliders.clear();
			collisionSystem->getPotentialCollisions(first, &colliders);
			for (Collider2D* coll : colliders)
			{
				coll->getGameObject()->getComponent<SpriteRenderer>()->setColor(Color::GREEN);
			}
		}

		if (Input::IsKeyDownNow(c))
		{
			Logger::Print("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			smart_pointer<Material> mat =
				AssetManager::LoadMaterial("Unlit", "Resources/Shaders/UnlitSprite.vert", "Resources/Shaders/UnlitSprite.frag");
			mat->addTexture(textureTransparent);

			GameObject* obj2 = new GameObject("SecondGameObject");

			obj2->addComponent<SpriteRenderer>()->addMaterial(mat);
			BoxCollider2D* secondColl = obj2->addComponent<BoxCollider2D>();
			secondColl->size = Vector2(0.5f, 0.5f);
			float x = Math::Random(-5.0f, 5.0f);
			float y = Math::Random(-5.0f, 5.0f);
			Logger::Print("POs %f, %f\n", x, y);
			obj2->getTransform()->setPosition(Vector3(x, y, 0.0f));
			//obj2->getTransform()->setPosition(Vector3(-2.0f + 0.5f*i, 3.2f, 0.0f));
			obj2->getTransform()->setScale(Vector3(0.08f, 0.08f, 0.1f));

			collisionSystem->addCollider(secondColl);
		}
		if (first && second)
		{
			//bool has = first->HasCollision(second);
			//bool has = CollisionUtils::IsInersectsWithCollider(Vector2::ZERO, Vector2(2.56f, 2.56f), first);
// 			if (has)
// 				first->getGameObject()->getComponent<SpriteRenderer>()->setColor(Color::GREEN);
// 			else
// 				first->getGameObject()->getComponent<SpriteRenderer>()->setColor(Color::WHITE);
		}

		if (Input::IsKeyDown(Key::e))
		{
			printf("AUUUUUU\n");
			exit(0);
		}

		float speed = 5.0f;
		float rotationSpeed = 100.0f;
		if (Input::IsKeyDown(Key::a))
			//getTransform()->RotateY(-rotationSpeed*GameTime::DeltaTime());
			getTransform()->TranslateRight(-speed*GameTime::DeltaTime());
		if (Input::IsKeyDown(Key::d))
			//getTransform()->RotateY(rotationSpeed*GameTime::DeltaTime());
			getTransform()->TranslateRight(speed*GameTime::DeltaTime());
		if (Input::IsKeyDown(Key::w))
			getTransform()->TranslateUp(speed*GameTime::DeltaTime());
		if (Input::IsKeyDown(Key::s))
			getTransform()->TranslateUp(-speed*GameTime::DeltaTime());

		if (Input::IsKeyDown(Key::n))
		{
			getTransform()->RotateX(rotationSpeed*GameTime::DeltaTime());
		}
		if (Input::IsKeyDown(Key::m))
		{
			getTransform()->RotateX(-rotationSpeed*GameTime::DeltaTime());
		}
	}

	void OnAction(string action, void*const data)
	{
		cout << "GLTestComponent::Action:" << action << endl;
	}

	void OnEnable()
	{
		//std::cout << "GLTestComponent: OnEnable" << std::endl;
	}

	void OnDisable()
	{
		std::cout << "GLTestComponent: OnDisable" << std::endl;
	}

	void OnDestroy()
	{
		std::cout << "GLTestComponent: OnDestroy" << std::endl;
	}
};
