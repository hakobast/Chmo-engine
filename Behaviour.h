//
//  Behaviour.h
//  EngineTesting
//
//  Created by Hakob on 11/13/14.
//  Copyright (c) 2014 Haksist. All rights reserved.
//

#ifndef EngineTesting_Behaviour_h
#define EngineTesting_Behaviour_h

#include "Component.h"
#include "GameObject.h"
#include <string>

class GameObject;

class Behaviour:public Component
{
	friend class GameObject;
public:
	~Behaviour(){}
    virtual void Init(){};
    virtual void Update(float deltaTime){};
	virtual void OnEnable(){};
	virtual void OnDisable(){};
	virtual void OnAction(std::string action, void*const data){};


	void destroy();
	void setEnabled(bool toogle);
	void sendAction(std::string action, void*const data);
};


inline void Behaviour::setEnabled(bool toogle)
{
	enabled = toogle;
}

inline void Behaviour::destroy()
{
	getGameObject()->removeComponent(this);
}

inline void Behaviour::sendAction(std::string action, void*const data)
{
	gameObject->sendAction(action, data);
}


#endif
