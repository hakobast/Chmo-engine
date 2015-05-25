//
//  Engine.h
//  EngineTesting
//
//  Created by Hakob on 11/13/14.
//  Copyright (c) 2014 Haksist. All rights reserved.
//

#include <iostream>

#include "Engine.h"
#include "LIBS.h"
#include "ActiveComponent.h"
#include "Utils.h"
#include "GameObject.h"
#include "System.h"
#include "Component.h"
#include "AssetManager.h"

#include "../Systems/GameLogicSystem.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/ScreenSystem.h"
#include "../Systems/GameTime.h"
#include "../Systems/Input.h"

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

void f_Destroy()
{
	Engine::getInstance().Cleanup();
}

Engine::~Engine()
{
	
}

void Engine::Create()
{
	displayModule->create();
	displayModule->addObserver(this);

#if defined(_WIN32) || defined(__APPLE__)
	atexit(f_Destroy);
	if (glewInit() == GLEW_OK)
		printf("GLEW Inited!\n");
#endif

	AssetManager::Initialize();

	RenderSystem* renderSystem = new RenderSystem; //renderer system
	GameLogicSystem* gameLogicSystem = new GameLogicSystem;	//gamelogic system
	ScreenSystem* screenSystem = new ScreenSystem(displayModule);
	Input* inputSystem = new Input;
	GameTime* timeSystem = new GameTime;

	Engine::getInstance().addSystem(*gameLogicSystem, 1);
	Engine::getInstance().addSystem(*screenSystem, 2);
	Engine::getInstance().addSystem(*renderSystem, 3);
	Engine::getInstance().addSystem(*inputSystem, 4);
	Engine::getInstance().addSystem(*timeSystem, 5);

	std::cout << "Engine::Init()" << std::endl;
}

void Engine::draw()
{
	if(_compInitList.size() > 0)
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

	for (GameObject* gmObj : _gmObjDestroyList) //TODO find more effective solution
	{
		for (Component* comp : gmObj->components_)
		{
			delete comp;
		}

		delete gmObj;
	}


	if (_compInitQueue.size() > 0)
	{
		_compInitList.insert(_compInitList.end(), _compInitQueue.begin(), _compInitQueue.end());
		_compInitQueue.clear();
	}

	_compDestroyList.clear();
	_gmObjDestroyList.clear();
}

void Engine::Resume()
{

}

void Engine::Pause()
{

}

void Engine::addSystem(System &s, int priority)
{
    s.priority = priority;
    _systems.push_back(&s);
	std::sort(_systems.begin(), _systems.end(), pred_sortSystems);
}

void Engine::addGameObject(GameObject &obj)
{
    _gameObjects.push_back(&obj);
}

void Engine::addComponent(Component &comp, int priority)
{
    comp.priority = priority;
    _components.push_back(&comp);
	_compInitQueue.push_back(&comp);

	for (System* s : _systems)
		if (s->isSystemComponent(comp))
			comp.system = s;

	comp.Create();
	ActiveComponent* activeComp = dynamic_cast<ActiveComponent*>(&comp);
	if (activeComp != NULL && activeComp->isEnabled())
		activeComp->OnEnable();
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
	vectorRemove<Component>(_compInitQueue, &comp);
	_compDestroyList.push_back(&comp);
}

GameObject* Engine::FindGameObjectByName(std::string name) const
{
	for (GameObject* obj : _gameObjects)
		if (obj->name == name)
			return obj;

	return NULL;
}

void Engine::Cleanup()
{
	for (GameObject* gmObj : _gameObjects)
	{
		std::cout << "<<<<<<DELETING GAMEOBJECT>>>>>>>>> -------- " << gmObj->name << std::endl;

		for (Component* comp : gmObj->components_)
		{
			std::cout << "<<<<<<DELETING COMPONENT>>>>>>>>> " << std::endl;
			ActiveComponent* activeComp = dynamic_cast<ActiveComponent*>(comp);
			if (activeComp != NULL)
			{
				if (activeComp->isEnabled())
					activeComp->OnDisable();
				activeComp->OnDestroy();
			}

			delete comp;
		}

		delete gmObj;
	}

	for (size_t i = 0, len = _systems.size(); i < len; i++)
	{
		delete _systems[i];
	}

	_gameObjects.clear();
	_components.clear();
	_systems.clear();

	AssetManager::Deinitialize();
}