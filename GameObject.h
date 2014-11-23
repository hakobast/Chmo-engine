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
#include "Engine.h"

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

	//statics
	static GameObject* FindGameObjectByName(std::string name);
	template<class T>
	static T* FindComponent();
	template<class T>
	static std::vector<T*> FindComponents();

	void sendAction(std::string action, void*const data);
	void sendMessage(std::string function, void *data);
	GameTransform*const getTransform();
    void setActive(bool toogle);
    bool isActive() const;
    void destroy();
    
private:
    bool _isActive = true;
	GameTransform* transform;
    std::vector<Component*> components;
	void removeComponent(Component *);
};

inline bool GameObject::isActive()const
{
    return _isActive;
}

inline GameTransform*const GameObject::getTransform()
{
	return transform;
}

#include "GameObjectTemplates.h"

#endif
