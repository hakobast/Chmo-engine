

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <vector>
#include <string>

#include "Engine.h"
#include "Transform.h"
#include "ActiveComponent.h"
#include "../Extras/DoubleLinkedList.h"

class Transform;

class GameObject
{
friend class Component;
friend class Engine;
friend class ActiveComponent;

private:
	std::string name_;
	std::string tag_;
	bool isActive_ = true;
	bool isDestroying = false;
	Transform* transform_ = 0;
	DoubleLinkedList<Component> componentsList_;
	Node<GameObject>* node_ = 0;

	~GameObject();
	void removeComponent(Component* component);
public:
	static GameObject*							FindGameObjectByName(std::string name);
	template<class T> static T*					FindComponent();
	template<class T> static std::vector<T*>	FindComponents();

	GameObject(std::string name);
    
	template<class T> T*				addComponent();
	template<class T> T*				getComponent(bool enabledOnly = false);
	template<class T> std::vector<T*>	getComponents(bool enabledOnly = false);

	Transform*const getTransform();
	std::string		getName();
	std::string		getTag();
	void			setName(std::string newName);
	void			setTag(std::string newTag);
	void			sendAction	(std::string action, void*const data);
    void			setActive	(bool toogle);
    bool			isActive	();
    void			destroy		();

	friend std::ostream& operator << (std::ostream& stream, const GameObject& obj);
};

inline std::ostream& operator << (std::ostream& stream, const GameObject& obj)
{
	return stream << obj.name_ << " GameObject" << std::endl;
}

inline std::string GameObject::getName()
{
	return name_;
}

inline std::string GameObject::getTag()
{
	return tag_;
}

inline void GameObject::setName(std::string newName)
{
	name_ = newName;
}

inline void GameObject::setTag(std::string newTag)
{
	tag_ = newTag;
}

inline Transform*const GameObject::getTransform()
{
	return transform_;
}

inline bool GameObject::isActive()
{
    return isActive_;
}

template<class T>
T* GameObject::addComponent()
{
	if (std::is_base_of<Component, T>::value && !std::is_base_of<Transform, T>::value)
	{
		T *t = new T();
		Component* baseType = t;
		baseType->gameObject_ = this;
		baseType->transform_ = getTransform();

		componentsList_.addToBack(baseType->node_);

		Engine::GetInstance().addComponent(baseType);
		baseType->Create();

		ActiveComponent* activeComp = dynamic_cast<ActiveComponent*>(baseType);
		if (!isDestroying && activeComp)
		{
			if (isActive())
				activeComp->OnEnable();
			else
				activeComp->OnDisable();
		}
		else if (isDestroying) //if the gameobject is in destroy state added component must be destroyed
		{
			if (activeComp != NULL)
				activeComp->destroy();
			else
				Engine::GetInstance().removeComponent(baseType);
		}

		return t;
	}

	return NULL;
}

template<class T>
T* GameObject::getComponent(bool enabledOnly)
{
	DoubleLinkedList<Component>::iterator iter = componentsList_.getIterator();
	while (iter.hasNext())
	{
		Node<Component>* node = iter.next();
		if (dynamic_cast<T*>(node->data) && (!enabledOnly || node->data->isEnabled()))
			return (T*)node->data;
	}

	return NULL;
}

template<class T>
std::vector<T*> GameObject::getComponents(bool enabledOnly)
{
	std::vector<T*> comps;
	DoubleLinkedList<Component>::iterator iter = componentsList_.getIterator();
	while (iter.hasNext())
	{
		Node<Component>* node = iter.next();
		if (dynamic_cast<T*>(node->data) && (!enabledOnly || node->data->isEnabled()))
			comps.push_back((T*)node->data);
	}

	return comps;
}

////////////STATICS//////////////
template<class T>
T* GameObject::FindComponent()
{
	return Engine::GetInstance().FindComponent<T>();
}

template<class T>
std::vector<T*> GameObject::FindComponents()
{
	return Engine::GetInstance().FindComponents<T>();
}

#endif
