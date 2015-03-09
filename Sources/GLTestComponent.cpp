//
//  TestComponent.h
//  EngineTesting
//
//  Created by Hakob on 11/13/14.
//  Copyright (c) 2014 Haksist. All rights reserved.
//
#include <iostream>

#include "Engine.h"
#include "GameLogic.h"
#include "Input.h"
#include "GameTime.h"
#include "FPSCounter.cpp"

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
		if (Input::GetKeyDown(KeyCode::l))
		{
			FPSCounter* rend = getGameObject()->getComponent<FPSCounter>();
			if (rend != NULL)
			{
				std::cout << "FOUND " << rend->isEnabled() << " Counter " << !rend->isEnabled() << std::endl;
				rend->getGameObject()->setActive(false);

				rend->setEnabled(!rend->isEnabled());
				rend->destroy();
				rend->getGameObject()->setActive(true);
				rend->getGameObject()->destroy();

				rend->getGameObject()->setActive(false);
				rend->getGameObject()->addComponent<GLTestComponent>();
				getGameObject()->destroy();
			}
			else
				std::cout << "CAN'T FIND\n";
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

		if (Input::GetKeyDown(27))
		{
			printf("AUUUUUU\n");
			exit(0);
		}

		float speed = 5.0f;
		float rotationSpeed = 100.0f;
		if (Input::GetKeyDown(KeyCode::a))
			getTransform()->RotateY(rotationSpeed*GameTime::DeltaTime());
		if (Input::GetKeyDown(KeyCode::d))
			getTransform()->RotateY(-rotationSpeed*GameTime::DeltaTime());
		if (Input::GetKeyDown(KeyCode::w))
			getTransform()->TranslateForward(-speed*GameTime::DeltaTime());
		if (Input::GetKeyDown(KeyCode::s))
			getTransform()->TranslateForward(speed*GameTime::DeltaTime());

		if (Input::GetKeyDown(KeyCode::n))
		{
			getTransform()->RotateX(rotationSpeed*GameTime::DeltaTime());
		}
		if (Input::GetKeyDown(KeyCode::m))
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

