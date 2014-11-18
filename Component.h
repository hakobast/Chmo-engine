//
//  Component.h
//  EngineTesting
//
//  Created by Hakob on 11/13/14.
//  Copyright (c) 2014 Haksist. All rights reserved.
//

#ifndef EngineTesting_Component_h
#define EngineTesting_Component_h

class GameObject;
class GameTransform;

class Component
{
	friend class GameObject;
public:
    int priority;
    virtual ~Component(){}
    virtual void Init(){};
    virtual void Update(float deltaTime){};
	bool isEnabled() const;
	GameObject*const getGameObject();
	GameTransform*const getTransform();
protected:
	bool enabled = true;
	GameObject* gameObject;
	GameTransform* transform;
};

inline bool Component::isEnabled() const
{
	return enabled;
}

inline GameObject*const Component::getGameObject()
{
	return gameObject;
}

inline GameTransform*const Component::getTransform()
{
	return transform;
}

#endif
