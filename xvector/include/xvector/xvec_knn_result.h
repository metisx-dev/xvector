#pragma once

#include <stdlib.h>

#include "xvec_index.h"
#include "xvec_vector_array.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Knn result.
 */
typedef struct xvecKnnResultTag_* xvecKnnResult;

/**
 * @brief Release a k-NN result.
 *
 * @details This function decrements the reference count of the k-NN result.
 *
 * @param [in] result k-NN result
 *
 * @return xvecStatus
 */
xvecStatus xvecReleaseKnnResult(xvecKnnResult result);

/**
 * @brief Get k.
 *
 * @param [in]  result k-NN result
 * @param [out] k       K
 *
 * @return xvecStatus
 */
xvecStatus xvecGetKnnResultK(xvecKnnResult result, size_t* k);

/**
 * @brief Get scores in a k-NN result.
 *
 * @details The returned scores are only valid until the k-NN result is released.
 *
 * @param [in]  result k-NN result
 * @param [out] scores  the scores
 *
 * @return xvecStatus
 */
xvecStatus xvecGetKnnResultScores(xvecKnnResult result, float** scores);

/**
 * @brief Get the indices in a k-NN result.
 *
 * @details The returned indices are only valid until the k-NN result is released.
 *
 * @param [in]  result k-NN result
 * @param [out] indices the indices
 *
 * @return xvecStatus
 */
xvecStatus xvecGetKnnResultIndices(xvecKnnResult result, xvecIndex** indices);

/**
 * @brief Get the target vector array indices in a k-NN result.
 *
 * @details The returned vectorArrays are only valid until the k-NN result is released.
 *
 * @param [in]  result       k-NN result
 * @param [out] vectorArrays vector arrays
 *
 * @return xvecStatus
 */
xvecStatus xvecGetKnnResultVectorArrays(xvecKnnResult result, xvecVectorArray** vectorArrays);

/**
 * @brief Get the result vector's metadata in a k-NN result.
*/
xvecStatus xvecGetKnnResultMetadata(xvecKnnResult result, uintptr_t** metada);

#ifdef __cplusplus
}
#endif
