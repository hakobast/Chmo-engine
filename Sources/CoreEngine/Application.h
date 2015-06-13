#ifndef APPLICATION_H
#define APPLICATION_H

#ifdef _WIN32
#define PLATFORM_WINDOWS

#elif __APPLE__
#define PLATFORM_MAC

#elif __ANDROID__ 
#define PLATFORM_ANDROID

#endif


#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_MAC)
#define GL_OPENGL
#else
#define GL_OPENGL_ES
#endif

enum Platform
{
	WINDOWS_PLATFORM,
	MAC_PLATFORM,
	ANDROID_PLATFORM
};

class Application
{
public:
	static Platform CurrentPlatform();
};

inline Platform Application::CurrentPlatform()
{
#if defined(PLATFORM_WINDOWS)
	return Platform::WINDOWS_PLATFORM;
#elif defined(PLATFORM_MAC)
	return Platform::MAC_PLATFORM;
#elif defined(PLATFORM_ANDROID)
	return Platform::ANDROID_PLATFORM;
#endif
}

#endif