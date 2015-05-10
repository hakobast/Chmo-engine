
#ifndef TIME_UTILS_H
#define TIME_UTILS_H

class TimeUtils
{
public:
	static long Now_Ms();
private:
	static long Now_Ms_Android();
	static long Now_Ms_Win();
	static long Now_Ms_OSX();
};

#endif