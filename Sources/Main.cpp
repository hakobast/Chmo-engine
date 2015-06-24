

#include <iostream>
#include <chrono>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <memory>

#include "CoreEngine/ChmoEngine.h"
#include "Extras/GLUtils.h"

#include "CoreEngine/GLUTDisplay.h"
#include "CoreEngine/GLUTInput.h"
#include "CoreEngine/WinAssetLoader.h"

#include "Testings/GameController.h"

#define TARGET_FPS 60

void CreateGame();

int main(int argc, char **argv)
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//creating engine
	Engine* engine = new Engine;

	GLUTInput* nativeInput = new GLUTInput;
	engine->nativeInput = nativeInput;

	WinAssetLoader* assetLoader = new WinAssetLoader;
	engine->assetLoader = assetLoader;

	GLUTDisplay* displayModule = new GLUTDisplay(engine, &argc, argv, GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH, 800, 600, "ENGINE");
	engine->display = displayModule;
	displayModule->create();

	CreateGame();

	glutMainLoop(); //TEMP

	return 0;
}

void CreateGame()
{
	GameController* gameController = (new GameObject("GameController"))->addComponent<GameController>();
	gameController->spaceShipType = STANDART;
}