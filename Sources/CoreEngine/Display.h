#ifndef DISPLAY_MODULE_H
#define DISPLAY_MODULE_H

#include <vector>

class Display
{
public:
	virtual ~Display(){}
	virtual void create() = 0;
	virtual void change(int width, int height) = 0;
	virtual void draw() = 0;
	virtual void pause() = 0;
	virtual void resume() = 0;
	virtual void destroy() = 0;
};

#endif
