#ifndef ANDROID_DISPLAY_MODULE_H
#define ANDROID_DISPLAY_MODULE_H

#include "Display.h"

class Engine;

class AndroidDisplay : public Display
{
public:
	AndroidDisplay(Engine* engine);
	virtual void create();
	virtual void change(int width, int height);
	virtual void draw();
	virtual void pause();
	virtual void resume();
	virtual void destroy();
private:
	Engine* engine_;
};
#endif