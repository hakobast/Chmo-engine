//
//  Engine.h
//  EngineTesting
//
//  Created by Hakob on 11/13/14.
//  Copyright (c) 2014 Haksist. All rights reserved.
//

#include <iostream>

#include "CoreEngine/Engine.h"
#include "CoreEngine/LIBS.h"
#include "CoreEngine/ActiveComponent.h"
#include "CoreEngine/Utils.h"
#include "Systems/GameLogicSystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/ScreenSystem.h"
#include "Systems/GameTime.h"
#include "Systems/Input.h"


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
	if (glewInit() == GLEW_OK)
		printf("GLEW Inited!\n");

#ifdef FREEIMAGE_LIB
	FreeImage_Initialise();
#endif

	RenderSystem* renderSystem = new RenderSystem; //renderer system
	GameLogicSystem* gameLogicSystem = new GameLogicSystem;	//gamelogic system
	ScreenSystem* screenSystem = new ScreenSystem;
	Input* inputSystem = new Input;
	GameTime* timeSystem = new GameTime;

	Engine::getInstance().addSystem(*gameLogicSystem, 1);
	Engine::getInstance().addSystem(*screenSystem, 2);
	Engine::getInstance().addSystem(*renderSystem, 3);
	Engine::getInstance().addSystem(*inputSystem, 4);
	Engine::getInstance().addSystem(*timeSystem, 5);

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
