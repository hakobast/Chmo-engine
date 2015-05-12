
#ifdef _WIN32

#include "../Debug/Logger.h"

#include <GL\glut.h>
#include "WinGLUTDisplayModule.h"

WinGLUTDisplayModule* WinGLUTDisplayModule::instance_ = NULL;

void change_f(int width, int height)
{
	WinGLUTDisplayModule::instance_->change(width, height);
}

void draw_f()
{
	WinGLUTDisplayModule::instance_->draw();
}

void timer_f(int value)
{
	WinGLUTDisplayModule::instance_->timer_tick(value);
}

WinGLUTDisplayModule::WinGLUTDisplayModule(int *argcp, char **argv, unsigned int displayMode, int width, int height, const char* windowName)
{
	glutInit(argcp, argv);
	glutInitDisplayMode(displayMode);
	glutInitWindowSize(width, height);

	this->windowName_ = windowName;
	WinGLUTDisplayModule::instance_ = this;
}

void WinGLUTDisplayModule::create()
{
	glutCreateWindow(windowName_);

 	glutReshapeFunc(change_f);
 	glutDisplayFunc(draw_f);
 	glutTimerFunc(1000 / targetFPS, timer_f, 0);

	DisplayModule::create();
}

void WinGLUTDisplayModule::draw()
{
	DisplayModule::draw();

	glutSwapBuffers();
}

void WinGLUTDisplayModule::timer_tick(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / targetFPS, timer_f, 0);
}

#endif