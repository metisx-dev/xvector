#include "com_metisx_xvector_Context.h"
#include "throw_exception.hpp"

#include <xvector/xvector.h>

#include <string_view>

JNIEXPORT jlong JNICALL Java_com_metisx_xvector_Context_nativeInit(JNIEnv *jniEnv, jobject jThis)
{
    (void)jThis;

    xvecContext context;

    xvecStatus status = xvecCreateContext(&context, nullptr);
    if (status != XVEC_SUCCESS)
    {
        throwJavaException(jniEnv, "xvecCreateContext() failed");
        return 0;
    }

    return reinterpret_cast<jlong>(context);
}

JNIEXPORT void JNICALL Java_com_metisx_xvector_Context_nativeClose(JNIEnv *jniEnv, jobject jThis, jlong jNative)
{
    (void)jThis;

    xvecContext context = reinterpret_cast<xvecContext>(jNative);

    xvecStatus status = xvecDestroyContext(context);
    if (status != XVEC_SUCCESS)
    {
        throwJavaException(jniEnv, "xvecCreateContext() failed");
        return;
    }
}
