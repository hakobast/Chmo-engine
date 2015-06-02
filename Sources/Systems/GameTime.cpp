
#include <chrono>
#include <iostream>

#include "../Extras/TimeUtils.h"
#include "../Debug/Logger.h"
#include "GameTime.h"

//static variable initialization
GameTime* GameTime::instance_ = NULL;
//end

GameTime::GameTime()
{
	instance_ = this;
}

GameTime::~GameTime()
{

}

void GameTime::OnCreate()
{
	std::cout << "GameTime System:: Init()" << std::endl;
	lastTime_ = TimeUtils::Now_Ms();
}

void GameTime::Update()
{
	uint64_t time = TimeUtils::Now_Ms();

	deltaTime_ = (time - lastTime_) / 1000.0f;
	timeSinceGameStarted_ += deltaTime_;
	frame_++;
	lastTime_ = time;
}