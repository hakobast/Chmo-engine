#ifndef DISPLAY_MODULE_H
#define DISPLAY_MODULE_H

#include <vector>

class DisplayModuleObserver;

class DisplayModule
{
public:
	virtual ~DisplayModule(){}
	virtual void create();
	virtual void change(int width, int height);
	virtual void draw();
	void addObserver(DisplayModuleObserver* observer);
	void removeObserver(DisplayModuleObserver* observer);
private:
	std::vector<DisplayModuleObserver*> observers_;
};

#endif
