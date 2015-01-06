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

static bool pred_sortSystems(const System* lhs, const System* rhs)
{ 
	return lhs->priority < rhs->priority;
}

static bool pred_initComponents(Component* c)
{
	if (c->isEnabled())
	{
		c->Init();
		return true;
	}

	return false;
}

void Engine::Init()
{
	std::cout << "Engine::Init()" << std::endl;
}

void Engine::Update()
{
	vectorRemove(_compInitList, pred_initComponents);

	for (System* s : _systems)
		s->Update();

	for (Component* comp : _compDestroyList)
	{
		ActiveComponent* activeComp = dynamic_cast<ActiveComponent*>(comp);
		if (activeComp != NULL)
		{
			activeComp->OnDisable();
			activeComp->OnDestroy();
		}

		delete comp;
	}

	for (GameObject* gmObj : _gmObjDestroyList)
	{
		delete gmObj;
	}

	_compDestroyList.clear();
	_gmObjDestroyList.clear();
}

void Engine::addSystem(System &s, int priority)
{
    s.priority = priority;
    _systems.push_back(&s);
	std::sort(_systems.begin(), _systems.end(),pred_sortSystems);
}

void Engine::addGameObject(GameObject &obj)
{
    _gameObjects.push_back(&obj);
}

void Engine::addComponent(Component &comp, int priority)
{
    comp.priority = priority;
    _components.push_back(&comp);
	_compInitList.push_back(&comp);

	for (System* s : _systems)
		s->addComponent(comp);

	ActiveComponent* activeComp = dynamic_cast<ActiveComponent*>(&comp);
	if (activeComp != NULL && activeComp->isEnabled())
		activeComp->OnEnable();
	comp.Create();
}

void Engine::removeSystem(System &s)
{
	vectorRemove<System>(_systems, &s);
}

void Engine::removeGameObject(GameObject &obj)
{
	vectorRemove<GameObject>(_gameObjects, &obj);
	_gmObjDestroyList.push_back(&obj);
}

void Engine::removeComponent(Component &comp)
{
	vectorRemove<Component>(_components, &comp);
	vectorRemove<Component>(_compInitList, &comp);
	_compDestroyList.push_back(&comp);
}

GameObject* Engine::FindGameObjectByName(std::string name) const
{
	for (GameObject* obj : _gameObjects)
		if (obj->name == name)
			return obj;

	return NULL;
}
