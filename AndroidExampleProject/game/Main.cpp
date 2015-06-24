
#include "Logic/EngineInclude.h"
#include "Logic/GameController.h"

void Main()
{
	GameController* gameController = (new GameObject("GameController"))->addComponent<GameController>();
	gameController->spaceShipType = STANDART;
}