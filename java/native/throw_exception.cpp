#include "throw_exception.hpp"

#include <cstdlib>
#include <iostream>

void throwJavaException(JNIEnv *jniEnv, std::string_view what, std::string_view class_)
{
    jclass execeptionClass = jniEnv->FindClass(class_.data());

    if (execeptionClass == NULL)
    {
        std::cerr << "FindClass(" << class_ << ") failed." << std::endl;
        std::exit(1);
    }

    // 예외 던지기
    jniEnv->ThrowNew(execeptionClass, what.data());

    jniEnv->DeleteLocalRef(execeptionClass);
}
