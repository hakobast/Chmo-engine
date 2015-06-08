
#include <iostream>

#include "../CoreEngine/Engine.h"
#include "../CoreEngine/GameLogic.h"
#include "../Systems/Input.h"
#include "../Systems/GameTime.h"
#include "FPSCounter.cpp"
#include "../Components/SpriteRenderer.h"
#include "../Components/MeshRenderer.h"

using namespace std;

class GLTestComponent : public GameLogic
{
public:
	~GLTestComponent()
	{
		cout << "GLTestComponent:: ~~~deleted~~~" << endl;
	}

	void Create()
	{
		cout << "GLTestComponent:: Create" << endl;
	}

	void Init()
	{
		std::cout << "GL TEST INITED" << std::endl;
	}

	void Update()
	{
		if (Input::IsKeyDownNow(SpecialKey::UP))
		{
			MeshRenderer* meshRend = GameObject::FindComponent<MeshRenderer>();

			if (meshRend != NULL)
			{
				smart_pointer<Mesh> mesh = meshRend->getMesh();

				std::vector<unsigned int> indices{ 2, 3, 1 };
			//	std::vector<unsigned int> indices{ 0, 1, 2, 3, 0, 2 };

				std::vector<Vector3> verts{ Vector3(-1.0f, -1.0f, 0.0f), Vector3(1.0f, -1.0f, 0.0f), Vector3(1.0f, 1.0f, 0.0f), Vector3(-1.0f, 1.0f, 0.0f) };
				std::vector<Vector3> norms{ Vector3(0.0f, 0.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f) };

				//mesh->setVertices(&verts);
				//mesh->setNormals(norms);
				mesh->setIndices(&indices);

				//meshRend->setMesh(mesh);
			}
			else
				std::cout << "CAN'T FIND\n";
		}

		if (Input::IsKeyDownNow(SpecialKey::DOWN))
		{
			MeshRenderer* meshRend = GameObject::FindComponent<MeshRenderer>();

			if (meshRend != NULL)
			{
				smart_pointer<Mesh> mesh = meshRend->getMesh();

				std::vector<unsigned int> indices{ 3, 0, 2 };
				std::vector<Vector3> verts{ Vector3(-1.0f, -3.0f, 0.0f), Vector3(1.0f, -1.0f, 0.0f), Vector3(1.0f, 1.0f, 0.0f), Vector3(-1.0f, 1.0f, 0.0f) };
				std::vector<Vector3> norms{ Vector3(0.0f, 0.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f) };

				//mesh->setVertices(&verts);
				//mesh->setNormals(norms);
				mesh->setIndices(&indices);

				//meshRend->setMesh(mesh);
			}
			else
				std::cout << "CAN'T FIND\n";
		}

		if (Input::IsMouseDownNow(MouseButton::Left))
		{
			std::cout << "PRINT ME\n";
		}

		if (Input::IsKeyDownNow(Key::p))
		{
			std::cout << "PRINT ME\n";
		}

		if (Input::IsKeyDownNow(Key::F))
		{
			SpriteRenderer* spRend = GameObject::FindComponent<SpriteRenderer>();
			if (spRend != NULL)
			{
				spRend->destroy();
			}
		}

		//glMaterialfv(GL_FRONT, GL_DIFFUSE, new float[4]{ 1.0f, 0.0f, 0.0f, 1.0f });
		//glBegin(GL_LINES);
		//{
		//	float z = -5.0f;

		//	glVertex3f(0.0f, 1.0f, z);
		//	glVertex3f(0.0f, -1.0f, z);

		//	glVertex3f(-1.0f, 0.0f, z);
		//	glVertex3f(1.0f, 0.0f, z);
		//}
		//glEnd();

		if (Input::IsKeyDown(Key::e))
		{
			printf("AUUUUUU\n");
			exit(0);
		}

		float speed = 15.0f;
		float rotationSpeed = 100.0f;
		if (Input::IsKeyDown(Key::a))
			//getTransform()->RotateY(-rotationSpeed*GameTime::DeltaTime());
			getTransform()->TranslateRight(-speed*GameTime::DeltaTime());
		if (Input::IsKeyDown(Key::d))
			//getTransform()->RotateY(rotationSpeed*GameTime::DeltaTime());
			getTransform()->TranslateRight(speed*GameTime::DeltaTime());
		if (Input::IsKeyDown(Key::w))
			getTransform()->TranslateForward(-speed*GameTime::DeltaTime());
		if (Input::IsKeyDown(Key::s))
			getTransform()->TranslateForward(speed*GameTime::DeltaTime());

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
		std::cout << "GLTestComponent: OnEnable" << std::endl;
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
