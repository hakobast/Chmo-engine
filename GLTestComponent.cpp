//
//  TestComponent.h
//  EngineTesting
//
//  Created by Hakob on 11/13/14.
//  Copyright (c) 2014 Haksist. All rights reserved.
//

#include "Engine.h"
#include "Behaviour.h"
#include <iostream>
#include <GL\glut.h>

using namespace std;

class GLTestComponent: public Behaviour
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
    
    void Update(float deltaTime)
    {
		cout << "GLTestComponent:: Updated()" << endl;

		transform->RotateZ(5.0f);
    }

	void OnAction(string action, void*const data)
	{
		cout << "GLTestComponent::Action:" << action << endl;
	}
};

