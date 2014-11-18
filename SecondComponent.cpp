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

class SecondComponent: public Component
{
public:

	~SecondComponent()
    {
       cout << "~SecondComponent()" << endl; 
    }
    
    void Init()
    {
        cout << "SecondComponent:Init() Priority: " << priority << endl;
    }
    
    void Update(float deltaTime)
    {
		cout << "Delta " << deltaTime << endl;
    }

	/*void OnAction(string action, void*const data)
	{
		cout << "SecondComponent::Action:" << action << endl;
	}*/
};

