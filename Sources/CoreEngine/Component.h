
#ifndef COMPONENT_H
#define COMPONENT_H

#include <typeinfo>
#include <string>
#include <iostream>

#include "../Extras/DoubleLinkedList.h"

class Transform;
class GameObject;
class System;

class Component
{
	friend class GameObject;
	friend class Engine;
private:
	GameObject*		gameObject_ = 0;
	Transform*		transform_ = 0;
	Node<Component>* node_ = 0;

public:
	Component();
	virtual ~Component();
	virtual void Create(){};
	virtual void Init(){};
	virtual void Update(){};
	virtual bool isEnabled() const;

	/////////////Implement Generic methods/////////////////

	///////////////////////////////////////////////////////

	GameObject*const	getGameObject() const;
	Transform*const		getTransform() const;
	std::string			getName();
	std::string			getTag();
	void				setName(std::string newName);
	void				setTag(std::string newTag);

friend std::ostream& operator << (std::ostream& stream, const Component& obj);
};

inline std::ostream& operator << (std::ostream& stream, const Component& obj)
{
	return stream << typeid(&obj).name() << " Component(" << obj.isEnabled() << ")" << std::endl;
}

inline bool Component::isEnabled() const
{
	return true; 
}

inline GameObject*const Component::getGameObject() const
{
	return gameObject_;
}

inline Transform*const Component::getTransform() const
{
	return transform_;
}

#endif