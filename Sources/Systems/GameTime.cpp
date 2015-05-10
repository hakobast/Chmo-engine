
#include <chrono>
#include <iostream>

#include "../Extras/TimeUtils.h"
#include "GameTime.h"

//static variable initialization
GameTime* GameTime::instance_ = NULL;
//end

GameTime::GameTime()
{
	instance_ = this;
	lastTime_ = TimeUtils::Now_Ms();
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
	uint64_t time = TimeUtils::Now_Ms();

	deltaTime_ = (time - lastTime_) / 1000.0f;
	timeSinceGameStarted_ += deltaTime_;
	frame_++;
	lastTime_ = time;
}

void GameTime::addComponent(Component &c){}
void GameTime::removeComponent(Component &c){}
bool GameTime::isSystemComponent(Component &c){ return false; }