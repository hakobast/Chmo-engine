
#ifndef EngineTesting_Engine_h
#define EngineTesting_Engine_h

#include <vector>
#include <iostream>
#include <string>

class System;
class Component;
class GameObject;

class Engine
{
friend class GameObject;
public:
	~Engine();
    void Init();
	void Update();
	void Resume();
	void Pause();
	void ScreenChange(int width, int height);
    void addSystem(System &s, int priority);
    void addGameObject(GameObject &obj);
    void addComponent(Component &comp, int priority);
	void removeGameObject(GameObject &obj);
	void removeComponent(Component &comp);
	GameObject* FindGameObjectByName(std::string name) const;
	template<class T> T* FindComponent() const;
	template<class T> std::vector<T*> FindComponents() const;

	static Engine& getInstance()
	{
		static Engine engine;
		return engine;
	}

private:
	std::vector<Component*> _compInitList; 
	std::vector<Component*> _compInitQueue;
	std::vector<Component*> _compDestroyList;
	std::vector<GameObject*> _gmObjDestroyList;

    std::vector<Component*> _components;
    std::vector<GameObject*> _gameObjects;
    std::vector<System*> _systems;

	Engine()
	{
		std::cout << "ENGINE created" << std::endl;
	}

	void Cleanup();

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