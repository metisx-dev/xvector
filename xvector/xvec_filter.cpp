#include "xvec_filter.h"

#include "xvector/detail/context.hpp"
#include "xvector/detail/filter.hpp"

extern "C"
{
xvecStatus xvecCreateFilter(xvecFilter* filter_, xvecContext context_)
{
    auto context = reinterpret_cast<xvec::detail::Context*>(context_);
    auto Filter = xvec::detail::Filter::create(context);
    if (Filter == nullptr)
        return XVEC_ERROR_OUT_OF_MEMORY;

    Filter->retain();
    *filter_ = reinterpret_cast<xvecFilter>(Filter.get());
    return XVEC_SUCCESS;
}

xvecStatus xvecReleaseFilter(xvecFilter filter_)
{
    auto Filter = reinterpret_cast<xvec::detail::Filter*>(filter_);
    Filter->release();
    return XVEC_SUCCESS;
}

xvecStatus xvecSetFilterBitmap(xvecFilter filter_, xvecBuffer bitmap_, size_t validCount)
{
    auto Filter = reinterpret_cast<xvec::detail::Filter*>(filter_);
    auto bitmap = reinterpret_cast<xvec::detail::HostBuffer*>(bitmap_);
    // auto validityBitmap = reinterpret_cast<xvec::detail::HostBuffer*>(validityBitmap_);
    Filter->setBitmap(bitmap, validCount);
    return XVEC_SUCCESS;
}

xvecStatus xvecGetFilterBitmap(xvecFilter filter_, xvecBuffer* bitmap_)
{
    auto Filter = reinterpret_cast<xvec::detail::Filter*>(filter_);

    auto bitmap = Filter->bitmap();
    if (bitmap)
        bitmap->retain();
    *bitmap_ = reinterpret_cast<xvecBuffer>(bitmap.get());
    return XVEC_SUCCESS;
}

xvecStatus xvecGetFilterValidCount(xvecFilter filter_, size_t* validCount)
{
    auto filter = reinterpret_cast<xvec::detail::Filter*>(filter_);
    *validCount = filter->validCount();
    return XVEC_SUCCESS;
}

xvecStatus xvecSetFilterCustomData(xvecFilter filter_, uintptr_t customData)
{
    auto Filter = reinterpret_cast<xvec::detail::Filter*>(filter_);
    Filter->setCustomData(customData);
    return XVEC_SUCCESS;
}

xvecStatus xvecGetFilterCustomData(xvecFilter filter_, uintptr_t* customData)
{
    auto Filter = reinterpret_cast<xvec::detail::Filter*>(filter_);
    *customData = Filter->customData();
    return XVEC_SUCCESS;
}

}  // extern "C"
