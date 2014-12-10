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


	GLfloat diffuse[4];// = { 1.0f, 0.0f, 0.0f, 1.0f };
	GLfloat lightPos[4];// = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat lightDir[4];

	void Init()
	{
		diffuse[0] = 1.0f; diffuse[1] = 1.0f; diffuse[2] = 1.0f; diffuse[3] = 1.0f;
		lightPos[0] = 0.0f; lightPos[1] = 0.0f; lightPos[2] = 10.0f; lightPos[3] = 1.0f;
		lightDir[0] = 0.0f; lightDir[1] = 0.0f; lightDir[2] = -1.0f; lightDir[3] = 1.0f;

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse); 
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
		glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, 10.0f);
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightDir);

		glEnable(GL_COLOR_MATERIAL);
	}
    
    void Update()
    {
		glPushMatrix();
		getTransform()->applyTransformation();
		glTranslatef(0.0f, 0.0f, 0.0f);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightDir);
		glPopMatrix();

		if (Input::GetKeyDown(KeyCode::a))
		{
			getGameObject()->getComponent<Renderer>()->destroy();
		}

		//RGB
		if (Input::GetKeyDown(KeyCode::r))
		{
			diffuse[0] += 0.1f;
		}

		if (Input::GetKeyDown(KeyCode::g))
		{
			diffuse[1] += 0.1f;
		}

		if (Input::GetKeyDown(KeyCode::b))
		{
			diffuse[2] += 0.1f;
		}

		if (Input::GetMouseDown(0))
		{
			getTransform()->RotateX(3.0f);
			getTransform()->RotateY(2.0f);
			getTransform()->RotateZ(2.0f);
		}
		else if (Input::GetMouseDown(2))
		{
			getTransform()->RotateX(-3.0f);
			getTransform()->RotateY(-2.0f);
			getTransform()->RotateZ(-2.0f);
		}

		if (Input::GetKeyDown(27))
			exit(0);

		float speed = 1.0f;
		float rotationSpeed = 200.0f;
		if (Input::GetKeyDown(100))
			getTransform()->TranslateRight(-speed*GameTime::DeltaTime());
		if (Input::GetKeyDown(101))
			getTransform()->TranslateUp(speed*GameTime::DeltaTime());
		if (Input::GetKeyDown(102))
			getTransform()->TranslateRight(speed*GameTime::DeltaTime());
		if (Input::GetKeyDown(103))
			getTransform()->TranslateUp(-speed*GameTime::DeltaTime());
    }

	void OnAction(string action, void*const data)
	{
		cout << "GLTestComponent::Action:" << action << endl;
	}
};

