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

	GameObject* FindGameObjectByName(std::string name) const;
	template<class T>
	T* FindComponent() const;
	template<class T>
	std::vector<T*> FindComponents() const;

	static inline Engine& getInstance()
	{
		static Engine engine;
		return engine;
	}
private:
	std::vector<Component*> _compInitList;
	std::vector<Component*> _compDestroyList;
	std::vector<GameObject*> _gmObjDestroyList;

    std::vector<Component*> _components;
    std::vector<GameObject*> _gameObjects;
    std::vector<System*> _systems;

	Engine()
	{
		std::cout << "ENGINE created" << std::endl;
	}
};

//****STATICS*****
template<class T>
T* Engine::FindComponent() const
{
	for (Component* comp : _components)
	if (dynamic_cast<T*>(comp))
		return (T*)comp;

	return NULL;
}

template<class T>
std::vector<T*> Engine::FindComponents() const
{
	std::vector<T*> comps;
	for (Component* comp : _components)
	if (dynamic_cast<T*>(comp))
		comps.push_back((T*)comp);

	return comps;
}

#endif