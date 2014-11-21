
#include <chrono>
#include <iostream>

#include "GameTime.h"

//static variable initialization
GameTime* GameTime::instance = NULL;
//end

unsigned long long timeInMills;

GameTime::GameTime()
{
	instance = this;
	auto duration = std::chrono::system_clock::now().time_since_epoch();
	lastTime = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

GameTime::~GameTime()
{

}

void GameTime::Init()
{
	std::cout << "GameTime System:: Init()" << std::endl;
}

void GameTime::Update()
{
	auto duration = std::chrono::system_clock::now().time_since_epoch();
	timeInMills = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

	deltaTime = (timeInMills - lastTime) / 1000.0f;
	timeSinceGameStarted += deltaTime;
	lastTime = timeInMills;
}

void GameTime::addComponent(Component& c){}