#include <assert.h>

#include "AndroidDisplayModule.h"
#include "Engine.h"

AndroidDisplayModule::AndroidDisplayModule(Engine* engine)
	:engine_(engine)
{
	assert(engine != NULL);

	engine_->displayModule = this;
}

void AndroidDisplayModule::create()
{
	engine_->create();
}

void AndroidDisplayModule::change(int width, int height)
{
	engine_->change(width, height);
}

void AndroidDisplayModule::draw()
{
	engine_->draw();
}

void AndroidDisplayModule::pause()
{
	engine_->pause();
}

void AndroidDisplayModule::resume()
{
	engine_->resume();
}

void AndroidDisplayModule::destroy()
{
	engine_->destroy();
}