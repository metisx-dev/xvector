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

xvecStatus xvecGetDistanceResultValues(xvecDistanceResult result_, float** scores_)
{
    auto result = reinterpret_cast<xvec::detail::DistanceResult*>(result_);
    *scores_ = reinterpret_cast<float*>(result->values().get());
    return XVEC_SUCCESS;
}

xvecStatus xvecGetDistanceResultSize(xvecDistanceResult result_, size_t* size)
{
    auto result = reinterpret_cast<xvec::detail::DistanceResult*>(result_);
    *size = result->count();
    return XVEC_SUCCESS;
}