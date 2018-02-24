LOCAL_PATH := $(call my-dir)


include $(CLEAR_VARS)
LOCAL_MODULE := mpg123
LOCAL_SRC_FILES := ../sdl/$(TARGET_ARCH_ABI)/libmpg123.so
include $(PREBUILT_SHARED_LIBRARY)
include $(CLEAR_VARS)
LOCAL_MODULE := SDL2
LOCAL_SRC_FILES := ../sdl/$(TARGET_ARCH_ABI)/libSDL2.so
include $(PREBUILT_SHARED_LIBRARY)
include $(CLEAR_VARS)
LOCAL_MODULE := SDL2_image
LOCAL_SRC_FILES := ../sdl/$(TARGET_ARCH_ABI)/libSDL2_image.so
include $(PREBUILT_SHARED_LIBRARY)
include $(CLEAR_VARS)
LOCAL_MODULE := SDL2_mixer
LOCAL_SRC_FILES := ../sdl/$(TARGET_ARCH_ABI)/libSDL2_mixer.so
include $(PREBUILT_SHARED_LIBRARY)



#include $(CLEAR_VARS)
#LOCAL_MODULE := PisteEngine
#LOCAL_C_INCLUDES := #SDL include
#LOCAL_SRC_FILES := #PisteEngine files
#LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image SDL2_mixer
#LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog
#include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := PK2

LOCAL_C_INCLUDES := ../include

LOCAL_SRC_FILES := test.cpp

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image SDL2_mixer mpg123

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog
include $(BUILD_SHARED_LIBRARY)
