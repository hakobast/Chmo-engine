
#include <GL\glut.h>
#include <iostream>
#include "Input.h"

using namespace std;

//static variable initialization
Input* Input::instance = NULL;
//end

//Friend functions
void OnKeyDown(unsigned char key, int x, int y)
{
	//std::cout << "InputSystem:: Keydown: " << (int)key << std::endl;
	//Input::instance->keypressed.insert(std::make_pair((int)key, true));
	Input::instance->keypressed[(int)key] = true;
}

void OnKeyUp(unsigned char key, int x, int y)
{
	Input::instance->keypressed[(int)key] = false;
}


void OnSpecialKeyDown(int key, int x, int y)
{
	//std::cout << "InputSystem:: Special Key down: " << key << std::endl;
	//Input::instance->keypressed.insert(std::make_pair((int)key, true));
	Input::instance->keypressed[(int)key] = true;
}

void OnSpecialKeyUp(int key, int x, int y)
{
	Input::instance->keypressed[(int)key] = false;
}

void MouseFunc(int button, int state, int x, int y)
{
	//std::cout << "btn: " << button << " state: " << state << " x: " << x << " y:" << y << std::endl;
	Input::instance->mouseButtons[button] = state;
}

void MouseMotionFunc(int x, int y)
{
	//std::cout << " x: " << x << " y:" << y << std::endl;
	Input::instance->mousePosition.set(x, y);
}

void MousePassiveMotionFunc(int x, int y)
{
	//std::cout << "Passive" << " x: " << x << " y:" << y << std::endl;
	Input::instance->mousePosition.set(x, y);
}

//friends

Input::Input()
{
	glutKeyboardFunc(OnKeyDown);
	glutKeyboardUpFunc(OnKeyUp);
	glutSpecialFunc(OnSpecialKeyDown);
	glutSpecialUpFunc(OnSpecialKeyUp);
	glutMouseFunc(MouseFunc);
	glutMotionFunc(MouseMotionFunc);
	glutPassiveMotionFunc(MousePassiveMotionFunc);

	for (int i = 0; i < 3; i++)
		mouseButtons[i] = 1;

	instance = this;
}

Input::~Input()
{
	std::cout << "InputSystem:: ~~~deleted~~~" << std::endl;
}

void Input::Init()
{
	std::cout << "InputSystem:: Init()" << std::endl;
}

void Input::Update()
{
	//std::cout << "InputSystem:: Update()" << std::endl;
	//keypressed.clear();
}