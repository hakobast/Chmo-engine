#ifndef DISPLAY_MODULE_OBSERVER_H
#define DISPLAY_MODULE_OBSERVER_H

#include "DisplayModule.h"

class DisplayModuleObserver
{
friend DisplayModule;
protected:
	virtual void create(){};
	virtual void change(int width, int height){};
	virtual void draw(){};
	virtual void pause(){};
	virtual void resume(){};
	virtual void destroy(){};
};

#endif