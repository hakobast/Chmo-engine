//
//  System.h
//  EngineTesting
//
//  Created by Hakob on 11/13/14.
//  Copyright (c) 2014 Haksist. All rights reserved.
//

#ifndef EngineTesting_System_h
#define EngineTesting_System_h

#include <algorithm>
#include <vector>
#include "Utils.h"
#include "Component.h"

static bool sortComponents(const Component* lhs, const Component* rhs) { return lhs->priority < rhs->priority; }

class System
{
friend class Engine;

public:
	int priority;
protected:
	virtual ~System(){};
	virtual void Init() = 0; //INFO this maybe not usable function
    virtual void Update() = 0;
    virtual void addComponent(Component &c)
	{
		components.push_back(&c);
		std::sort(components.begin(), components.end(), sortComponents);
	};

    virtual void removeComponent(Component &c)
	{
		vectorRemove<Component>(components, c);
	};
protected:
    std::vector<Component*> components;
};

#endif
