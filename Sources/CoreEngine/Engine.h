
#ifndef EngineTesting_Engine_h
#define EngineTesting_Engine_h

#include <vector>
#include <iostream>
#include <string>

#include "DisplayModuleObserver.h"
#include "../Extras/Singleton.h"

class System;
class Component;
class GameObject;
class DisplayModule;
class AssetLoader;

class Engine : public Singleton<Engine>
{
friend class GameObject;
public:
	DisplayModule* displayModule = 0;
	AssetLoader* assetLoader = 0;

    void addSystem(System &s, int priority);
    void addGameObject(GameObject &obj);
    void addComponent(Component &comp, int priority);
	void removeGameObject(GameObject &obj);
	void removeComponent(Component &comp);
	GameObject* FindGameObjectByName(std::string name) const;
	template<class T> T* FindComponent() const;
	template<class T> std::vector<T*> FindComponents() const;

	void create();
	void change(int width, int height);
	void resume();
	void pause();
	void destroy();
	void draw();
private:
	~Engine();

	std::vector<Component*> _compInitList; 
	std::vector<Component*> _compInitQueue;
	std::vector<Component*> _compDestroyList;
	std::vector<GameObject*> _gmObjDestroyList;

    std::vector<Component*> _components;
    std::vector<GameObject*> _gameObjects;
    std::vector<System*> _systems;
	bool isEngineInited_ = false;

	void Cleanup(); //TEMP

	friend void f_Destroy();
	friend bool pred_initComponents(Component* c);
};

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