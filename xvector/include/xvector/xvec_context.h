#pragma once

#include "xvec_internal.h"
#include "xvec_status.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct xvecContextTag_* xvecContext;

/**
 * @brief Create a context.
 *
 * @details The context must be released by `xvecDestroyContext()` when it is no longer needed,
 *          otherwise it causes a memory leak.
 *
 * @param [out] context context
 *
 * @return xvecStatus
 */
xvecStatus xvecCreateContext(xvecContext* context, void* device);

/**
 * @brief Release a context.
 *
 *
 * @param [in] context context
 *
 * @return xvecStatus
 */
xvecStatus xvecDestroyContext(xvecContext context);

#ifdef __cplusplus
}
#endif
