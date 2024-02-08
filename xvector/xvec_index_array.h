#pragma once

#include <stdint.h>
#include <stdlib.h>

#include "xvec_buffer.h"
#include "xvec_status.h"
#include "xvec_vector_array.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Index array.
 */
typedef struct xvecIndexArrayTag_* xvecIndexArray;

/**
 * @brief Index Array Id type.
 */
typedef uint32_t xvecIndexArrayId;

/**
 * @brief Create an index array.
 *
 * @param [out] indexArray index array
 * @param [in]  target    target vector array
 * @param [in]  size       the number of target vector arrays
 *
 * @return xvecStatus
 */
xvecStatus xvecCreateIndexArray(xvecIndexArray* indexArray, xvecVectorArray target);

/**
 * @brief Release an index array.
 *
 * @details This function decrements the reference count of the index array.
 *
 * @param [in] indexArray index array
 *
 * @return xvecStatus
 */
xvecStatus xvecReleaseIndexArray(xvecIndexArray indexArray);

/**
 * @brief Get the target vector array of the index array.
 *
 * @details The returned target vector array must be released by `xvecReleaseVectorArray()`, when it is no longer
 *         needed, otherwise it will cause a memory leak.
 *
 * @param [in]  indexArray index array
 * @param [out] target     target vector array
 *
 * @return xvecStatus
 */
xvecStatus xvecGetIndexArrayTarget(xvecIndexArray indexArray, xvecVectorArray* target);

/**
 * @brief Set the indices of the index array.
 *
 * @details The index array buffer is an array of indices to be used for similarity search.
 *
 * @param [in] indexArray index array
 * @param [in] indices    a buffer of indices
 * @param [in] size       the number of indices
 *
 * @return xvecStatus
 */
xvecStatus xvecSetIndexArrayIndices(xvecIndexArray indexArray, xvecBuffer targetIndices, size_t size);

/**
 * @brief Get the indices of the index array.
 *
 * @details The returned buffer must be released by `xvecReleaseBuffer()`, when it is no longer needed,
 *          otherwise it will cause a memory leak.
 *
 * @param [in]  indexArray index array
 * @param [out] buffer     a buffer of indices
 *
 * @return xvecStatus
 */
xvecStatus xvecGetIndexArrayIndices(xvecIndexArray indexArray, xvecBuffer* targetIndices);

/**
 * @brief Get the number of indices of the index array.
 *
 * @param [in]  indexArray index array
 * @param [out] size       the number of indices
 *
 * @return xvecStatus
 */
xvecStatus xvecGetIndexArraySize(xvecIndexArray indexArray, size_t* size);

/**
 * @brief Set the custom data to a index array.
 *
 * @param [in] indexArray index array
 * @param [in] customData  custom data
 *
 * @return xvecStatus
 */
xvecStatus xvecSetIndexArrayCustomData(xvecIndexArray indexArray_, uintptr_t customData);

/**
 * @brief Get the custom data of a index array.
 *
 * @param [in]  indexArray   index array
 * @param [out] customData    custom data
 *
 * @return xvecStatus
 */
xvecStatus xvecGetIndexArrayCustomData(xvecIndexArray indexArray_, uintptr_t *customData);

#if 0
/**
 * @brief Get the validity bitmap of the index array.
 *
 * @details The returned buffer must be released by `xvecReleaseBuffer()`, when it is no longer needed,
 *         otherwise it will cause a memory leak.
 *
 * @param [in]  indexArray    index array
 * @param [out] validityBitmap a buffer of validity bitmap
 *
 * @return xvecStatus
 */
xvecStatus xvecGetIndexArrayValidityBitmap(xvecIndexArray indexArray, xvecBuffer* validityBitmap);
#endif

#ifdef __cplusplus
}
#endif
