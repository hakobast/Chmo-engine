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

static bool sortSystems(const System* lhs, const System* rhs) { return lhs->priority < rhs->priority; }

class Engine
{
friend class GameObject;
public:
    void Init();
    void Update();
    void addSystem(System &s, int priority);
    void addGameObject(GameObject &obj);
    void addComponent(Component &comp, int priority);
	void removeSystem(System &s);
	void removeGameObject(GameObject &obj);
	void removeComponent(Component &comp);
	void print();

	/*GameObject* FindGameObjectByName(std::string name) const;
	template<class T>
	T* FindComponent();
	template<class T>
	std::vector<T*> FindComponents();*/

	static inline Engine& getInstance()
	{
		static Engine engine;
		return engine;
	}
private:
	std::vector<Component*> componentsToInit;
    std::vector<Component*> components;
    std::vector<GameObject*> gameObjects;
    std::vector<System*> systems;
    int frameRate;

	Engine()
	{
		std::cout << "ENGINE created" << std::endl;
	}
};

/*GameObject* Engine::FindGameObjectByName(std::string name) const
{
	for (GameObject* obj : gameObjects)
		if (obj->name == name)
			return obj;

	return NULL;
}

template<class T>
T* Engine::FindComponent()
{
	for (Component* comp : components)
		if (dynamic_cast<T>(comp))
			return comp;

	return NULL;
}

template<class T>
std::vector<T*> Engine::FindComponents()
{
	std::vector<T*> comps;
	for (Component* comp : components)
		if (dynamic_cast<T>(comp))
			comps.push_back(comp);

	return comps;
}*/
#endif