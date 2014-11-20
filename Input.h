
#ifndef EngineTesting_Input_h
#define EngineTesting_Input_h

#include <map>
#include "System.h"
#include "Vectors.h"

enum KeyCode // implement All symbols
{
	A = 65,
	a = 97
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
	void addComponent(Component& comp);
private:
	static Input* instance;
	friend void OnKeyDown(unsigned char, int, int);
	friend void OnKeyUp(unsigned char, int, int);
	friend void OnSpecialKeyDown(int, int, int);
	friend void OnSpecialKeyUp(int, int, int);
	friend void MouseFunc(int button, int state, int x, int y);
	friend void MouseMotionFunc(int x, int y);
	friend void MousePassiveMotionFunc(int x, int y);
	std::map<int, bool> keypressed; //THINK maybe it can be int array
	int mouseButtons[3];
	Vector2 mousePosition;
};

//static functions
inline bool Input::GetKeyDown(int key)
{
	return instance->keypressed[key];
}

inline bool Input::GetMouseDown(int button)
{
	return instance->mouseButtons[button] != 1;
}

inline Vector2 Input::GetMousePosition()
{
	return instance->mousePosition;
}
//end
#endif