
#include <iostream>

#include "../../Sources/CoreEngine/ChmoEngine.h"

class HelloEngine : public GameLogic
{
public:
	void Init()
	{

	}

	void Update()
	{
		frames++;
		time += GameTime::DeltaTime();

		if (time >= 1.0f)
		{
			Logger::Print("FPS %d", frames);
			Logger::PrintWarning("WARNING FPS %d", frames);
			Logger::PrintError("ERROR FPS %d", frames);

			Logger::Print("TIME %f", (double)TimeUtils::Now_Ms());
			Logger::Print("DELTA TIME %f", GameTime::DeltaTime());
			Logger::Print("TIME SINCE STARTED %f", GameTime::TimeSinceGameStarted());

			time = 0;
			frames = 0;
		}
	}

private:
	int frames = 0;
	GLfloat time;
};