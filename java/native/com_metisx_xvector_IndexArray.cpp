#include "com_metisx_xvector_IndexArray.h"

#include <xvector/xvector.h>

#include "throw_exception.hpp"

JNIEXPORT jlong JNICALL Java_com_metisx_xvector_IndexArray_nativeInit(JNIEnv *jniEnv,
                                                                      jobject jThis,
                                                                      jlong jNativeVectorArray)
{
    (void)jThis;
    xvecVectorArray vectorArray = reinterpret_cast<xvecVectorArray>(jNativeVectorArray);

    xvecIndexArray indexArray;
    xvecStatus status = xvecCreateIndexArray(&indexArray, vectorArray);

    if (status != XVEC_SUCCESS)
    {
        throwJavaException(jniEnv, "xvecCreateIndexArray() failed");
        return 0;
    }

    status = xvecSetIndexArrayCustomData(indexArray, static_cast<void *>(jThis));

    if (status != XVEC_SUCCESS)
    {
        throwJavaException(jniEnv, "xvecSetIndexArrayCustomData() failed");
        return 0;
    }

    return reinterpret_cast<jlong>(indexArray);
}

JNIEXPORT void JNICALL Java_com_metisx_xvector_IndexArray_nativeClose(JNIEnv *jniEnv, jobject jThis, jlong jNativeThis)
{
    (void)jThis;
    (void)jniEnv;

    xvecIndexArray indexArray = reinterpret_cast<xvecIndexArray>(jNativeThis);
    xvecStatus status = xvecReleaseIndexArray(indexArray);

    if (status != XVEC_SUCCESS)
    {
        throwJavaException(jniEnv, "xvecReleaseIndexArray() failed");
        return;
    }
}

JNIEXPORT void JNICALL Java_com_metisx_xvector_IndexArray_nativeSetBuffer(JNIEnv *jniEnv,
                                                                            jobject jThis,
                                                                            jlong jNativeThis,
                                                                            jlong jNativeBuffer,
                                                                            jint length)
{
    (void)jThis;

    xvecIndexArray indexArray = reinterpret_cast<xvecIndexArray>(jNativeThis);
    xvecBuffer buffer = reinterpret_cast<xvecBuffer>(jNativeBuffer);
    // jbyte *array = jniEnv->GetByteArrayElements(jArray, NULL);

    xvecStatus status = xvecSetIndexArrayBuffer(indexArray, buffer, length);

    if (status != XVEC_SUCCESS)
    {
        throwJavaException(jniEnv, "xvecSetIndexArrayElements() failed");
        return;
    }
}
