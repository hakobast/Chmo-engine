
#ifndef ANDROID_INPUT_H
#define ANDROID_INPUT_H

#include "NativeInput.h"

enum MotionAction
{
	A_ACTION_DOWN = 0,
	A_ACTION_UP = 1,
	A_ACTION_MOVE = 2,
	A_ACTION_CANCEL = 3,
	A_ACTION_POINTER_DOWN = 5,
	A_ACTION_POINTER_UP = 6
};

typedef struct _JNIEnv JNIEnv;
typedef class _jobject* jobject;

class AndroidInput : public NativeInput
{
public:
	void OnTouchEvent(JNIEnv* env, jobject motionClass);
};

#endif