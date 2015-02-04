
#ifndef EngineTesting_Input_h
#define EngineTesting_Input_h

#include <map>
#include "System.h"
#include "Vectors.h"

#define KeyCodes_Count 256 //Temp size

enum KeyCode // implement All symbols
{
	a = 97,
	b = 98,
	c = 99,
	d = 100,
	e = 101,
	f = 102,
	g = 103,
	h = 104,
	i = 105,
	j = 106,
	k = 107,
	l = 108,
	m = 109,
	n = 110,
	o = 111,
	p = 112,
	q = 113,
	r = 114,
	s = 115,
	t = 116,
	u = 117,
	v = 118,
	w = 119,
	x = 120,
	y = 121,
	z = 122
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
	bool isSystemComponent(Component &c);

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