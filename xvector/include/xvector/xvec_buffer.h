#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "xvec_context.h"
#include "xvec_status.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Buffer represents a memory block on the device.
 */
typedef struct xvecBufferTag_* xvecBuffer;

typedef uint32_t xvecBufferId;

extern xvecBuffer XVEC_NULL_BUFFER;

/**
 * @brief Create a buffer.
 *
 * @param [out] buffer  buffer
 * @param [in]  context context
 * @param [in]  size    size in bytes
 *
 * @return xvecStatus
 */
xvecStatus xvecCreateBuffer(xvecBuffer* buffer, xvecContext context, size_t size);

/**
 * @brief Release a buffer.
 *
 * @details This function decrements the reference count of the buffer.
 *
 * @param [in] buffer buffer
 *
 * @return xvecStatus
 */
xvecStatus xvecReleaseBuffer(xvecBuffer buffer);

/**
 * @brief Get the context of the buffer.
 *
 * @param [in]  buffer  buffer
 * @param [out] context context
 *
 * @return xvecStatus
 */
xvecStatus xvecGetBufferContext(xvecBuffer buffer, xvecContext* context);

/**
 * @brief Get the address of the buffer.
 *
 * @param [in]  buffer  buffer
 * @param [out] address pointer to the address to be returned
 *
 * @return xvecStatus
 */
xvecStatus xvecGetBufferAddress(xvecBuffer buffer, void** address);

/**
 * @brief Copy data from host to the device.
 *
 * @param [in] dst       destination buffer
 * @param [in] src       source data
 * @param [in] dstOffset offset in bytes
 * @param [in] size      size in bytes
 */
xvecStatus xvecCopyHostToBuffer(xvecBuffer dst, const void* src, size_t dstOffset, size_t size);

/**
 * @brief Copy data from the buffer to host.
 *
 * @param [in]  dst       destination data
 * @param [in]  src       source buffer
 * @param [in]  srcOffset offset in bytes
 * @param [in]  size      size in bytes
 *
 * @return xvecStatus
 */
xvecStatus xvecCopyBufferToHost(void* dst, xvecBuffer src, size_t srcOffset, size_t size);

/**
 * @brief Copy data from the buffer to buffer.
 *
 * @param [in]  dst       destination data
 * @param [in]  dstOffset offset in bytes
 * @param [in]  src       source buffer
 * @param [in]  srcOffset offset in bytes
 * @param [in]  size      size in bytes
 *
 * @return xvecStatus
 */
xvecStatus xvecCopyBufferToBuffer(xvecBuffer dst,
                                  size_t dstOffset,
                                  xvecBuffer src,
                                  size_t srcOffset,
                                  size_t size);

/**
 * @brief Get the size of the buffer.
 *
 * @param [in]  buffer buffer
 * @param [out] size   size
 *
 * @return xvecStatus
 */
xvecStatus xvecGetBufferCapacity(xvecBuffer buffer, size_t* size);

#ifdef __cplusplus
}  // extern "C"
#endif
