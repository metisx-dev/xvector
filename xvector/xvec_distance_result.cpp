#include "xvec_distance_result.h"

#include <cstring>

#include "xvector/detail/distance_result.hpp"

xvecStatus xvecRetainDistanceResult(xvecDistanceResult result_)
{
    auto result = reinterpret_cast<xvec::detail::DistanceResult*>(result_);
    result->retain();
    return XVEC_SUCCESS;
}

xvecStatus xvecReleaseDistanceResult(xvecDistanceResult result_)
{
    auto result = reinterpret_cast<xvec::detail::DistanceResult*>(result_);
    result->release();
    return XVEC_SUCCESS;
}

xvecStatus xvecGetDistanceResulValues(xvecDistanceResult result_, float* values_)
{
    auto result = reinterpret_cast<xvec::detail::DistanceResult*>(result_);
    auto values = result->values();
    std::memcpy(values_, values.get(), result->count() * sizeof(float));
    return XVEC_SUCCESS;
}
