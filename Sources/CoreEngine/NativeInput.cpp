
#include <string.h>
#include <mutex>

#include "../Debug/Logger.h"
#include "../Extras/Vectors.h"
#include "NativeInput.h"

std::mutex mtx;

NativeInput::NativeInput()
{
	memset(keyStates_,			0, sizeof keyStates_);
	memset(specialKeyStates_,	0, sizeof specialKeyStates_);
	memset(mouseStates_,		0, sizeof mouseStates_);
	memset(mousePosition_,		0, sizeof mousePosition_);
}

void NativeInput::update()
{
	frame_++;
}

void NativeInput::lock()
{
	mtx.lock();
}

void NativeInput::unlock()
{
	mtx.unlock();
}

const Touch& NativeInput::getTouch(int index) const
{
	//Logger::PrintError("Index %d, Count %d", index, touchCount_);
	if (index >= 0 && index < touchCount_)
		return touches_[index];

	Logger::PrintError("Error in NativeInput::getTouch. Invalid Argument \n");
}