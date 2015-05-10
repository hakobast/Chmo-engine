LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

CORE_ENGINE_SRC_FILES  := $(wildcard $(LOCAL_PATH)/../../../Sources/CoreEngine/*.cpp)
CORE_ENGINE_SRC_FILES  := $(CORE_ENGINE_SRC_FILES:$(LOCAL_PATH)/%=%)

SYSTEMS_SRC_FILES  := $(wildcard $(LOCAL_PATH)/../../../Sources/Systems/*.cpp)
SYSTEMS_SRC_FILES  := $(SYSTEMS_SRC_FILES:$(LOCAL_PATH)/%=%)

COMPONENTS_SRC_FILES  := $(wildcard $(LOCAL_PATH)/../../../Sources/Components/*.cpp)
COMPONENTS_SRC_FILES  := $(COMPONENTS_SRC_FILES:$(LOCAL_PATH)/%=%)

EXTRAS_SRC_FILES  := $(wildcard $(LOCAL_PATH)/../../../Sources/Extras/*.cpp)
EXTRAS_SRC_FILES  := $(EXTRAS_SRC_FILES:$(LOCAL_PATH)/%=%)

DEBUG_SRC_FILES  := $(wildcard $(LOCAL_PATH)/../../../Sources/Debug/*.cpp)
DEBUG_SRC_FILES  := $(DEBUG_SRC_FILES:$(LOCAL_PATH)/%=%)

# prepare FreeImage
include $(CLEAR_VARS)
LOCAL_MODULE    := LibFreeImage
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libLibFreeImage.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE 	:= game
LOCAL_SRC_FILES := ../../common/JNIBridge.cpp jni.cpp
LOCAL_SRC_FILES += $(CORE_ENGINE_SRC_FILES)
LOCAL_SRC_FILES += $(SYSTEMS_SRC_FILES)
LOCAL_SRC_FILES += $(COMPONENTS_SRC_FILES)
LOCAL_SRC_FILES += $(EXTRAS_SRC_FILES)
LOCAL_SRC_FILES += $(DEBUG_SRC_FILES)
LOCAL_STATIC_LIBRARIES := LibFreeImage
LOCAL_LDLIBS    := -lGLESv2 -lm -llog   # using OpenGL ES 2.0 
LOCAL_CPPFLAGS  += -std=c++11   # enable c++11 features (fore example` non static member initialization)
LOCAL_CPPFLAGS  += -frtti 		# for RTTI (RunTime Type Information)

include $(BUILD_SHARED_LIBRARY)