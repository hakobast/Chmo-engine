#ifndef FPSCOUNTER_CPP
#define FPSCOUNTER_CPP

#include "EngineInclude.h"

#include <iostream>

class FPSCounter : public GameLogic
{
	GLfloat time = 0;
	int frames = 0;
public:
	void Update()
	{
		time += GameTime::DeltaTime();
		frames++;
		if (time >= 1)
		{
			Logger::Print("FPS:: %1.1f\n", frames/time);
			frames = 0;
			time = 0;
		}
	}
};
#endif