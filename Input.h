
#ifndef EngineTesting_Input_h
#define EngineTesting_Input_h

#include <map>
#include "System.h"
#include "Vectors.h"

#define KeyCodes_Count 256 //Temp size

enum KeyCode // implement All symbols
{
	A = 65,
	a = 97,
	b = 98,
	g = 103,
	r = 114,
};

class Input : public System
{
public:
	static bool GetKeyDown(int key);
	static bool GetMouseDown(int button);
	static Vector2 GetMousePosition();
	Input(); //TEMP remove this when init function will called
protected:
	~Input();
	void Init();
	void Update();
	void addComponent(Component &c);
	void removeComponent(Component &c);

private:
	static Input* instance;
	friend void OnKeyDown(unsigned char, int, int);
	friend void OnKeyUp(unsigned char, int, int);
	friend void OnSpecialKeyDown(int, int, int);
	friend void OnSpecialKeyUp(int, int, int);
	friend void MouseFunc(int button, int state, int x, int y);
	friend void MouseMotionFunc(int x, int y);
	friend void MousePassiveMotionFunc(int x, int y);
	int _keypressed[KeyCodes_Count];
	int _mouseButtons[3];
	Vector2 _mousePosition;
};

//static functions
inline bool Input::GetKeyDown(int key)
{
	return instance->_keypressed[key];
}

inline bool Input::GetMouseDown(int button)
{
	return instance->_mouseButtons[button];
}

inline Vector2 Input::GetMousePosition()
{
	return instance->_mousePosition;
}
//end
#endif