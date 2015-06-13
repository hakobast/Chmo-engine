
#ifndef ANDROID_INPUT_H
#define ANDROID_INPUT_H

#include "NativeInput.h"

typedef struct _JNIEnv JNIEnv;
typedef class _jobject* jobject;

class AndroidInput : public NativeInput
{
public:
	void OnTouchEvent(JNIEnv* env, jobject motionClass);
};

#endif