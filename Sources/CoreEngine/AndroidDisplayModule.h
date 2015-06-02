#ifndef ANDROID_DISPLAY_MODULE_H
#define ANDROID_DISPLAY_MODULE_H

#include "DisplayModule.h"

class Engine;

class AndroidDisplayModule : public DisplayModule
{
public:
	AndroidDisplayModule(Engine* engine);
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