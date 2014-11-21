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
	~ActiveComponent(){};
public:
	virtual void OnEnable(){};
	virtual void OnDisable(){};

	void destroy();
	void setEnabled(bool toogle);
};


inline void ActiveComponent::setEnabled(bool toogle)
{
	enabled = toogle;
	if (enabled)
		OnEnable();
	else
		OnDisable();
}

inline void ActiveComponent::destroy()
{
	getGameObject()->removeComponent(this);
}

#endif
