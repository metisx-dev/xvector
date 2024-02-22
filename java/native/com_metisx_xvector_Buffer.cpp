#include "com_metisx_xvector_Buffer.h"

#include <xvector/xvector.h>

#include "throw_exception.hpp"

JNIEXPORT jlong JNICALL Java_com_metisx_xvector_Buffer_nativeInit(JNIEnv *jniEnv,
                                                                  jobject jThis,
                                                                  jlong jNativeContext,
                                                                  jlong capacity)
{
    (void)jThis;
    xvecContext context = reinterpret_cast<xvecContext>(jNativeContext);

    xvecBuffer buffer;
    xvecStatus status = xvecCreateBuffer(&buffer, context, capacity);

    if (status != XVEC_SUCCESS)
    {
        throwJavaException(jniEnv, "xvecCreateBuffer() failed");
        return 0;
    }

    return reinterpret_cast<jlong>(buffer);
}

JNIEXPORT void JNICALL Java_com_metisx_xvector_Buffer_nativeClose(JNIEnv *jniEnv, jobject jThis, jlong jNativeThis)
{
    (void)jThis;
    (void)jniEnv;

    xvecBuffer buffer = reinterpret_cast<xvecBuffer>(jNativeThis);
    xvecStatus status = xvecReleaseBuffer(buffer);

    if (status != XVEC_SUCCESS)
    {
        throwJavaException(jniEnv, "xvecReleaseBuffer() failed");
        return;
    }
}

JNIEXPORT jlong JNICALL Java_com_metisx_xvector_Buffer_nativeCapacity(JNIEnv *jniEnv, jobject jThis, jlong jNativeThis)
{
    (void)jThis;

    size_t capacity;

    xvecBuffer buffer = reinterpret_cast<xvecBuffer>(jNativeThis);
    xvecStatus status = xvecGetBufferCapacity(buffer, &capacity);

    if (status != XVEC_SUCCESS)
    {
        throwJavaException(jniEnv, "xvecGetBufferCapacity() failed");
        return 0;
    }

    return static_cast<jlong>(capacity);
}

JNIEXPORT void JNICALL Java_com_metisx_xvector_Buffer_nativeCopyHostToBuffer__J_3BJJ(JNIEnv *jniEnv,
                                                                                     jobject jThis,
                                                                                     jlong jNativeThis,
                                                                                     jbyteArray jArray,
                                                                                     jlong offset,
                                                                                     jlong length)
{
    (void)jThis;

    xvecBuffer buffer = reinterpret_cast<xvecBuffer>(jNativeThis);
    jbyte *array = jniEnv->GetByteArrayElements(jArray, NULL);

    xvecStatus status = xvecCopyHostToBuffer(buffer, array, offset, length);

    if (status != XVEC_SUCCESS)
    {
        throwJavaException(jniEnv, "xvecCopyHostToBuffer() failed");
        return;
    }
}

JNIEXPORT void JNICALL Java_com_metisx_xvector_Buffer_nativeCopyHostToBuffer__J_3IJJ(JNIEnv *jniEnv,
                                                                                     jobject jThis,
                                                                                     jlong jNativeThis,
                                                                                     jintArray jArray,
                                                                                     jlong offset,
                                                                                     jlong length)
{
    (void)jThis;

    xvecBuffer buffer = reinterpret_cast<xvecBuffer>(jNativeThis);
    jint *array = jniEnv->GetIntArrayElements(jArray, NULL);

    xvecStatus status = xvecCopyHostToBuffer(buffer, array, offset, length * sizeof(jint));

    if (status != XVEC_SUCCESS)
    {
        throwJavaException(jniEnv, "xvecCopyHostToBuffer() failed");
        return;
    }
}

JNIEXPORT void JNICALL Java_com_metisx_xvector_Buffer_nativeCopyHostToBuffer__J_3FJJ(JNIEnv *jniEnv,
                                                                                     jobject jThis,
                                                                                     jlong jNativeThis,
                                                                                     jfloatArray jArray,
                                                                                     jlong offset,
                                                                                     jlong length)
{
    (void)jThis;

    xvecBuffer buffer = reinterpret_cast<xvecBuffer>(jNativeThis);
    jfloat *array = jniEnv->GetFloatArrayElements(jArray, NULL);

    xvecStatus status = xvecCopyHostToBuffer(buffer, array, offset, length * sizeof(jfloat));

    if (status != XVEC_SUCCESS)
    {
        throwJavaException(jniEnv, "xvecCopyHostToBuffer() failed");
        return;
    }
}

JNIEXPORT void JNICALL Java_com_metisx_xvector_Buffer_nativeCopyBufferToHost__J_3BJJ(JNIEnv *jniEnv,
                                                                                     jobject jThis,
                                                                                     jlong jNativeThis,
                                                                                     jbyteArray jArray,
                                                                                     jlong offset,
                                                                                     jlong length)
{
    (void)jThis;

    xvecBuffer buffer = reinterpret_cast<xvecBuffer>(jNativeThis);
    jbyte *array = jniEnv->GetByteArrayElements(jArray, NULL);

    xvecStatus status = xvecCopyBufferToHost(array, buffer, offset, length * sizeof(jbyte));

    if (status != XVEC_SUCCESS)
    {
        throwJavaException(jniEnv, "xvecCopyBufferToHost() failed");
        return;
    }
}

JNIEXPORT void JNICALL Java_com_metisx_xvector_Buffer_nativeCopyBufferToHost__J_3IJJ(JNIEnv *jniEnv,
                                                                                     jobject jThis,
                                                                                     jlong jNativeThis,
                                                                                     jintArray jArray,
                                                                                     jlong offset,
                                                                                     jlong length)
{
    (void)jThis;

    xvecBuffer buffer = reinterpret_cast<xvecBuffer>(jNativeThis);
    jint *array = jniEnv->GetIntArrayElements(jArray, NULL);

    xvecStatus status = xvecCopyBufferToHost(array, buffer, offset, length);

    if (status != XVEC_SUCCESS)
    {
        throwJavaException(jniEnv, "xvecCopyBufferToHost() failed");
        return;
    }
}

JNIEXPORT void JNICALL Java_com_metisx_xvector_Buffer_nativeCopyBufferToHost__J_3FJJ(JNIEnv *jniEnv,
                                                                                     jobject jThis,
                                                                                     jlong jNativeThis,
                                                                                     jfloatArray jArray,
                                                                                     jlong offset,
                                                                                     jlong length)
{
    (void)jThis;

    xvecBuffer buffer = reinterpret_cast<xvecBuffer>(jNativeThis);
    jfloat *array = jniEnv->GetFloatArrayElements(jArray, NULL);

    xvecStatus status = xvecCopyBufferToHost(array, buffer, offset, length * sizeof(jfloat));

    if (status != XVEC_SUCCESS)
    {
        throwJavaException(jniEnv, "xvecCopyBufferToHost() failed");
        return;
    }
}
