#pragma once

#include <stddef.h>

#include "xvec_buffer.h"
#include "xvec_context.h"
#include "xvec_float_type.h"
#include "xvec_identifier.h"
#include "xvec_internal.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct xvecVectorArrayTag_ *xvecVectorArray;

// typedef uint32_t xvecVectorArrayId;

/**
 * @brief Create a vector array.
 *
 * @details The created vector array must be released by `xvecReleaseVectorArray()` when it is no longer needed,
 *          otherwise it will cause a memory leak.
 *
 * @param [out] vectorArray vector array
 * @param [in]  context     context
 * @param [in]  dim         dimension
 *
 * @return xvecStatus
 */
xvecStatus xvecCreateVectorArray(xvecVectorArray *vectorArray,
                                 xvecContext context,
                                 size_t dimension);

/**
 * @brief Release a vector array.
 *
 * @details This function decrements the reference count of the vector array,
 *          and releases the vector array if the reference count becomes zero.
 *
 * @param [in] vectorArray vector array
 *
 * @return xvecStatus
 */
xvecStatus xvecReleaseVectorArray(xvecVectorArray vectorArray);

/**
 * @brief Get the dimension of a vector array.
 *
 * @param [in]  vectorArray vector array
 * @param [out] dimension   dimension
 *
 * @return xvecStatus
 */
xvecStatus xvecGetVectorArrayDimension(xvecVectorArray vectorArray, size_t *dimension);

/**
 * @brief Set vectors to a vector array.
 *
 * @details The vector array will retain the buffer and it will be released when the vector array is released.
 *          So the caller can safely release the buffer after calling this function.
 *
 * @param [in] vectorArray vector array
 * @param [in] vectors     a buffer containing vectors
 * @param [in] size        the number of vectors
 *
 * @return xvecStatus
 */
xvecStatus xvecSetVectorArrayVectors(xvecVectorArray vectorArray, xvecBuffer vectors, size_t size);

/**
 * @brief Get the buffer containing vectors of a vector array.
 *
 * @details The returned buffer must be released by `xvecReleaseBuffer()` when it is no longer needed,
 *          otherwise it will cause a memory leak.
 *
 * @param [in]  vectorArray vector array
 * @param [out] vectors     a buffer containing vectors
 *
 * @return xvecStatus
 */
xvecStatus xvecGetVectorArrayVectors(xvecVectorArray vectorArray, xvecBuffer *vectors);

/**
 * @brief Get the number of vectors in a vector array.
 *
 * @details The size includes both valid and invalid vectors.
 *
 * @param [in] vectorArray vector array
 * @param [out] size       the number of vectors
 *
 * @return xvecStatus
 */
xvecStatus xvecGetVectorArraySize(xvecVectorArray vectorArray, size_t *size);

/**
 * @brief Set the custom data to a vector array.
 *
 * @param [in] vectorArray vector array
 * @param [in] customData  custom data
 *
 * @return xvecStatus
 */
xvecStatus xvecSetVectorArrayCustomData(xvecVectorArray vectorArray_, void *customData);

/**
 * @brief Get the custom data of a vector array.
 *
 * @param [in]  vectorArray   vector array
 * @param [out] customData    custom data
 *
 * @return xvecStatus
 */
xvecStatus xvecGetVectorArrayCustomData(xvecVectorArray vectorArray_, void **customData);

#if 0

/**
 * @brief Set the validity bitmap to a vector array.
 * 
 * @details The vector array will retain the buffer and it will be released when the vector array is released.
 *         So the caller can safely release the buffer after calling this function.
 * 
 * @param [in] vectorArray   vector array
 * @param [in] validityBitmap a buffer containing validity bitmap
 * @param [in] validCount     the number of valid vectors
 * 
 * @return xvecStatus
 */
xvecStatus xvecSetVectorArrayValidityBitmap(xvecVectorArray vectorArray, xvecBuffer validityBitmap, size_t validCount);

/**
 * @brief Get the buffer containing validity bitmap of a vector array.
 *
 * @details The returned buffer must be released by `xvecReleaseBuffer()` when it is no longer needed,
 *         otherwise it will cause a memory leak.
 *
 * @param [in]  vectorArray   vector array
 * @param [out] validityBitmap a buffer containing validity bitmap
 *
 * @return xvecStatus
 */
xvecStatus xvecGetVectorArrayValidityBitmap(xvecVectorArray vectorArray, xvecBuffer *validityBitmap);

/**
 * @brief Get the number of valid vectors in a vector array.
 *
 * @param [in] vectorArray vector array
 * @param [out] validCount the number of valid vectors
 *
 * @return xvecStatus
 */
xvecStatus xvecGetVectorArrayValidCount(xvecVectorArray vectorArray, size_t *validCount);

/**
 * @brief Set a vector to a vector array.
 *
 * @param [in] vectorArray vector array
 * @param [in] position    position
 * @param [out] vector     vector
 *
 * @return xvecStatus
 */
xvecStatus xvecGetVectorArrayVector(xvecVectorArray vectorArray, size_t position, xvecBuffer *vector);
#endif

#if 0
/**
 *
 */
xvecStatus xvecUpdateVectorArrayVectors(xvecVectorArray vectorArray,
                                        xvecBuffer positions,
                                        xvecBuffer vectors,
                                        size_t size);

/**
 */
xvecStatus xvecInsertVectorArrayVectors(xvecVectorArray vectorArray,
                                        xvecBuffer vectors,
                                        xvecBuffer *position,
                                        size_t size);

xvecStatus xvecDeleteVectorArrayVectors(xvecVectorArray vectorArray, xvecBuffer indices, size_t size);
#endif

#ifdef __cplusplus
}
#endif
