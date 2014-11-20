
#include <chrono>
#include <iostream>

#include "GameTime.h"

//static variable initialization
GameTime* GameTime::instance = NULL;
//end

GameTime::GameTime()
{
	instance = this;
}

GameTime::~GameTime()
{

}

void GameTime::Init()
{
	/*prevTime = std::chrono::system_clock::now().time_since_epoch() /
		std::chrono::milliseconds(1);*/
}

void GameTime::Update()
{
	/*unsigned long now = std::chrono::system_clock::now().time_since_epoch() /
		std::chrono::milliseconds(1);*/

	//deltaTime = (now - prevTime) / 1000.0f;
	//prevTime = now;

	//std::cout << "deltaTime " << deltaTime<< std::endl;
}

void GameTime::addComponent(Component& c){}