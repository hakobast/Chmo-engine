//
//  Engine.h
//  EngineTesting
//
//  Created by Hakob on 11/13/14.
//  Copyright (c) 2014 Haksist. All rights reserved.
//

#include "Engine.h"
#include "ActiveComponent.h"
#include "Utils.h"

#include <iostream>

void Engine::Init()
{
	std::cout << "Engine::Init()" << std::endl;
}

void Engine::Update()
{
	//TODO maybe this is bad solution
	for (Component* c : componentsToInit)
		if (c->isEnabled() && c->getGameObject()->isActive())
		{
			if (dynamic_cast<ActiveComponent*>(c))
				((ActiveComponent*)c)->OnEnable();
			c->Init();
		}
	componentsToInit.clear();

	for (System* s : systems)
		s->Update();
}

void Engine::addSystem(System &s, int priority)
{
    s.priority = priority;
    systems.push_back(&s);
	std::sort(systems.begin(), systems.end(),sortSystems);
}

void Engine::addGameObject(GameObject &obj)
{
    gameObjects.push_back(&obj);
}

void Engine::addComponent(Component &comp, int priority)
{
    comp.priority = priority;
    components.push_back(&comp);
	componentsToInit.push_back(&comp);
	for (System *s : systems)
		s->addComponent(comp);

	comp.Create();
}

void Engine::removeSystem(System &s)
{
	vectorRemove<System>(systems, s);
}

void Engine::removeGameObject(GameObject &obj)
{
	vectorRemove<GameObject>(gameObjects, obj);
}

void Engine::removeComponent(Component &comp)
{
	vectorRemove<Component>(components, comp);
	vectorRemove<Component>(componentsToInit, comp);
	for (System *s : systems)
		s->removeComponent(comp);

	if (dynamic_cast<ActiveComponent*>(&comp))
		((ActiveComponent*)&comp)->OnDisable();
}

GameObject* Engine::FindGameObjectByName(std::string name) const
{
	for (GameObject* obj : gameObjects)
		if (obj->name == name)
			return obj;

	return NULL;
}
