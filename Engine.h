//
//  Engine.h
//  EngineTesting
//
//  Created by Hakob on 11/13/14.
//  Copyright (c) 2014 Haksist. All rights reserved.
//

#ifndef EngineTesting_Engine_h
#define EngineTesting_Engine_h

#include <vector>
#include <iostream>
#include <string>
#include "System.h"
#include "GameObject.h"
#include "Component.h"
#include "Engine.h"

static bool sortSystems(const System* lhs, const System* rhs) { return lhs->priority < rhs->priority; }

class Engine
{

public:
    void Init();
    void Update();
    void addSystem(System &s, int priority);
    void addGameObject(GameObject &obj);
    void addComponent(Component &comp, int priority);
	void removeSystem(System &s);
	void removeGameObject(GameObject &obj);
	void removeComponent(Component &comp);
	static inline Engine& getInstance()
	{
		static Engine engine;
		return engine;
	}
private:
    std::vector<Component*> components;
    std::vector<GameObject*> gameObjects;
    std::vector<System*> systems;
    int frameRate;

	Engine()
	{
		std::cout << "ENGINE created" << std::endl;
	}

	friend class GameObject;
};

#endif