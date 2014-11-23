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
protected:
	virtual ~Component(){};
	bool enabled = true;
public:
    int priority;
	virtual void Create(){};
	virtual void Init(){};
	virtual void Update(){};
	bool isEnabled() const;
	GameObject*const getGameObject() const;
	GameTransform*const getTransform() const;
private:
	GameObject* gameObject;
	GameTransform* transform;
};

inline bool Component::isEnabled() const
{
	return enabled;
}

inline GameObject*const Component::getGameObject() const
{
	return gameObject;
}

inline GameTransform*const Component::getTransform() const
{
	return transform;
}

#endif