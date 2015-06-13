
#ifndef EngineTesting_GameLogic_h
#define EngineTesting_GameLogic_h

#include <string>

#include "Component.h"
#include "GameObject.h"
#include "ActiveComponent.h"
#include "../Components/Renderer.h"

class GameLogic :public ActiveComponent
{
friend class GameObject;
friend class GameLogicSystem;
protected:
	virtual ~GameLogic(){};
public:
	virtual void OnAction(std::string action, void*const data){};
	void sendAction(std::string action, void*const data);
};

inline void GameLogic::sendAction(std::string action, void*const data)
{
	getGameObject()->sendAction(action, data);
}

#endif
