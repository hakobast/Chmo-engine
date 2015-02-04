//
//  Engine.h
//  EngineTesting
//
//  Created by Hakob on 11/13/14.
//  Copyright (c) 2014 Haksist. All rights reserved.
//

#include <iostream>
#include "GL_LIBS.h"

#include "Engine.h"
#include "ActiveComponent.h"
#include "Utils.h"


bool pred_sortSystems(const System* lhs, const System* rhs)
{ 
	return lhs->priority < rhs->priority;
}

bool pred_initComponents(Component* c)
{
	if (c->isEnabled())
	{
		for (System* s : Engine::getInstance()._systems)
			s->addComponent(*c);
		c->Init();
		return true;
	}

	return false;
}

Engine::~Engine()
{
#ifdef FREEIMAGE_LIB
	FreeImage_DeInitialise();
#endif
}

void Engine::Init()
{
	glewInit();

#ifdef FREEIMAGE_LIB
	FreeImage_Initialise();
#endif

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
			if (activeComp->isEnabled())
				activeComp->OnDisable();
			activeComp->OnDestroy();
		}

		delete comp;
	}

	for (GameObject* gmObj : _gmObjDestroyList)
	{
		for (Component* comp : gmObj->components)
		{
			delete comp;
		}

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
		if (s->isSystemComponent(comp))
			comp.system = s;

	comp.Create();
	ActiveComponent* activeComp = dynamic_cast<ActiveComponent*>(&comp);
	if (activeComp != NULL && activeComp->isEnabled())
		activeComp->OnEnable();
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
