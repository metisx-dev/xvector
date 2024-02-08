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
 * @param [in]  result result
 * @param [out] size   number of values
 *
 * @return xvecStatus
 */
xvecStatus xvecGetDistanceResultSize(xvecDistanceResult result, size_t* size);

#ifdef __cplusplus
}
#endif
