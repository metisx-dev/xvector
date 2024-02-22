#pragma once

#include <stdint.h>
#include <stdlib.h>

#include "xvec_buffer.h"
#include "xvec_status.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief filter.
 */
typedef struct xvecFilterTag_* xvecFilter;

/**
 * @brief Create an filter.
 *
 * @param [out] Filter filter
 * @param [in]  size       the number of target vector arrays
 *
 * @return xvecStatus
 */
xvecStatus xvecCreateFilter(xvecFilter* Filter, xvecContext context);

/**
 * @brief Release an filter.
 *
 * @details This function decrements the reference count of the filter.
 *
 * @param [in] Filter filter
 *
 * @return xvecStatus
 */
xvecStatus xvecReleaseFilter(xvecFilter Filter);

/**
 * @brief Set the bitmap of the filter.
 *
 * @param [in] Filter     filter
 * @param [in] bitmap     a buffer of bitmap
 * @param [in] validCount the number of valid(set) bits
 *
 * @return xvecStatus
 */
xvecStatus xvecSetFilterBuffer(xvecFilter Filter, xvecBuffer bitmap, size_t validCount);

/**
 * @brief Get the bitmap of the filter.
 *
 * @param [in]  Filter filter
 * @param [out] buffer a buffer of bitmap
 *
 * @return xvecStatus
 */
xvecStatus xvecGetFilterBuffer(xvecFilter Filter, xvecBuffer* bitmap);

/**
 * @brief Get the number of valid bits of the filter.
 *
 * @param [in]  Filter filter
 * @param [out] size   the number of valid bits
 *
 * @return xvecStatus
 */
xvecStatus xvecGetFilterValidCount(xvecFilter Filter, size_t* validCount);

/**
 * @brief Set the custom data to a filter.
 *
 * @param [in] Filter filter
 * @param [in] customData  custom data
 *
 * @return xvecStatus
 */
xvecStatus xvecSetFilterCustomData(xvecFilter Filter_, uintptr_t customData);

/**
 * @brief Get the custom data of a filter.
 *
 * @param [in]  Filter   filter
 * @param [out] customData    custom data
 *
 * @return xvecStatus
 */
xvecStatus xvecGetFilterCustomData(xvecFilter Filter_, uintptr_t* customData);

#ifdef __cplusplus
}
#endif
