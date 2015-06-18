//
//  Engine.h
//  EngineTesting
//
//  Created by Hakob on 11/13/14.
//  Copyright (c) 2014 Haksist. All rights reserved.
//

#include <cassert>
#include <iostream>

#include "Engine.h"
#include "Application.h"
#include "LIBS.h"
#include "ActiveComponent.h"
#include "Utils.h"
#include "GameObject.h"
#include "System.h"
#include "Component.h"
#include "AssetManager.h"
#include "AssetLoader.h"
#include "Display.h"
#include "NativeInput.h"

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
		for (System* s : Engine::GetInstance()._systems)
			s->addComponent(*c);
		c->Init();
		return true;
	}

	return false;
}

void f_Destroy()
{
	Engine::GetInstance().destroy();
}

Engine::~Engine()
{
	Logger::PrintError("Engine::DELETED\n");

	Cleanup(); //TEMP

	for (size_t i = 0, len = _systems.size(); i < len; i++)
	{
		delete _systems[i];
	}

	delete display;
	delete assetLoader;
	delete nativeInput;

	display = NULL;
	assetLoader = NULL;
}

void Engine::create()
{
	if (!isEngineInited_)
	{
#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_MAC)
		atexit(f_Destroy);
		if (glewInit() == GLEW_OK)
			printf("GLEW Inited!\n");
#endif

		RenderSystem* renderSystem = new RenderSystem; //renderer system
		GameLogicSystem* gameLogicSystem = new GameLogicSystem;	//gamelogic system
		ScreenSystem* screenSystem = new ScreenSystem;
		Input* inputSystem = new Input(nativeInput);
		GameTime* timeSystem = new GameTime;
		AssetManager* assetSystem = new AssetManager;

		addSystem(*assetSystem, 0);
		addSystem(*inputSystem, 1);
		addSystem(*gameLogicSystem, 2);
		addSystem(*screenSystem, 3);
		addSystem(*renderSystem, 4);
		addSystem(*timeSystem, 5);

		for (size_t i = 0, len = _systems.size(); i < len; i++)
			_systems[i]->OnCreate();

		isEngineInited_ = true;
		Logger::Print("Engine::Inited\n");

	}

}

void Engine::change(int width, int height)
{
	for (size_t i = 0, len = _systems.size(); i < len; i++)
		_systems[i]->OnScreenChange(width,height);
}

void Engine::draw()
{
	if(_compInitList.size() > 0)
		vectorRemove(_compInitList, pred_initComponents);

	for (System* s : _systems)
		s->OnStartFrame();

	for (System* s : _systems)
		s->Update();

	for (System* s : _systems)
		s->OnEndFrame();

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

//TODO load graphic resources
void Engine::resume()
{
	Logger::PrintError("ENGINE::Resume");

	for (size_t i = 0, len = _systems.size(); i < len; i++)
		_systems[i]->OnResume();
}

//TODO unload graphic resources
void Engine::pause() 
{
	Logger::PrintError("ENGINE::Pause");

	for (size_t i = 0, len = _systems.size(); i < len; i++)
		_systems[i]->OnPause();

	//TEMPPPPPPPPPPPPPPP
	delete instance_;
	instance_ = NULL;
}

//TODO cleanup objects, resources and destroy engine
void Engine::destroy()
{
	Logger::PrintError("ENGINE::Destroy");

 	for (size_t i = 0, len = _systems.size(); i < len; i++)
 		_systems[i]->OnDestroy();

	delete instance_;
	instance_ = NULL;
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
	{
		if (s->isSystemComponent(comp))
		{
			comp.system = s;
			break;
		}
	}

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

	_gameObjects.clear();
	_components.clear();
}