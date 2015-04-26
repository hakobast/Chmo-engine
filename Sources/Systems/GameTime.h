#ifndef EngineTesting_GameTime_h
#define EngineTesting_GameTime_h

#include "../CoreEngine/LIBS.h"
#include "../CoreEngine/System.h"

class GameTime :public System
{
public:
	//TODO implement timeScale
	static GLfloat DeltaTime();
	static GLfloat TimeSinceGameStarted();
	static GLuint GetFrame();
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
	GLfloat deltaTime = 0;
	GLfloat timeSinceGameStarted = 0;
	GLuint frame = 1;
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

inline GLuint GameTime::GetFrame()
{
	return instance->frame;
}

//end
#endif