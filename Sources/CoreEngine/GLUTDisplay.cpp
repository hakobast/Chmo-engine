
#include "../CoreEngine/Application.h"
#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_MAC)

#include <assert.h>

#include "LIBS.h"
#include "Engine.h"
#include "../Debug/Logger.h"
#include "GLUTDisplay.h"

void change_f(int width, int height)
{
	GLUTDisplay::instance_->change(width, height);
}

void draw_f()
{
	GLUTDisplay::instance_->draw();
}

void timer_f(int value)
{
	GLUTDisplay::instance_->timer_tick(value);
}

GLUTDisplay::GLUTDisplay(Engine* engine, int *argcp, char **argv, unsigned int displayMode, int width, int height, const char* windowName)
:engine_(engine), windowName_(windowName)
{
	assert(engine != NULL);

	glutInit(argcp, argv);
	glutInitDisplayMode(displayMode);
	glutInitWindowSize(width, height);
}

void GLUTDisplay::create()
{
	glutCreateWindow(windowName_);

	glutReshapeFunc(change_f);
	glutDisplayFunc(draw_f);
	glutTimerFunc(1000 / targetFPS, timer_f, 0);

	engine_->create();
}

void GLUTDisplay::change(int width, int height)
{
	engine_->change(width, height);
}

void GLUTDisplay::draw()
{
	engine_->draw();

	glutSwapBuffers();
}

void GLUTDisplay::pause()
{
	engine_->pause();
}

void GLUTDisplay::resume()
{
	engine_->resume();
}

void GLUTDisplay::destroy()
{
	engine_->destroy();
}

void GLUTDisplay::timer_tick(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / targetFPS, timer_f, 0);
}

#endif