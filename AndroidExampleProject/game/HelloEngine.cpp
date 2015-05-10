
#include <iostream>

#include <android/log.h>
#include <time.h>
#include "../../Sources/CoreEngine/ChmoEngine.h"

#define APPNAME "MyApp"

static double now_ms(void)
{
	struct timespec res;
	clock_gettime(CLOCK_REALTIME, &res);
	return 1000.0 * res.tv_sec + (double)res.tv_nsec / 1e6;
}

class HelloEngine : public GameLogic
{
public:
	void Init()
	{
		__android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "HelloEngine: Init()");
		lastTime = now_ms();
	}

	void Update()
	{
		frames++;
		time += (now_ms() - lastTime);
		if (time >= 1000)
		{
			__android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "HelloEngine: FPS %d",frames);
			time = 0;
			frames = 0;
		}

		lastTime = now_ms();
	}

private:
	int frames = 0;
	double time;
	double lastTime = 0;
};