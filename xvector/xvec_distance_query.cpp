#include "xvec_distance_query.h"

#include <cstring>
#include <vector>

#include "xvector/detail/cpu/cpu_query.hpp"
#include "xvector/detail/distance_query.hpp"

extern "C"
{
xvecStatus xvecCreateDistanceQuery(xvecDistanceQuery* query_,
                                   xvecContext context_,
                                   xvecDistanceType type,
                                   const float* vector_,
                                   size_t dimension)
{
    auto context = reinterpret_cast<xvec::detail::Context*>(context_);
    std::shared_ptr<uint8_t[]> vector(new uint8_t[dimension * sizeof(float)]);
    std::memcpy(vector.get(), vector_, dimension * sizeof(float));
    auto query = xvec::detail::DistanceQuery::create(context, type, vector, XVEC_FLOAT32, dimension);
    if (query == nullptr)
        return XVEC_ERROR_OUT_OF_MEMORY;
    query->retain();
    *query_ = reinterpret_cast<xvecDistanceQuery>(static_cast<xvec::detail::CpuQuery*>(query.get()));
    return XVEC_SUCCESS;
}

#if 0
xvecStatus xvecRetainDistanceQuery(xvecDistanceQuery query_)
{
    auto query = dynamic_cast<xvec::detail::DistanceQuery*>(reinterpret_cast<xvec::detail::CpuQuery>(query_));
    query->retain();
    return XVEC_SUCCESS;
}
#endif

xvecStatus xvecReleaseDistanceQuery(xvecDistanceQuery query_)
{
    auto query = dynamic_cast<xvec::detail::DistanceQuery*>(reinterpret_cast<xvec::detail::CpuQuery*>(query_));
    query->release();
    return XVEC_SUCCESS;
}

xvecStatus xvecGetDistanceQueryVector(xvecDistanceQuery query_, float* vector_)
{
    auto query = dynamic_cast<xvec::detail::DistanceQuery*>(reinterpret_cast<xvec::detail::CpuQuery*>(query_));
    auto vector = query->vector();
    std::memcpy(vector_, vector.get(), query->dimension() * sizeof(float));
    return XVEC_SUCCESS;
}

xvecStatus xvecSetDistanceQueryTargets(xvecDistanceQuery query_,
                                       xvecDistanceTargetType type,
                                       const float* targets_,
                                       size_t count)
{
    auto query = dynamic_cast<xvec::detail::DistanceQuery*>(reinterpret_cast<xvec::detail::CpuQuery*>(query_));
    std::shared_ptr<uint8_t[]> targets(new uint8_t[count * query->dimension() * sizeof(float)]);
    std::memcpy(targets.get(), targets_, count * query->dimension() * sizeof(float));
    query->setTargets(type, targets, count);

    return XVEC_SUCCESS;
}

#if 0
xvecStatus xvecGetDistanceQueryTargetBufferCount(xvecDistanceQuery query_, size_t* count)
{
    auto query = reinterpret_cast<xvec::detail::DistanceQuery*>(query_);
    *count = query->targetBuffers().size();
    return XVEC_SUCCESS;
}
#endif

xvecStatus xvecGetDistanceResult(xvecDistanceQuery query_, xvecDistanceResult* result_)
{
    auto query = dynamic_cast<xvec::detail::DistanceQuery*>(reinterpret_cast<xvec::detail::CpuQuery*>(query_));
    auto result = query->result();
    result->retain();
    *result_ = reinterpret_cast<xvecDistanceResult>(result.get());
    return XVEC_SUCCESS;
}

}  // extern "C"
