#ifndef EngineTesting_GameTime_h
#define EngineTesting_GameTime_h

#include <map>
#include "System.h"
#include <GL\glut.h>

class GameTime :public System
{
public:
	//TODO implement timeScale
	static GLfloat DeltaTime();
	static GLfloat TimeSinceGameStarted();
	GameTime(); //TEMP remove this when init function will called
protected:
	~GameTime();
	void Init();
	void Update();
private:
	static GameTime* instance;
	unsigned long long lastTime;
	GLfloat deltaTime;
	GLfloat timeSinceGameStarted;
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