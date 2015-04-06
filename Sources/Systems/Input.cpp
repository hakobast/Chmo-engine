
#include "CoreEngine/LIBS.h"

#include <iostream>
#include "Input.h"

using namespace std;

//static variable initialization
Input* Input::instance = NULL;
//end

/////////////Friend functions
void OnKeyDown(unsigned char key, int x, int y)
{
	//std::cout << "InputSystem:: Keydown: " << (int)key << std::endl;
	
	if (Input::instance->_keypressed[(int)key] == 0)
		Input::instance->_keypressed[(int)key] = GameTime::GetFrame();
}

void OnKeyUp(unsigned char key, int x, int y)
{
	//std::cout << "InputSystem:: Keyup: " << (int)key << std::endl;
	Input::instance->_keypressed[(int)key] = 0;
}

void OnSpecialKeyDown(int key, int x, int y)
{
	//std::cout << "InputSystem:: Special Key down: " << key << std::endl;
	if (Input::instance->_keypressed[key + Special_Keys_Count] == 0)
		Input::instance->_keypressed[key + Special_Keys_Count] = GameTime::GetFrame();
}

void OnSpecialKeyUp(int key, int x, int y)
{
	//std::cout << "InputSystem:: Special Key up: " << key << std::endl;
	Input::instance->_keypressed[key + Special_Keys_Count] = 0;
}

void MouseFunc(int button, int state, int x, int y)
{
	//std::cout << "btn: " << button << " state: " << state << " x: " << x << " y:" << y << std::endl;
	Input::instance->_mouseButtons[button] = !state;
}

void MouseMotionFunc(int x, int y)
{
	//std::cout << " x: " << x << " y:" << y << std::endl;
	Input::instance->_mousePosition.set(x, y);
}

void MousePassiveMotionFunc(int x, int y)
{
	//std::cout << "Passive" << " x: " << x << " y:" << y << std::endl;
	Input::instance->_mousePosition.set(x, y);
}

////////////////////////friends

Input::Input()
{
	instance = this;

	glutKeyboardFunc(OnKeyDown);
	glutKeyboardUpFunc(OnKeyUp);
	glutSpecialFunc(OnSpecialKeyDown);
	glutSpecialUpFunc(OnSpecialKeyUp);
	glutMouseFunc(MouseFunc);
	glutMotionFunc(MouseMotionFunc);
	glutPassiveMotionFunc(MousePassiveMotionFunc);

	for (int i = 0; i < KeyCodes_Count; i++)
		_keypressed[i] = 0;

	for (int i = 0; i < 3; i++)
		_mouseButtons[i] = 0;
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

void Input::addComponent(Component &c){}
void Input::removeComponent(Component &c){}
bool Input::isSystemComponent(Component &c){ return false; }