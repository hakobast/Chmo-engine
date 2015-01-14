#ifndef EngineTesting_GameTime_h
#define EngineTesting_GameTime_h

#include <map>

#include "GL_LIBS.h"
#include "System.h"

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
	void addComponent(Component &c);
	void removeComponent(Component &c);
	bool isSystemComponent(Component &c);
private:
	static GameTime* instance;
	unsigned long long lastTime;
	GLfloat deltaTime;
	GLfloat timeSinceGameStarted = 0;
};

//static functions
inline GLfloat GameTime::DeltaTime()
{
	return instance->deltaTime;
}

inline GLfloat GameTime::TimeSinceGameStarted()
{
	return instance->timeSinceGameStarted;
}
//end
#endif