
#include <iostream>

#include "../CoreEngine/NativeInput.h"
#include "GameTime.h"
#include "Input.h"

Input::Input(NativeInput* input)
:nativeInput_(input)
{
	nativeInput_->init();
}

void Input::Update()
{
	nativeInput_->update();
}

void Input::OnStartFrame()
{
	nativeInput_->lock();
}

void Input::OnEndFrame()
{
	nativeInput_->unlock();
}

// Static functions
bool Input::IsKeyDown(Key key)
{
	return instance_->nativeInput_->getKey(key) > 0;
}

bool Input::IsKeyDownNow(Key key)
{
	return instance_->nativeInput_->getKey(key) == GameTime::GetFrame();
}

bool Input::IsKeyDown(SpecialKey key)
{
	return instance_->nativeInput_->getKey(key) > 0;
}

bool Input::IsKeyDownNow(SpecialKey key)
{
	return instance_->nativeInput_->getKey(key) == GameTime::GetFrame();
}

bool Input::IsMouseDown(MouseButton button)
{
	return instance_->nativeInput_->getMouse(button) > 0;
}

bool Input::IsMouseDownNow(MouseButton button)
{
	return instance_->nativeInput_->getMouse(button) == GameTime::GetFrame();
}

void Input::GetMousePosition(Vector2& value)
{
	instance_->nativeInput_->getMousePosition(value);
}

int	Input::GetTouchCount()
{
	return instance_->nativeInput_->getTouchCount();
}

const Touch& Input::GetTouch(int index)
{
	return instance_->nativeInput_->getTouch(index);
}

// end