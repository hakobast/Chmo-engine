#ifndef WIN_GLUT_DISPLAY_MODULE_H
#define WIN_GLUT_DISPLAY_MODULE_H

#include "../Extras/Singleton.h"
#include "Display.h"

class Engine;

class GLUTDisplay :public Display, private Singleton<GLUTDisplay>
{
public:
	GLUTDisplay::GLUTDisplay(
		Engine* engine,
		int *argcp, 
		char **argv,
		unsigned int displayMode,
		int width,
		int height,
		const char* windowName);

	virtual void create();
	virtual void change(int width, int height);
	virtual void draw();
	virtual void pause();
	virtual void resume();
	virtual void destroy();

	void timer_tick(int value);
	int targetFPS = 60;
private:
	const char* windowName_;
	Engine* engine_;

	friend void change_f(int width, int height);
	friend void draw_f();
	friend void timer_f(int value);
};
#endif