#pragma once

#include "xvec_buffer.h"
#include "xvec_internal.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Distance result.
 */
typedef struct xvecDistanceResultTag_* xvecDistanceResult;

/**
 * @brief Release a distance result.
 *
 * @details This function decrements the reference count of the distance result.
 *
 * @param [in] result distance result
 *
 * @return xvecStatus
 */
xvecStatus xvecReleaseDistanceResult(xvecDistanceResult result);

/**
 * @brief Get result buffer.
 *
 * @details The result buffer contains the distance values.
 *          The type of each entry is either float16 or float32.
 *
 *          The returned buffer must be released by `xvecReleaseBuffer()`, when it is no longer needed,
 *          otherwise it will cause a memory leak.
 *
 * @param [in]  result distance result
 * @param [out] values the distance values
 *
 * @return xvecStatus
 */
xvecStatus xvecGetDistanceResultValues(xvecDistanceResult result, xvecBuffer* values);

#ifdef __cplusplus
}
#endif
