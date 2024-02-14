#pragma once

#include <stdlib.h>

#include "xvec_distance_result.h"
#include "xvec_filter.h"
#include "xvec_internal.h"
#include "xvec_query.h"  // IWYU pragma: export

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum xvecDistanceType
{
    XVEC_DISTANCE_L2_DISTANCE,
    XVEC_DISTANCE_DOT_PRODUCT,
    XVEC_DISTANCE_COSINE_SIMILARITY,
} xvecDistanceType;

typedef enum xvecDistanceTargetType
{
    XVEC_DISTANCE_TARGET_VECTOR_ARRAY,
    XVEC_DISTANCE_TARGET_INDEX_ARRAY,
    XVEC_DISTANCE_TARGET_VECTOR,  // TODO: Implement this
} xvecDistanceTargetType;

/**
 * @brief Distance query.
 */
typedef struct xvecDistanceQueryTag_* xvecDistanceQuery;

/**
 * @brief Create a distance query.
 *
 * @param [out] query     distance query
 * @param [in]  context   context
 * @param [in]  type      distance type
 * @param [in]  vector    query vector
 * @param [in]  dimension dimension of the query vector
 *
 * @return xvecStatus
 */
xvecStatus xvecCreateDistanceQuery(xvecDistanceQuery* query,
                                   xvecContext context,
                                   xvecDistanceType type,
                                   const float* vector,
                                   size_t dimension);

/**
 * @brief Release a distance query.
 *
 * @details This function decrements the reference count of the distance query.
 *
 * @param [in] query distance query
 *
 * @return xvecStatus
 */
xvecStatus xvecReleaseDistanceQuery(xvecDistanceQuery query);

/**
 * @brief Get the query vector.
 *
 * @param [in]  query  distance query
 * @param [out] vector query vector
 *
 * @return xvecStatus
 */
xvecStatus xvecGetDistanceQueryVector(xvecDistanceQuery query, float* vector);

/**
 * @brief Set the targets
 *
 * @param [in] query   distance query
 * @param [in] type    target type
 * @param [in] targets the buffer containing targets.
 *                     The targets are one of the following: vector array, index array.
 * @param [in] count   number of targets in the buffer
 *
 * @return xvecStatus
 */
xvecStatus xvecSetDistanceQueryTargets(xvecDistanceQuery query_,
                                       xvecDistanceTargetType type,
                                       const void* targets_,
                                       size_t count);

/**
 * @brief Set the filters
 *
 * @param [in] query   k-NN query
 * @param [in] filters the buffers containing filters.
 * @param [in] count   number of filters
 *
 * @return xvecStatus
 */
xvecStatus xvecSetDistanceQueryFilters(xvecDistanceQuery query, xvecFilter* filters, size_t count);

/**
 * @brief Get the result of distance query.
 *
 * @details The result contains the distance between the query and target vectors at the time of the latest
 *          `xvecCalculateDistance()` call.
 *
 *          The result is only valid until the next `xvecCalculateDistance()` call.
 *
 *          The returned result must be released by `xvecReleaseDistanceResult()` when it is no longer needed,
 *          otherwise it will cause a memory leak.
 *
 * @param [in]  query  distance query
 * @param [out] result distance result
 *
 * @return xvecStatus
 */
xvecStatus xvecGetDistanceQueryResult(xvecDistanceQuery query, xvecDistanceResult* result);

#ifdef __cplusplus
}
#endif
