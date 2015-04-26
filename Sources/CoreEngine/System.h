
#ifndef EngineTesting_System_h
#define EngineTesting_System_h

#include <vector>

#include "Utils.h"
#include "Component.h"

class System
{
friend class Engine;

public:
	int priority;
protected:
	virtual ~System(){};
	virtual void Init() = 0; //INFO this function maybe not usable
    virtual void Update() = 0;
public:
	virtual void addComponent(Component &c) = 0;
	virtual void removeComponent(Component &c) = 0;
	virtual bool isSystemComponent(Component &c) = 0;
};

#endif
