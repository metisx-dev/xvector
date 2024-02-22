#include "com_metisx_xvector_KnnQuery.h"

#include <xvector/xvector.h>

#include "com_metisx_xvector_Buffer.h"
#include "throw_exception.hpp"

JNIEXPORT jlong JNICALL Java_com_metisx_xvector_KnnQuery_nativeInit(JNIEnv *jniEnv,
                                                                    jobject jThis,
                                                                    jlong jNativeContext,
                                                                    jint opType,
                                                                    jfloatArray jQueryVector,
                                                                    jint dimension,
                                                                    jint k)
{
    (void)jThis;
    xvecContext context = reinterpret_cast<xvecContext>(jNativeContext);
    jfloat *queryVector = jniEnv->GetFloatArrayElements(jQueryVector, NULL);

    xvecKnnQuery knnQuery;
    xvecStatus status =
        xvecCreateKnnQuery(&knnQuery, context, static_cast<xvecOpType>(opType), queryVector, dimension, k);

    if (status != XVEC_SUCCESS)
    {
        throwJavaException(jniEnv, "xvecCreateKnnQuery() failed");
        return 0;
    }

    return reinterpret_cast<jlong>(knnQuery);
}

JNIEXPORT void JNICALL Java_com_metisx_xvector_KnnQuery_nativeClose(JNIEnv *jniEnv, jobject jThis, jlong jNativeThis)
{
    (void)jThis;

    xvecKnnQuery knnQuery = reinterpret_cast<xvecKnnQuery>(jNativeThis);
    xvecStatus status = xvecReleaseKnnQuery(knnQuery);

    if (status != XVEC_SUCCESS)
    {
        throwJavaException(jniEnv, "xvecReleaseKnnQuery() failed");
        return;
    }
}

JNIEXPORT void JNICALL Java_com_metisx_xvector_KnnQuery_nativeSetTargets(JNIEnv *jniEnv,
                                                                         jobject jThis,
                                                                         jlong jNativeThis,
                                                                         jint targetType,
                                                                         jlongArray jTargets)
{
    (void)jThis;

    xvecKnnQuery knnQuery = reinterpret_cast<xvecKnnQuery>(jNativeThis);
    jlong *targets = jniEnv->GetLongArrayElements(jTargets, NULL);
    jsize targetCount = jniEnv->GetArrayLength(jTargets);

    xvecStatus status = xvecSetKnnQueryTargets(knnQuery, static_cast<xvecTargetType>(targetType), targets, targetCount);

    if (status != XVEC_SUCCESS)
    {
        throwJavaException(jniEnv, "xvecSetKnnQueryTargets() failed");
        return;
    }
}

JNIEXPORT void JNICALL Java_com_metisx_xvector_KnnQuery_nativeSetFilters(JNIEnv *jniEnv,
                                                                         jobject jThis,
                                                                         jlong jNativeThis,
                                                                         jlongArray jTargets)
{
    (void)jThis;

    xvecKnnQuery knnQuery = reinterpret_cast<xvecKnnQuery>(jNativeThis);
    jlong *filters = jniEnv->GetLongArrayElements(jTargets, NULL);
    jsize filterCount = jniEnv->GetArrayLength(jTargets);

    xvecStatus status = xvecSetKnnQueryFilters(knnQuery, reinterpret_cast<xvecFilter*>(filters), filterCount);

    if (status != XVEC_SUCCESS)
    {
        throwJavaException(jniEnv, "xvecSetKnnQueryFilters() failed");
        return;
    }
}

JNIEXPORT jlong JNICALL Java_com_metisx_xvector_KnnQuery_nativeGetResults(JNIEnv *jniEnv,
                                                                          jobject jThis,
                                                                          jlong jNativeThis)
{
    (void)jThis;

    xvecKnnResult result;

    xvecKnnQuery knnQuery = reinterpret_cast<xvecKnnQuery>(jNativeThis);
    xvecStatus status = xvecGetKnnQueryResult(knnQuery, &result);

    if (status != XVEC_SUCCESS)
    {
        throwJavaException(jniEnv, "xvecGetKnnQueryResult() failed");
        return 0;
    }

    return reinterpret_cast<jlong>(result);
}
