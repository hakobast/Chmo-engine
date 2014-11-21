#ifndef EngineTesting_GameTime_h
#define EngineTesting_GameTime_h

#include <map>
#include "System.h"

class GameTime :public System
{
public:
	//TODO implement timeScale
	static float DeltaTime();
	static float TimeSinceGameStarted();
	GameTime(); //TEMP remove this when init function will called
protected:
	~GameTime();
	void Init();
	void Update();
	void addComponent(Component &c);
private:
	static GameTime* instance;
	unsigned long long lastTime;
	float deltaTime;
	float timeSinceGameStarted;
};

//static functions
inline float GameTime::DeltaTime()
{
	return instance->deltaTime;
}

inline float GameTime::TimeSinceGameStarted()
{
	return instance->timeSinceGameStarted;
}
//end
#endif