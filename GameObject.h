//
//  GameObject.h
//  EngineTesting
//
//  Created by Hakob on 11/13/14.
//  Copyright (c) 2014 Haksist. All rights reserved.
//

#ifndef EngineTesting_GameObject_h
#define EngineTesting_GameObject_h


#include <vector>
#include <string>
#include "Component.h"
#include "Transform.h"

class GameObject
{
friend class Component;
friend class ActiveComponent;

protected:
	~GameObject();
public:
    std::string name;
	std::string tag;
    
	GameObject(std::string name);
    
	template<class T>
	T* addComponent();
	template<class T>
	T* getComponent(bool enabledOnly = false) const;
	template<class T>
	std::vector<T*> getComponents(bool enabledOnly = false) const;
	
	void sendAction(std::string action, void*const data);
	void sendMessage(std::string function, void *data);
    void setActive(bool toogle);
    bool isActive() const;
    void destroy();
    
private:
    bool _isActive = true;
    std::vector<Component*> components;
	void removeComponent(Component *);
};

inline bool GameObject::isActive()const
{
    return _isActive;
}

template<class T>
T* GameObject::addComponent()
{
	if (std::is_base_of<Component, T>::value)
	{
		T *t = new T();
		Component* baseType = t;
		baseType->gameObject = this; 
		baseType->transform = (GameTransform*)components[0]; // first component of each gameobject is GameTransform

		components.push_back(baseType);
		Engine::getInstance().addComponent(*baseType,baseType->priority);
		return t;
	}

	return NULL;
}

template<class T>
T* GameObject::getComponent(bool enabledOnly) const
{
	for (int i = 0; i < components.size(); i++)
	{
		if (dynamic_cast<T*>(components[i]) && (!enabledOnly || components[i]->isEnabled()))
		{
			return (T*)components[i];
		}
	}	

	return NULL;
}

template<class T>
std::vector<T*> GameObject::getComponents(bool enabledOnly)  const
{
	std::vector<T*const> comps;
	for (int i = 0; i < components.size(); i++)
	{
		if (dynamic_cast<T*>(components[i]) && (!enabledOnly || components[i]->isEnabled()))
		{
			comps.push_back((T*)components[i]);
		}
	}

	return comps;
}

#endif
