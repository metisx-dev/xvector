#include "com_metisx_xvector_Query.h"

#include <xvector/xvector.h>

#include "com_metisx_xvector_Buffer.h"
#include "throw_exception.hpp"

#include <iostream>

JNIEXPORT void JNICALL Java_com_metisx_xvector_Query_nativeExecute(JNIEnv *jniEnv, jclass jClass, jlongArray jQueries)
{
    (void)jClass;

    jlong *queries = jniEnv->GetLongArrayElements(jQueries, NULL);

    jsize queryCount = jniEnv->GetArrayLength(jQueries);

    xvecStatus status = xvecExecuteQueries(queries, queryCount);
    if (status != XVEC_SUCCESS)
    {
        throwJavaException(jniEnv, "xvecExecuteQueries() failed");
    }
}
