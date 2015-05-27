#ifndef EngineTesting_GameTime_h
#define EngineTesting_GameTime_h

#include <inttypes.h>

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
	static GameTime* instance_;
	uint64_t lastTime_;
	GLfloat deltaTime_ = 0;
	GLfloat timeSinceGameStarted_ = 0;
	GLuint frame_ = 0;
};

//static functions
inline GLfloat GameTime::DeltaTime()
{
	return instance_->deltaTime_;
}

inline GLfloat GameTime::TimeSinceGameStarted()
{
	return instance_->timeSinceGameStarted_;
}

inline GLuint GameTime::GetFrame()
{
	return instance_->frame_;
}

//end
#endif