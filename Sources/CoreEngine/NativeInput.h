#ifndef NATIVE_INPUT_H
#define NATIVE_INPUT_H

#include <vector>
#include "../Extras/Vectors.h"

//TODO add all key codes


enum Key
{
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
	z = 122
};

enum SpecialKey
{
	F1 = 0x0001,
	F2 = 0x0002,
	F3 = 0x0003,
	F4 = 0x0004,
	F5 = 0x0005,
	F6 = 0x0006,
	F7 = 0x0007,
	F8 = 0x0008,
	F9 = 0x0009,
	F10 = 0x000A,
	F11 = 0x000B,
	F12 = 0x000C,
	LEFT = 0x0064,
	UP = 0x0065,
	RIGHT = 0x0066,
	DOWN = 0x0067,
	PAGE_UP = 0x0068,
	PAGE_DOWN = 0x0069,
	HOME = 0x006A,
	END = 0x006B,
	INSERT = 0x006C
};

enum MouseButton
{
	Left,
	Middle,
	Right
};

enum TouchAction
{
	ACTION_DOWN,
	ACTION_STATIC,
	ACTION_MOVE,
	ACTION_UP
};


class Touch
{
	friend class AndroidInput;
	friend class NativeInput;
public:
	void getPosition(Vector2& value) const;
	void getDeltaPosition(Vector2& value) const;
	int	 getTouchId() const;
	TouchAction getAction() const;
private:
	int position[2];
	int deltaPosition[2];
	int touchId;
	TouchAction action;
};

class NativeInput
{
public:
	NativeInput();
	virtual void init(){};
	virtual void update();

	void lock();
	void unlock();
	int  getKey				(Key key)			 const;
	int  getKey				(SpecialKey key)	 const;
	int	 getMouse			(MouseButton button) const;
	void getMousePosition	(Vector2& value)	 const;
	int	 getTouchCount		()					 const;

	const Touch& getTouch(int index) const;

protected:
	int frame_ = 0;
	int touchCount_ = 0;
	int keyStates_			[256];
	int specialKeyStates_	[256];
	int mouseStates_		[3];
	int mousePosition_		[2];

	std::vector<Touch> touches_;
};

inline int NativeInput::getKey(Key key) const
{
	return keyStates_[key];
}

inline int NativeInput::getKey(SpecialKey key) const
{
	return specialKeyStates_[key];
}

inline int NativeInput::getMouse(MouseButton button) const
{
	return mouseStates_[button];
}

inline void NativeInput::getMousePosition(Vector2& value) const
{
	value.x = (float)mousePosition_[0];
	value.y = (float)mousePosition_[1];
}

inline int	NativeInput::getTouchCount() const
{ 
	return touchCount_;
}

// Touch class impl
inline void Touch::getPosition(Vector2& value) const
{
	value.x = (float)position[0];
	value.y = (float)position[1];
}

inline void Touch::getDeltaPosition(Vector2& value) const
{
	value.x = (float)deltaPosition[0];
	value.y = (float)deltaPosition[1];
}

inline int Touch::getTouchId() const
{
	return touchId;
}

inline TouchAction Touch::getAction() const
{
	return action;
}

// end;

#endif