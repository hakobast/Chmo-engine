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
    
    void Init()
    {
        cout << "GLTestComponent:: Init()" << endl;
    }
    
    void Update()
    {
		//cout << "GLTestComponent:: Updated()" << endl;

		if (Input::GetMouseDown(0))
		{
			transform->RotateZ(5.0f);
		}
		else if (Input::GetMouseDown(2))
		{
			transform->RotateZ(-5.0f);
		}

		if (Input::GetKeyDown(27))
			exit(0);

		if (Input::GetKeyDown(100))
			transform->RotateZ(5.0f);
		if (Input::GetKeyDown(101))
			transform->TranslateUp(0.3f);
		if (Input::GetKeyDown(102))
			transform->RotateZ(-5.0f);
		if (Input::GetKeyDown(103))
			transform->TranslateUp(-0.3f);
    }

	void OnAction(string action, void*const data)
	{
		cout << "GLTestComponent::Action:" << action << endl;
	}
};

