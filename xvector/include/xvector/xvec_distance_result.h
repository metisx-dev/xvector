#pragma once

#include <stddef.h>

#include "xvec_internal.h"
#include "xvec_status.h"

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
 * @brief Get the values of the distance query
 *
 * @details The returned indices are only valid until the k-NN result is released.
 *
 * @param [in]  result result
 * @param [out] values the distance values
 *
 * @return xvecStatus
 */
xvecStatus xvecGetDistanceResultValues(xvecDistanceResult result, float** values);

/**
 * @brief Get the number of values of the distance result
 *
 * @param [in]  result the result
 * @param [out] length the number of values
 */
xvecStatus xvecGetDistanceResultLength(xvecDistanceResult result, size_t* length);

#ifdef __cplusplus
}
#endif
