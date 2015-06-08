#include <assert.h>

#include "AndroidDisplay.h"
#include "Engine.h"

AndroidDisplay::AndroidDisplay(Engine* engine)
	:engine_(engine)
{
	assert(engine != NULL);
}

void AndroidDisplay::create()
{
	engine_->create();
}

void AndroidDisplay::change(int width, int height)
{
	engine_->change(width, height);
}

void AndroidDisplay::draw()
{
	engine_->draw();
}

void AndroidDisplay::pause()
{
	engine_->pause();
}

void AndroidDisplay::resume()
{
	engine_->resume();
}

void AndroidDisplay::destroy()
{
	engine_->destroy();
}