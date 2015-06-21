
#ifndef EngineTesting_GameLogicSystem_h
#define EngineTesting_GameLogicSystem_h

#include <vector>
#include "../CoreEngine/GameLogic.h"
#include "../CoreEngine/System.h"
#include "../Extras/DoubleLinkedList.h"

class GameLogicSystem:public System
{
private:
	DoubleLinkedList<GameLogic> componentsList_;
public:
    ~GameLogicSystem();
    virtual void OnCreate();
	virtual void Update();
	virtual void addComponent(Component &c);
	virtual void removeComponent(Component &c);
	virtual bool isSystemComponent(Component &c);
	virtual std::vector<Component*> getComponents();
protected:
	virtual void OnBufferChange(std::vector<Component*>& components);
};

#endif
