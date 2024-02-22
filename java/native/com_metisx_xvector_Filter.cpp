#include "com_metisx_xvector_Filter.h"

#include <xvector/xvector.h>

#include "throw_exception.hpp"

JNIEXPORT jlong JNICALL Java_com_metisx_xvector_Filter_nativeInit(JNIEnv *jniEnv, jobject jThis, jlong jNativeContext)
{
    (void)jThis;
    xvecContext context = reinterpret_cast<xvecContext>(jNativeContext);

    xvecFilter filter;
    xvecStatus status = xvecCreateFilter(&filter, context);

    if (status != XVEC_SUCCESS)
    {
        throwJavaException(jniEnv, "xvecCreateFilter() failed");
        return 0;
    }

    return reinterpret_cast<jlong>(filter);
}

JNIEXPORT void JNICALL Java_com_metisx_xvector_Filter_nativeClose(JNIEnv *jniEnv, jobject jThis, jlong jNativeThis)
{
    (void)jThis;
    (void)jniEnv;

    xvecFilter filter = reinterpret_cast<xvecFilter>(jNativeThis);
    xvecStatus status = xvecReleaseFilter(filter);

    if (status != XVEC_SUCCESS)
    {
        throwJavaException(jniEnv, "xvecReleaseFilter() failed");
        return;
    }
}

JNIEXPORT void JNICALL Java_com_metisx_xvector_Filter_nativeSetBuffer(JNIEnv *jniEnv,
                                                                      jobject jThis,
                                                                      jlong jNativeThis,
                                                                      jlong jNativeBuffer,
                                                                      jint validCount)
{
    (void)jThis;

    xvecFilter filter = reinterpret_cast<xvecFilter>(jNativeThis);
    xvecBuffer buffer = reinterpret_cast<xvecBuffer>(jNativeBuffer);
    // jbyte *array = jniEnv->GetByteArrayElements(jArray, NULL);

    xvecStatus status = xvecSetFilterBuffer(filter, buffer, validCount);

    if (status != XVEC_SUCCESS)
    {
        throwJavaException(jniEnv, "xvecSetFilterBuffer() failed");
        return;
    }
}
