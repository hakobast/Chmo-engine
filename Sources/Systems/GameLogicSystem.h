
#ifndef EngineTesting_GameLogicSystem_h
#define EngineTesting_GameLogicSystem_h

#include <vector>
#include "../CoreEngine/GameLogic.h"
#include "../CoreEngine/System.h"

class GameLogicSystem:public System
{
private:
	std::vector<GameLogic*> components;
public:
    ~GameLogicSystem();
    virtual void OnCreate();
	virtual void Update();
	virtual void addComponent(Component &c);
	virtual void removeComponent(Component &c);
	virtual bool isSystemComponent(Component &c);
};

#endif
