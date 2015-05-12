
#include "../Debug/Logger.h"
#include "Utils.h"

#include "DisplayModule.h"
#include "DisplayModuleObserver.h"

void DisplayModule::create()
{
	for (DisplayModuleObserver* obs : observers_)
		obs->create();
}

void DisplayModule::change(int width, int height)
{
	for (DisplayModuleObserver* obs : observers_)
		obs->change(width, height);
}

void DisplayModule::draw()
{
	for (DisplayModuleObserver* obs : observers_)
		obs->draw();
}

void DisplayModule::addObserver(DisplayModuleObserver* observer)
{
	observers_.push_back(observer);
}

void DisplayModule::removeObserver(DisplayModuleObserver* observer)
{
	vectorRemove<DisplayModuleObserver>(observers_, observer);
}