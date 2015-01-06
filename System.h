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

class System
{
friend class Engine;

public:
	int priority;
protected:
	virtual ~System(){};
	virtual void Init() = 0; //INFO this maybe not usable function
    virtual void Update() = 0;
public:
	virtual void addComponent(Component &c) = 0;
	virtual void removeComponent(Component &c) = 0;
};

#endif
