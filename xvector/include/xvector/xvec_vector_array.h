#pragma once

#include <stddef.h>

#include "xvec_buffer.h"
#include "xvec_context.h"
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
xvecStatus xvecCreateVectorArray(xvecVectorArray *vectorArray, xvecContext context, size_t dimension);

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
 * @param [in] metadata    metadata
 * @param [in] length      the number of vectors
 *
 * @return xvecStatus
 */
xvecStatus xvecSetVectorArrayBuffer(xvecVectorArray vectorArray, xvecBuffer buffer, uintptr_t *metadata, size_t length);

/**
 * @brief Get the buffer containing vectors of a vector array.
 *
 * @details The returned buffer must be released by `xvecReleaseBuffer()` when it is no longer needed,
 *          otherwise it will cause a memory leak.
 *
 * @param [in]  vectorArray vector array
 * @param [out] buffer      buffer
 *
 * @return xvecStatus
 */
xvecStatus xvecGetVectorArrayBuffer(xvecVectorArray vectorArray, xvecBuffer *buffer);

/**
 * @brief Get the metadata to a vector array.
 *
 * @param [in] vectorArray vector array
 * @param [out] metadata    metadata
 *
 * @return xvecStatus
 */
xvecStatus xvecGetVectorArrayMetadata(xvecVectorArray vectorArray, uintptr_t **metadata);

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
xvecStatus xvecGetVectorArrayLength(xvecVectorArray vectorArray, size_t *size);

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

#ifdef __cplusplus
}
#endif
