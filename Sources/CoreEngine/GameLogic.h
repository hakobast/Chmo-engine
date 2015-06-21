
#ifndef EngineTesting_GameLogic_h
#define EngineTesting_GameLogic_h

#include <string>

#include "Component.h"
#include "GameObject.h"
#include "ActiveComponent.h"
#include "../Components/Renderer.h"
#include "../Extras/DoubleLinkedList.h"

class GameLogic :public ActiveComponent
{
friend class GameLogicSystem;
private:
	Node<GameLogic>* logicSystemNode_ = 0;
public:
	GameLogic(){ logicSystemNode_ = new Node<GameLogic>(this); }
	virtual ~GameLogic(){ delete logicSystemNode_; logicSystemNode_ = NULL; };
	virtual void OnAction(std::string action, void*const data){};
	void sendAction(std::string action, void*const data);
};

inline void GameLogic::sendAction(std::string action, void*const data)
{
	getGameObject()->sendAction(action, data);
}

#endif
