#include "xvector/xvec_filter.h"

#include "context.hpp"
#include "filter.hpp"

extern "C"
{
xvecStatus xvecCreateFilter(xvecFilter* filter_, xvecContext context_)
{
    try
    {
        auto context = reinterpret_cast<xvec::sim::Context*>(context_);
        auto filter = new xvec::sim::Filter(context);
        *filter_ = reinterpret_cast<xvecFilter>(filter);
    }
    catch (std::bad_alloc& e)
    {
        return XVEC_ERROR_OUT_OF_MEMORY;
    }
    catch (...)
    {
        return XVEC_ERROR_UNKNOWN;
    }

    return XVEC_SUCCESS;
}

xvecStatus xvecReleaseFilter(xvecFilter filter_)
{
    auto filter = reinterpret_cast<xvec::sim::Filter*>(filter_);
    filter->release();
    return XVEC_SUCCESS;
}

xvecStatus xvecSetFilterBitmap(xvecFilter filter_, xvecBuffer bitmap_, size_t validCount)
{
    auto filter = reinterpret_cast<xvec::sim::Filter*>(filter_);
    auto bitmap = reinterpret_cast<xvec::sim::DeviceBuffer*>(bitmap_);
    // auto validityBitmap = reinterpret_cast<xvec::sim::DeviceBuffer*>(validityBitmap_);
    filter->setBitmap(bitmap, validCount);
    return XVEC_SUCCESS;
}

xvecStatus xvecGetFilterBitmap(xvecFilter filter_, xvecBuffer* bitmap_)
{
    auto filter = reinterpret_cast<xvec::sim::Filter*>(filter_);

    auto bitmap = filter->bitmap();
    if (bitmap)
        bitmap->retain();
    *bitmap_ = reinterpret_cast<xvecBuffer>(bitmap.get());
    return XVEC_SUCCESS;
}

xvecStatus xvecGetFilterValidCount(xvecFilter filter_, size_t* validCount)
{
    auto filter = reinterpret_cast<xvec::sim::Filter*>(filter_);
    *validCount = filter->validCount();
    return XVEC_SUCCESS;
}

xvecStatus xvecSetFilterCustomData(xvecFilter filter_, uintptr_t customData)
{
    auto filter = reinterpret_cast<xvec::sim::Filter*>(filter_);
    filter->setCustomData(customData);
    return XVEC_SUCCESS;
}

xvecStatus xvecGetFilterCustomData(xvecFilter filter_, uintptr_t* customData)
{
    auto filter = reinterpret_cast<xvec::sim::Filter*>(filter_);
    *customData = filter->customData();
    return XVEC_SUCCESS;
}

}  // extern "C"
