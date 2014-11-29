#include "GameLogic.h"
#include "GameTime.h"

#include <iostream>

class FPSCounter : public GameLogic
{
	float time;
	int frames;
public:
	void Update()
	{
		time += GameTime::DeltaTime();
		frames++;
		if (time >= 1)
		{
			std::cout << "FPS:" << frames << std::endl;
			frames = 0;
			time = 0;
		}
	}
};