#ifndef GAMETIME_H
#define GAMETIME_H

#include <inttypes.h>

#include "../CoreEngine/LIBS.h"
#include "../CoreEngine/System.h"

//#TODO implement timeScale
class GameTime :public System
{
public:
	static float DeltaTime();
	static float TimeSinceGameStarted();
	static unsigned int GetFrame();
	GameTime();
protected:
	~GameTime();
	virtual void OnCreate();
	virtual void Update();
private:
	static GameTime* instance_;
	uint64_t lastTime_;
	float deltaTime_ = 0;
	float timeSinceGameStarted_ = 0;
	unsigned int frame_ = 0;
};

//static functions
inline float GameTime::DeltaTime()
{
	return instance_->deltaTime_;
}

inline float GameTime::TimeSinceGameStarted()
{
	return instance_->timeSinceGameStarted_;
}

inline unsigned int GameTime::GetFrame()
{
	return instance_->frame_;
}

//end
#endif