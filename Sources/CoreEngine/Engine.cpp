//
//  Engine.h
//  EngineTesting
//
//  Created by Hakob on 11/13/14.
//  Copyright (c) 2014 Haksist. All rights reserved.
//

#include <cassert>
#include <assert.h>
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

void f_Destroy()
{
	Engine::GetInstance().destroy();
}

Engine::~Engine()
{
	Logger::PrintError("Engine::Deleted\n");

	DoubleLinkedList<GameObject>::iterator gameObjectIter = gameObjectsList_.getIterator();
	while (gameObjectIter.hasNext())
		gameObjectIter.next()->data->destroy();

	while (componentsToDestroy_.size() > 0)
	{
		ActiveComponent* activeComp = dynamic_cast<ActiveComponent*>(componentsToDestroy_.front());
		if (activeComp != NULL)
			activeComp->OnDestroy();

		delete componentsToDestroy_.front();
		componentsToDestroy_.pop();
	}

	while (gameobjectsToDestroy_.size() > 0)
	{
		delete gameobjectsToDestroy_.front();
		gameobjectsToDestroy_.pop();
	}

	for (size_t i = 0, len = systems_.size(); i < len; i++)
		delete systems_[i];

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
		assert(glewInit() == GLEW_OK);
#endif

		RenderSystem* renderSystem = new RenderSystem;
		GameLogicSystem* gameLogicSystem = new GameLogicSystem;
		ScreenSystem* screenSystem = new ScreenSystem;
		Input* inputSystem = new Input(nativeInput);
		GameTime* timeSystem = new GameTime;
		AssetManager* assetSystem = new AssetManager;

		addSystem(assetSystem, 0);
		addSystem(inputSystem, 1);
		addSystem(gameLogicSystem, 2);
		addSystem(screenSystem, 3);
		addSystem(renderSystem, 4);
		addSystem(timeSystem, 5);

		for (size_t i = 0, len = systems_.size(); i < len; i++)
			systems_[i]->OnCreate();

		isEngineInited_ = true;
		Logger::Print("Engine::Inited\n");
	}
}

void Engine::change(int width, int height)
{
	for (size_t i = 0, len = systems_.size(); i < len; i++)
		systems_[i]->OnScreenChange(width,height);
}

void Engine::draw()
{
	for (System* s : systems_)
		s->OnStartFrame();

	for (System* s : systems_)
		s->Update();

	for (System* s : systems_)
		s->OnEndFrame();

	while (componentsToDestroy_.size() > 0)
	{
		if (ActiveComponent* activeComp = dynamic_cast<ActiveComponent*>(componentsToDestroy_.front()))
			activeComp->OnDestroy();

		delete componentsToDestroy_.front();
		componentsToDestroy_.pop();
	}

	while (gameobjectsToDestroy_.size() > 0)
	{
		delete gameobjectsToDestroy_.front();
		gameobjectsToDestroy_.pop();
	}
}

//#TODO load graphic resources
void Engine::resume()
{
	Logger::PrintError("Engine::Resume");

	for (size_t i = 0, len = systems_.size(); i < len; i++)
		systems_[i]->OnResume();
}

//#TODO unload graphic resources
void Engine::pause() 
{
	Logger::PrintError("Engine::Pause");

	for (size_t i = 0, len = systems_.size(); i < len; i++)
		systems_[i]->OnPause();

	//TEMP destroy function sometimes not called, find solution for that and remove this lines
	delete instance_;
	instance_ = NULL;
}

//#TODO cleanup objects, resources and destroy engine
void Engine::destroy()
{
	Logger::PrintError("Engine::Destroy");

 	for (size_t i = 0, len = systems_.size(); i < len; i++)
 		systems_[i]->OnDestroy();

	delete instance_;
	instance_ = NULL;
}

void Engine::addSystem(System* s, int priority)
{
    s->priority = priority;
    systems_.push_back(s);
	std::sort(systems_.begin(), systems_.end(), pred_sortSystems);
}

void Engine::addGameObject(GameObject* obj)
{
	gameObjectsList_.addToBack(obj->node_);
}

void Engine::addComponent(Component* comp)
{
	for (System* system : systems_)
		if (system->isSystemComponent(*comp))
			system->addComponent(*comp);
}

void Engine::removeGameObject(GameObject* obj)
{
	if (obj->node_ == NULL)
		return;

	gameObjectsList_.remove(obj->node_);
	gameobjectsToDestroy_.push(obj);
}

void Engine::removeComponent(Component* comp)
{
	for (System* system : systems_)
		if (system->isSystemComponent(*comp))
			system->removeComponent(*comp);

	componentsToDestroy_.push(comp);
}

GameObject* Engine::FindGameObjectByName(std::string name)
{
	DoubleLinkedList<GameObject>::iterator iter = gameObjectsList_.getIterator();
	while (iter.hasNext())
	{
		Node<GameObject>* node = iter.next();
		if (node->data->getName() == name)
			return node->data;
	}

	return NULL;
}

void Engine::Cleanup()
{
	//#TEMP this will call components callbacks in wrong order
//	DoubleLinkedList<GameObject>::iterator gameObjectIter = gameObjectsList_.getIterator();
// 	while (gameObjectIter.hasNext())
// 	{
// 		Node<GameObject>* gameObjectNode = gameObjectIter.next();
// 
// 		DoubleLinkedList<Component>::iterator componentIter = gameObjectNode->data->componentsList_.getIterator();
// 		while (componentIter.hasNext())
// 		{
// 			Node<Component>* componentNode = componentIter.next();
// 			ActiveComponent* activeComp = dynamic_cast<ActiveComponent*>(componentNode->data);
// 			if (activeComp != NULL)
// 			{
// 				if (activeComp->isEnabled())
// 					activeComp->OnDisable();
// 			}
// 		}
// 	}
}