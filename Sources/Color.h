
#ifndef OpenGLTesting_Color_h
#define OpenGLTesting_Color_h

#include <iostream>

struct Color
{
private:
	float r,g,b,a;
public:
	static const Color BLACK;
	static const Color WHITE;
	static const Color RED;
	static const Color GREEN;
	static const Color BLUE;
	static const Color YELLOW;
	static const Color PURPLE;
	static const Color CYAN;


	Color() :r(1.0f), g(1.0f), b(1.0f), a(1.0f){};
	Color(float r, float g, float b, float a = 1) :r(r), g(g), b(b), a(a){};

	void set(float r, float g = 1.0f, float b = 1.0f, float a = 1.0f);
	void setR(float r);
	void setG(float g);
	void setB(float b);
	void setA(float a);
	float getR() const;
	float getG() const;
	float getB() const;
	float getA() const;
	const float*const operator [](int index) const;
	friend std::ostream& operator << (std::ostream& stream, const Color& color);
};

inline void Color::set(float r, float g, float b, float a)
{
	this->r = r > 1.0f ? 1.0f : r;this->g = g > 1.0f ? 1.0f : g;
	this->b = b > 1.0f ? 1.0f : b;this->a = a > 1.0f ? 1.0f : a;
}

inline void Color::setR(float r)
{
	this->r = r > 1.0f ? 1.0f : r;
}

inline void Color::setG(float g)
{
	this->g = g > 1.0f ? 1.0f : g;;
}

inline void Color::setB(float b)
{
	this->b = b > 1.0f ? 1.0f : b;
}

inline void Color::setA(float a)
{
	this->a = a > 1.0f ? 1.0f : a;
}

inline float Color::getR()const{ return r; }
inline float Color::getG()const{ return g; }
inline float Color::getB()const{ return b; }
inline float Color::getA()const{ return a; }

inline const float*const Color::operator [](int index) const
{
	return &(&r)[index];
}

inline std::ostream& operator << (std::ostream& stream, const Color& color)
{
	return stream << "Color(" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << ")";
}

#endif