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

using namespace std;

class TestComponent: public Behaviour
{
public:

    ~TestComponent()
    {
       cout << "~TestComponent()" << endl; 
    }
    
    void Init()
    {
        cout << "TestComponent:Init() Priority: " << priority << endl;
    }
    
    void Update(float deltaTime)
    {
		cout << "TestComponent:Update() Priority: " << priority << " GameObject " << getGameObject()->name << endl;
    }

	void OnAction(string action, void*const data)
	{
		cout << "TestComponent::Action:" << action << endl;
	}
};

