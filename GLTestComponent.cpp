//
//  TestComponent.h
//  EngineTesting
//
//  Created by Hakob on 11/13/14.
//  Copyright (c) 2014 Haksist. All rights reserved.
//

#include <iostream>
#include <GL\glut.h>

#include "Engine.h"
#include "GameLogic.h"
#include "Input.h"
#include "GameTime.h"

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

	}

    void Init()
    {

    }
    
    void Update()
    {
		if (Input::GetMouseDown(0))
		{
			getTransform()->RotateZ(5.0f);
		}
		else if (Input::GetMouseDown(2))
		{
			getTransform()->RotateZ(-5.0f);
		}

		if (Input::GetKeyDown(27))
			exit(0);

		float speed = 10.0f;
		float rotationSpeed = 200.0f;
		if (Input::GetKeyDown(100))
			getTransform()->RotateZ(rotationSpeed*GameTime::DeltaTime());
		if (Input::GetKeyDown(101))
			getTransform()->TranslateUp(speed*GameTime::DeltaTime());
		if (Input::GetKeyDown(102))
			getTransform()->RotateZ(-rotationSpeed*GameTime::DeltaTime());
		if (Input::GetKeyDown(103))
			getTransform()->TranslateUp(-speed*GameTime::DeltaTime());
    }

	void OnAction(string action, void*const data)
	{
		cout << "GLTestComponent::Action:" << action << endl;
	}
};

