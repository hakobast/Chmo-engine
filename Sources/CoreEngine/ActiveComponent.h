//
//  Behaviour.h
//  EngineTesting
//
//  Created by Hakob on 11/13/14.
//  Copyright (c) 2014 Haksist. All rights reserved.
//

#ifndef EngineTesting_ActiveComponent_h
#define EngineTesting_ActiveComponent_h

#include "Component.h"
#include "GameObject.h"
#include <string>

class GameObject;

class ActiveComponent :public Component
{
	friend class GameObject;
protected:
	~ActiveComponent()
	{
		std::cout << "ActiveComponent: ~~~~~~~~~~~~~" << std::endl;
	};
private:
	bool enabled = true;
	bool destroyState = false; //is is for performance reason, if system's list will be a MAP remove this variable
	void _destroy();
public:
	virtual void OnEnable(){/* std::cout << "ActiveComponent: OnEnable" << std::endl;*/ };
	virtual void OnDisable(){ /*std::cout << "ActiveComponent: OnDisable" << std::endl;*/ };
	virtual void OnDestroy(){};
	bool isEnabled() const;
	void destroy();
	void setEnabled(bool toogle);
};

inline bool ActiveComponent::isEnabled() const
{
	return enabled && getGameObject()->isActive();
}

inline void ActiveComponent::setEnabled(bool toogle)
{
	if (enabled == toogle || !getGameObject()->isActive())
		return;

	enabled = toogle;
	if (enabled)
	{
		OnEnable();
		if (system != NULL && !destroyState)
			system->addComponent(*this);
	}
	else
	{
		OnDisable();
		if (system != NULL && !destroyState)
			system->removeComponent(*this);
	}
}

inline void ActiveComponent::destroy()
{
	destroyState = true;
	getGameObject()->removeComponent(this);
	if (system != NULL)
		system->removeComponent(*this);
}

inline void ActiveComponent::_destroy()
{
	destroyState = true;
	if (system != NULL)
		system->removeComponent(*this);
}

#endif
