#pragma once

#include <stdlib.h>

#include "xvec_status.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Execute queries
 *
 * @details You can call this multiple times with different target vectors.
 *          For KnnQueries, The top-k is selected as a continuation of previous results.
 *
 * @param [in] queries queries
 * @param [in] count  target vectors
 *
 * @return xvecStatus
 */
xvecStatus xvecExecuteQueries(void* queries, size_t count);

#ifdef __cplusplus
}
#endif
