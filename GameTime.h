#ifndef EngineTesting_GameTime_h
#define EngineTesting_GameTime_h

#include <map>
#include "System.h"

class GameTime :public System
{
public:
	static float DeltaTime();
	static int FramesElapsed();
	GameTime(); //TEMP remove this when init function will called
	float timeScale;
protected:
	~GameTime();
	void Init();
	void Update();
	void addComponent(Component &c);
private:
	static GameTime* instance;
	float deltaTime;
	unsigned long prevTime;
	int framesCount;
};

//static functions
inline float GameTime::DeltaTime()
{
	return instance->deltaTime;
}

inline int GameTime::FramesElapsed()
{
	return instance->framesCount;
}
//end
#endif