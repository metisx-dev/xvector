#pragma once

#include <jni.h>
#include <string_view>

void throwJavaException(JNIEnv *jniEnv, std::string_view what, std::string_view class_ = "java/lang/RuntimeException");
