#ifdef __ANDROID__

#include <jni.h>
#include <math.h>
#include "../Debug/Logger.h"
#include "AndroidInput.h"

enum MotionAction
{
	A_ACTION_DOWN = 0,
	A_ACTION_UP = 1,
	A_ACTION_MOVE = 2,
	A_ACTION_CANCEL = 3,
	A_ACTION_POINTER_DOWN = 5,
	A_ACTION_POINTER_UP = 6
};

void AndroidInput::OnTouchEvent(JNIEnv* env, jobject motionClass)
{
	lock();
	jclass cls = env->GetObjectClass(motionClass);
	jmethodID method_getPointerCount = env->GetMethodID(cls, "getPointerCount", "()I");
	jmethodID method_getPointerId = env->GetMethodID(cls, "getPointerId", "(I)I");
	jmethodID method_getActionMasked = env->GetMethodID(cls, "getActionMasked", "()I");
	jmethodID method_getActionIndex = env->GetMethodID(cls, "getActionIndex", "()I");
	jmethodID method_getX = env->GetMethodID(cls, "getX", "(I)F");
	jmethodID method_getY = env->GetMethodID(cls, "getY", "(I)F");
	jmethodID method_getHistorySize = env->GetMethodID(cls, "getHistorySize", "()I");
	jmethodID method_getHistoricalX = env->GetMethodID(cls, "getHistoricalX", "(II)F");
	jmethodID method_getHistoricalY = env->GetMethodID(cls, "getHistoricalY", "(II)F");
	
	touchCount_ = env->CallIntMethod(motionClass, method_getPointerCount);
	int action = env->CallIntMethod(motionClass, method_getActionMasked);
	int actionIndex = env->CallIntMethod(motionClass, method_getActionIndex);

	if(touches_.size() < touchCount_)
		touches_.resize(touchCount_);

	for(int index = 0; index < touchCount_; index++)
	{
		float x = env->CallFloatMethod(motionClass, method_getX, index);
		float y = env->CallFloatMethod(motionClass, method_getY, index);
		int id = env->CallIntMethod(motionClass, method_getPointerId, index);

		touches_[index].position[0] = x;
		touches_[index].position[1] = y;
		touches_[index].touchId = id;

		int historySize = env->CallIntMethod(motionClass, method_getHistorySize);
		if(historySize > 0)
		{
			float prevX = env->CallFloatMethod(motionClass, method_getHistoricalX, index, historySize-1);
			float prevY = env->CallFloatMethod(motionClass, method_getHistoricalY, index, historySize-1);
			if(prevX == x && prevY == y)
				touches_[index].action = ACTION_STATIC;
			else
				touches_[index].action = ACTION_MOVE;
			touches_[index].deltaPosition[0] = x-prevX;
			touches_[index].deltaPosition[1] = y-prevY;
		}
	}

	switch (action)
	{
	case A_ACTION_DOWN:
		mouseStates_[MouseButton::Left] = frame_;
	case A_ACTION_POINTER_DOWN:
		touches_[actionIndex].action = ACTION_DOWN;
		break;
	case A_ACTION_UP:
		mouseStates_[MouseButton::Left] = 0;
	case A_ACTION_CANCEL:
	case A_ACTION_POINTER_UP:
		touches_[actionIndex].action = ACTION_UP;
		if(touchCount_ == 1)
			touchCount_ = 0;
		break;
	case A_ACTION_MOVE:
		//touches_[actionIndex].action = ACTION_MOVE;
		break;
	}

	/*switch (action)
	{
	case A_ACTION_DOWN:
		Logger::PrintError("OnMotionEvent: ACTION_DOWN");
		break;
	case A_ACTION_UP:
		Logger::PrintError("OnMotionEvent: ACTION_UP");
		break;
	case A_ACTION_MOVE:
		Logger::PrintError("OnMotionEvent: ACTION_MOVE");
		break;
	case A_ACTION_CANCEL:
		Logger::PrintError("OnMotionEvent: ACTION_CANCEL");
		break;
	case A_ACTION_POINTER_DOWN:
		Logger::PrintError("OnMotionEvent: ACTION_POINTER_DOWN");
		break;
	case A_ACTION_POINTER_UP:
		Logger::PrintError("OnMotionEvent: ACTION_POINTER_UP");
		break;
	default:
		Logger::PrintError("OnMotionEvent: ACTION_UNDEFINED");
		break;
	}*/

	unlock();
}

#endif