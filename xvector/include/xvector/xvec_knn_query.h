#pragma once

#include <stdlib.h>

#include "xvec_filter.h"
#include "xvec_knn_result.h"
#include "xvec_op_type.h"
#include "xvec_query.h"  // IWYU pragma: export
#include "xvec_target_type.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Knn query.
 */
typedef struct xvecKnnQueryTag_* xvecKnnQuery;

/**
 * @brief Create a k-NN query.
 *
 * @details The query vector is a vector to be compared with vectors in target.
 *          Either `xvecSetKnnQueryTargetVectors()` or `xvecSetKnnQueryTargetIndices()` must be called
 *          to set calculation target vectors directly or indirectly.
 *          If both are called, the later one is applied.
 *
 * @param [out] query     k-NN query
 * @param [in]  opType    operation type
 * @param [in]  vector    query vector
 * @param [in]  floatType float type
 * @param [in]  dimension dimension
 * @param [in]  k         k
 *
 * @return xvecStatus
 */
xvecStatus xvecCreateKnnQuery(xvecKnnQuery* query,
                              xvecContext context,
                              xvecOpType  opType,
                              const float* queryVector,
                              size_t dimension,
                              size_t k);

/**
 * @brief Release a k-NN query.
 *
 * @details This function decrements the reference count of the k-NN query.
 *
 * @param [in] query k-NN query
 *
 * @return xvecStatus
 */
xvecStatus xvecReleaseKnnQuery(xvecKnnQuery query);

/**
 * @brief Get the context of the query.
 *
 * @param [in]  query   query
 * @param [out] context context
 *
 * @return xvecStatus
 */
xvecStatus xvecGetKnnQueryContext(xvecKnnQuery query, xvecContext* context);

/**
 * @brief Get the query vector.
 *
 * @details The returned buffer must be released by `xvecReleaseBuffer()`, when it is no longer needed,
 *          otherwise it will cause a memory leak.
 *
 * @param [in]  query  k-NN query
 * @param [out] vector query vector
 *
 * @return xvecStatus
 */
xvecStatus xvecGetKnnQueryVector(xvecKnnQuery query, float* vector);

/**
 * @brief Set the targets
 *
 * @param [in] query   k-NN query
 * @param [in] type    target type
 * @param [in] targets the buffer containing targets.
 *                     The targets are one of the following: vector arrays, index arrays.
 * @param [in] count   number of targets in the buffer
 *
 * @return xvecStatus
 */
xvecStatus xvecSetKnnQueryTargets(xvecKnnQuery query, xvecTargetType type, const void* targets, size_t count);

/**
 * @brief Set the filters
 *
 * @param [in] query   k-NN query
 * @param [in] filters filters.
 * @param [in] count   number of filters
 *
 * @return xvecStatus
 */
xvecStatus xvecSetKnnQueryFilters(xvecKnnQuery query, xvecFilter* filters, size_t count);

/**
 * @brief Get the topK.
 *
 * @param [in] query k-NN query
 * @param [out] k    k
 *
 * @return xvecStatus
 *
 */
xvecStatus xvecGetKnnQueryK(xvecKnnQuery query, size_t* k);

/**
 * @brief Get the result of k-NN query.
 *
 * @details The returned result must be released by `xvecReleaseKnnResult()` when it is no longer needed,
 *          otherwise it will cause a memory leak.
 *
 * @param [in]  query       k-NN query
 * @param [out] result      k-NN result
 *
 * @return xvecStatus
 */
xvecStatus xvecGetKnnQueryResult(xvecKnnQuery query, xvecKnnResult* result);

#ifdef __cplusplus
}
#endif
