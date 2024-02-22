#include "com_metisx_xvector_VectorArray.h"

#include <xvector/xvector.h>

#include "throw_exception.hpp"

JNIEXPORT jlong JNICALL Java_com_metisx_xvector_VectorArray_nativeInit(JNIEnv *jniEnv,
                                                                       jobject jThis,
                                                                       jlong jNativeContext,
                                                                       jint dimension)
{
    (void)jThis;
    xvecContext context = reinterpret_cast<xvecContext>(jNativeContext);

    xvecVectorArray vectorArray;
    xvecStatus status = xvecCreateVectorArray(&vectorArray, context, dimension);

    if (status != XVEC_SUCCESS)
    {
        throwJavaException(jniEnv, "xvecCreateVectorArray() failed");
        return 0;
    }

    status = xvecSetVectorArrayCustomData(vectorArray, static_cast<void *>(jThis));

    if (status != XVEC_SUCCESS)
    {
        throwJavaException(jniEnv, "xvecSetVectorArrayCustomData() failed");
        return 0;
    }

    return reinterpret_cast<jlong>(vectorArray);
}

JNIEXPORT void JNICALL Java_com_metisx_xvector_VectorArray_nativeClose(JNIEnv *jniEnv,
                                                                       jobject jThis,
                                                                       jlong jNativeThis)
{
    (void)jThis;
    (void)jniEnv;

    xvecVectorArray vectorArray = reinterpret_cast<xvecVectorArray>(jNativeThis);
    xvecStatus status = xvecReleaseVectorArray(vectorArray);

    if (status != XVEC_SUCCESS)
    {
        throwJavaException(jniEnv, "xvecReleaseVectorArray() failed");
        return;
    }
}

JNIEXPORT jint JNICALL Java_com_metisx_xvector_VectorArray_nativeDimension(JNIEnv *,
                                                                           JNIEnv *jniEnv,
                                                                           jobject jThis,
                                                                           jlong jNativeThis)
{
    (void)jThis;

    size_t dimension;

    xvecVectorArray vectorArray = reinterpret_cast<xvecVectorArray>(jNativeThis);
    xvecStatus status = xvecGetVectorArrayDimension(vectorArray, &dimension);

    if (status != XVEC_SUCCESS)
    {
        throwJavaException(jniEnv, "xvecGetVectorArrayDimension() failed");
        return 0;
    }

    return static_cast<jint>(dimension);
}

JNIEXPORT void JNICALL Java_com_metisx_xvector_VectorArray_nativeSetBuffer(JNIEnv *jniEnv,
                                                                             jobject jThis,
                                                                             jlong jNativeThis,
                                                                             jlong jNativeBuffer,
                                                                             jint length)
{
    (void)jThis;

    xvecVectorArray vectorArray = reinterpret_cast<xvecVectorArray>(jNativeThis);
    xvecBuffer buffer = reinterpret_cast<xvecBuffer>(jNativeBuffer);
    // jbyte *array = jniEnv->GetByteArrayElements(jArray, NULL);

    xvecStatus status = xvecSetVectorArrayBuffer(vectorArray, buffer, length);

    if (status != XVEC_SUCCESS)
    {
        throwJavaException(jniEnv, "xvecSetVectorArrayBuffer() failed");
        return;
    }
}
