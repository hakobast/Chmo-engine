
#ifndef ENGINE_H
#define ENGINE_H

#include <vector>
#include <queue>
#include <iostream>
#include <string>

#include "System.h"
#include "../Extras/DoubleLinkedList.h"
#include "../Extras/Singleton.h"

class Component;
class GameObject;
class Display;
class AssetLoader;
class NativeInput;

class Engine : public Singleton<Engine>
{
friend class GameObject;
private:
	DoubleLinkedList<GameObject> gameObjectsList_;
	std::queue<Component*> componentsToDestroy_;
	std::queue<GameObject*> gameobjectsToDestroy_;
	std::vector<System*> systems_;
	bool isEngineInited_ = false;

	~Engine();

	void Cleanup();
public:
	Display* display = 0;
	AssetLoader* assetLoader = 0;
	NativeInput* nativeInput = 0;

    void addSystem(System* s, int priority);
    void addGameObject(GameObject* obj);
    void addComponent(Component* comp);
	void removeGameObject(GameObject* obj);
	void removeComponent(Component* comp);
	GameObject* FindGameObjectByName(std::string name);
	template<class T> T* FindComponent();
	template<class T> std::vector<T*> FindComponents();

	void create();
	void change(int width, int height);
	void draw();
	void resume();
	void pause();
	void destroy();

	friend void f_Destroy();
};

template<class T>
T* Engine::FindComponent()
{
	for (System* system : systems_)
	{
		std::vector<Component*> components = system->getComponents();
		for (Component* comp : components)
			if (dynamic_cast<T*>(comp))
				return (T*)comp;
	}

	return NULL;
}

template<class T>
std::vector<T*> Engine::FindComponents()
{
	std::vector<T*> comps;
	for (System* system : systems_)
	{
		std::vector<Component*> tempComps = system->getComponents();
		for (Component* comp : tempComps)
			if (dynamic_cast<T*>(comp))
				comps.push_back((T*)comp);
	}

	return comps;
}

#endif