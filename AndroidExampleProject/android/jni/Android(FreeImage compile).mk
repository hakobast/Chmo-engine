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

include $(LOCAL_PATH)/Makefile.srcs
include $(CLEAR_VARS)
LOCAL_MODULE       := LibFreeImage
LOCAL_C_INCLUDES   := $(LOCAL_PATH)/Source \
                        $(LOCAL_PATH)/Source/Metadata \
                        $(LOCAL_PATH)/Source/FreeImageToolkit \
                        $(LOCAL_PATH)/Source/LibJPEG \
                        $(LOCAL_PATH)/Source/LibPNG \
                        $(LOCAL_PATH)/Source/LibTIFF4 \
                        $(LOCAL_PATH)/Source/ZLib \
                        $(LOCAL_PATH)/Source/LibOpenJPEG \
                        $(LOCAL_PATH)/Source/OpenEXR \
                        $(LOCAL_PATH)/Source/OpenEXR/Half \
                        $(LOCAL_PATH)/Source/OpenEXR/Iex \
                        $(LOCAL_PATH)/Source/OpenEXR/IlmImf \
                        $(LOCAL_PATH)/Source/OpenEXR/IlmThread \
                        $(LOCAL_PATH)/Source/OpenEXR/Imath \
                        $(LOCAL_PATH)/Source/LibRawLite \
                        $(LOCAL_PATH)/Source/LibRawLite/dcraw \
                        $(LOCAL_PATH)/Source/LibRawLite/internal \
                        $(LOCAL_PATH)/Source/LibRawLite/libraw \
                        $(LOCAL_PATH)/Source/LibRawLite/src \
                        $(LOCAL_PATH)/Source/missing
LOCAL_SRC_FILES    := $(SRCS)
LOCAL_CPP_FEATURES := rtti exceptions
LOCAL_CFLAGS       := -O3 -fPIC 
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE 	:= game
LOCAL_MODULE    := FreeImage
LOCAL_SRC_FILES := ../../common/JNIBridge.cpp jni.cpp FreeImage.cpp
LOCAL_STATIC_LIBRARIES := LibFreeImage
LOCAL_SRC_FILES += $(CORE_ENGINE_SRC_FILES)
LOCAL_SRC_FILES += $(SYSTEMS_SRC_FILES)
LOCAL_SRC_FILES += $(COMPONENTS_SRC_FILES)
LOCAL_SRC_FILES += $(EXTRAS_SRC_FILES)
LOCAL_LDLIBS    := -lGLESv2 -lm    # using OpenGL ES 2.0 
LOCAL_CPPFLAGS  += -std=c++11   # enable c++11 features (fore example` non static member initialization)
LOCAL_CPPFLAGS  += -frtti 		# for RTTI (RunTime Type Information)

include $(BUILD_SHARED_LIBRARY)