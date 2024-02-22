#include "com_metisx_xvector_KnnResult.h"

#include <xvector/xvector.h>

#include <iostream>

#include "throw_exception.hpp"

JNIEXPORT void JNICALL Java_com_metisx_xvector_KnnResult_nativeClose(JNIEnv *jniEnv, jobject jThis, jlong jNativeThis)
{
    (void)jThis;

    xvecKnnResult knnResult = reinterpret_cast<xvecKnnResult>(jNativeThis);

    xvecStatus status = xvecReleaseKnnResult(knnResult);

    if (status != XVEC_SUCCESS)
    {
        throwJavaException(jniEnv, "xvecReleaseKnnResult() failed");
        return;
    }
}

JNIEXPORT jint JNICALL Java_com_metisx_xvector_KnnResult_nativeGetK(JNIEnv *jniEnv, jobject jThis, jlong jNativeThis)
{
    (void)jThis;

    xvecKnnResult knnResult = reinterpret_cast<xvecKnnResult>(jNativeThis);

    size_t k;
    xvecStatus status = xvecGetKnnResultK(knnResult, &k);

    if (status != XVEC_SUCCESS)
    {
        throwJavaException(jniEnv, "xvecGetKnnResultK() failed");
        return 0;
    }

    return static_cast<jint>(k);
}

JNIEXPORT jfloatArray JNICALL Java_com_metisx_xvector_KnnResult_nativeGetScores(JNIEnv *jniEnv,
                                                                            jobject jThis,
                                                                            jlong jNativeThis)
{
    (void)jThis;

    xvecKnnResult knnResult = reinterpret_cast<xvecKnnResult>(jNativeThis);

    size_t k;
    xvecStatus status = xvecGetKnnResultK(knnResult, &k);

    if (status != XVEC_SUCCESS)
    {
        throwJavaException(jniEnv, "xvecGetKnnResultK() failed");
        return 0;
    }

    float *scores;
    status = xvecGetKnnResultScores(knnResult, &scores);

    if (status != XVEC_SUCCESS)
    {
        throwJavaException(jniEnv, "xvecGetKnnResultK() failed");
        return 0;
    }

    jfloatArray floatArray = jniEnv->NewFloatArray(k);

    if (floatArray == NULL)
    {
        return NULL;
    }

    float *elements = jniEnv->GetFloatArrayElements(floatArray, NULL);

    for (size_t i = 0; i < k; i++)
    {
        elements[i] = scores[i];
    }

    jniEnv->ReleaseFloatArrayElements(floatArray, elements, 0);

    return floatArray;

    //jobject byteBuffer = jniEnv->NewDirectByteBuffer(scores, k * sizeof(float));
    //return byteBuffer;
}

JNIEXPORT jintArray JNICALL Java_com_metisx_xvector_KnnResult_nativeGetIndices(JNIEnv *jniEnv,
                                                                             jobject jThis,
                                                                             jlong jNativeThis)
{
    (void)jThis;

    xvecKnnResult knnResult = reinterpret_cast<xvecKnnResult>(jNativeThis);

    size_t k;
    xvecStatus status = xvecGetKnnResultK(knnResult, &k);

    if (status != XVEC_SUCCESS)
    {
        throwJavaException(jniEnv, "xvecGetKnnResultK() failed");
        return 0;
    }

    xvecIndex *indices;
    status = xvecGetKnnResultIndices(knnResult, &indices);

    if (status != XVEC_SUCCESS)
    {
        throwJavaException(jniEnv, "xvecGetKnnResultIndices() failed");
        return 0;
    }

    //for (size_t i = 0; i < 10; i++)
    //{
    //    std::cout << i << " -> " << indices[i] << std::endl;
    //}
//
    //std::cout << "AAA " << k << std::endl;


    jintArray intArray = jniEnv->NewIntArray(k);

    if (intArray == NULL)
    {
        return NULL;
    }

    int *elements = jniEnv->GetIntArrayElements(intArray, NULL);

    for (size_t i = 0; i < k; i++)
    {
        elements[i] = indices[i];
    }

    jniEnv->ReleaseIntArrayElements(intArray, elements, 0);

    //jobject byteBuffer = jniEnv->NewDirectByteBuffer(indices, k * sizeof(int));
    //jniEnv->NewGlobalRef(byteBuffer);
    //jniEnv->DeleteLocalRef(byteBuffer);

    //std::cout << "BBB" << std::endl;

    return intArray;

    //return byteBuffer;
}

JNIEXPORT jobjectArray JNICALL Java_com_metisx_xvector_KnnResult_nativeVectorArrays(JNIEnv *jniEnv,
                                                                                    jobject jThis,
                                                                                    jlong jNativeThis)
{
    (void)jThis;

    xvecKnnResult knnResult = reinterpret_cast<xvecKnnResult>(jNativeThis);

    size_t k;
    xvecStatus status = xvecGetKnnResultK(knnResult, &k);

    if (status != XVEC_SUCCESS)
    {
        throwJavaException(jniEnv, "xvecGetKnnResultK() failed");
        return NULL;
    }

    xvecVectorArray *vectorArrays;
    status = xvecGetKnnResultVectorArrays(knnResult, &vectorArrays);

    if (status != XVEC_SUCCESS)
    {
        throwJavaException(jniEnv, "xvecGetKnnResultVectorArrays() failed");
        return NULL;
    }

    jclass vectorArrayClass = jniEnv->FindClass("com/metisx/xvector/VectorArray");
    if (vectorArrayClass == NULL)
    {
        // 클래스를 찾지 못한 경우 처리
        return NULL;
    }

    // 객체 배열 생성
    jobjectArray objArray = jniEnv->NewObjectArray(k, vectorArrayClass, NULL);
    if (objArray == NULL)
    {
        jniEnv->DeleteLocalRef(vectorArrayClass);
        throwJavaException(jniEnv, "jniEnv->NewObjectArray() failed");
        return NULL;
    }

    for (size_t i = 0; i < k; i++)
    {
        void *data;
        status = xvecGetVectorArrayCustomData(vectorArrays[i], &data);
        if (status != XVEC_SUCCESS)
        {
            jniEnv->DeleteLocalRef(vectorArrayClass);
            throwJavaException(jniEnv, "xvecGetVectorArrayCustomData() failed");
            return NULL;
        }

        jniEnv->SetObjectArrayElement(objArray, i, static_cast<jobject>(data));
    }

    jniEnv->DeleteLocalRef(vectorArrayClass);

    return objArray;

    // jobject byteBuffer = jniEnv->NewDirectByteBuffer(indices, k * sizeof(float));
    // return byteBuffer;
}
