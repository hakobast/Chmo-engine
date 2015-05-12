#ifndef WIN_GLUT_DISPLAY_MODULE_H
#define WIN_GLUT_DISPLAY_MODULE_H

#include "DisplayModule.h"

class WinGLUTDisplayModule :public DisplayModule
{
public:
	WinGLUTDisplayModule::WinGLUTDisplayModule(
		int *argcp, 
		char **argv,
		unsigned int displayMode,
		int width,
		int height,
		const char* windowName);

	virtual void create();
	virtual void draw();
	void timer_tick(int value);
	int targetFPS = 60;
private:
	static WinGLUTDisplayModule* instance_;
	const char* windowName_;

	friend void change_f(int width, int height);
	friend void draw_f();
	friend void timer_f(int value);
};
#endif