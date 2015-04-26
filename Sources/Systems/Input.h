
#ifndef EngineTesting_Input_h
#define EngineTesting_Input_h

#include <map>

#include "../CoreEngine/System.h"
#include "GameTime.h"

#define KeyCodes_Count 256
#define Special_Keys_Count 28

enum KeyCode
{
	TAB = 9,
	MINUS = 45,
	EQUALS = 61,
	NUMB0 = 48,
	NUMB1 = 49,
	NUMB2 = 50,
	NUMB3 = 51,
	NUMB4 = 52,
	NUMB5 = 53,
	NUMB6 = 54,
	NUMB7 = 55,
	NUMB8 = 56,
	NUMB9 = 57,
	A = 65,
	B = 66,
	C = 67,
	D = 68,
	E = 69,
	F = 70,
	G = 71,
	H = 72,
	I = 73,
	J = 74,
	K = 75,
	L = 76,
	M = 77,
	N = 78,
	O = 79,
	P = 80,
	Q = 81,
	R = 82,
	S = 83,
	T = 84,
	U = 85,
	V = 86,
	W = 87,
	X = 88,
	Y = 89,
	Z = 90,
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
	z = 122,
	/*F1 =			GLUT_KEY_F1			+ Special_Keys_Count,
	F2 =			GLUT_KEY_F2			+ Special_Keys_Count,
	F3 =			GLUT_KEY_F3			+ Special_Keys_Count,
	F4 =			GLUT_KEY_F4			+ Special_Keys_Count,
	F5 =			GLUT_KEY_F5			+ Special_Keys_Count,
	F6 =			GLUT_KEY_F6			+ Special_Keys_Count,
	F7 =			GLUT_KEY_F7			+ Special_Keys_Count,
	F8 =			GLUT_KEY_F8			+ Special_Keys_Count,
	F9 =			GLUT_KEY_F9			+ Special_Keys_Count,
	F10 =			GLUT_KEY_F10		+ Special_Keys_Count,
	F11 =			GLUT_KEY_F11		+ Special_Keys_Count,
	F12 =			GLUT_KEY_F12		+ Special_Keys_Count,
	LEFT =			GLUT_KEY_LEFT		+ Special_Keys_Count,
	UP =			GLUT_KEY_UP			+ Special_Keys_Count,
	RIGHT =			GLUT_KEY_RIGHT		+ Special_Keys_Count,
	DOWN =			GLUT_KEY_DOWN		+ Special_Keys_Count,
	PAGE_UP =		GLUT_KEY_PAGE_UP	+ Special_Keys_Count,
	PAGE_DOWN =		GLUT_KEY_PAGE_DOWN	+ Special_Keys_Count,
	HOME =			GLUT_KEY_HOME		+ Special_Keys_Count,
	END =			GLUT_KEY_END		+ Special_Keys_Count,
	INSERT =		GLUT_KEY_INSERT		+ Special_Keys_Count,*/
	LEFT_SHIFT	=	112					+ Special_Keys_Count,
	RIGHT_SHIFT =	113					+ Special_Keys_Count,
	LEFT_CTRL =		114					+ Special_Keys_Count,
	RIGHT_CTRL =	115					+ Special_Keys_Count,
	LEFT_ALT =		116					+ Special_Keys_Count,
	RIGHT_ALT =		117					+ Special_Keys_Count,
};

class Input : public System
{
public:
	static bool IsKeyDown(int key);
	static bool IsKeyDownNow(int key);
	static bool IsMouseDown(int button);
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
	friend void OnKeyDown             (unsigned char, int, int);
	friend void OnKeyUp               (unsigned char, int, int);
	friend void OnSpecialKeyDown      (int, int, int);
	friend void OnSpecialKeyUp        (int, int, int);
	friend void MouseFunc             (int button, int state, int x, int y);
	friend void MouseMotionFunc       (int x, int y);
	friend void MousePassiveMotionFunc(int x, int y);

	static Input* instance;
	int _keypressed[KeyCodes_Count];
	int _mouseButtons[3];
	Vector2 _mousePosition;
};

//static functions
inline bool Input::IsKeyDown(int key)
{
	return instance->_keypressed[key] > 0;
}

inline bool Input::IsKeyDownNow(int key)
{
	return instance->_keypressed[key] == GameTime::GetFrame();
}

inline bool Input::IsMouseDown(int button)
{
	return instance->_mouseButtons[button] != 0;
}

inline Vector2 Input::GetMousePosition()
{
	return instance->_mousePosition;
}
//end
#endif