
#ifdef _WIN32

#include <assert.h>
#include "Engine.h"
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

WinGLUTDisplayModule::WinGLUTDisplayModule(Engine* engine, int *argcp, char **argv, unsigned int displayMode, int width, int height, const char* windowName)
:engine_(engine), windowName_(windowName)
{
	assert(engine != NULL);

	engine_->displayModule = this;

	glutInit(argcp, argv);
	glutInitDisplayMode(displayMode);
	glutInitWindowSize(width, height);

	WinGLUTDisplayModule::instance_ = this;
}

void WinGLUTDisplayModule::create()
{
	glutCreateWindow(windowName_);

	glutReshapeFunc(change_f);
	glutDisplayFunc(draw_f);
	glutTimerFunc(1000 / targetFPS, timer_f, 0);

	engine_->create();
}

void WinGLUTDisplayModule::change(int width, int height)
{
	engine_->change(width, height);
}

void WinGLUTDisplayModule::draw()
{
	engine_->draw();

	glutSwapBuffers();
}

void WinGLUTDisplayModule::pause()
{
	engine_->pause();
}

void WinGLUTDisplayModule::resume()
{
	engine_->resume();
}

void WinGLUTDisplayModule::destroy()
{
	engine_->destroy();
}

void WinGLUTDisplayModule::timer_tick(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / targetFPS, timer_f, 0);
}

#endif