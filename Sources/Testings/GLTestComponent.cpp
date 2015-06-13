
#include <iostream>

#include "FPSCounter.cpp"

#include "../CoreEngine/ChmoEngine.h"

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
