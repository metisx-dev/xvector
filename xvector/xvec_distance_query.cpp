#include "xvec_distance_query.h"

#include <cstring>

#include "xvector/detail/distance_query.hpp"
#include "xvector/xvec_index_array.h"
#include "xvector/xvec_vector_array.h"

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
                                       const void* targets_,
                                       size_t count)
{
    auto query = dynamic_cast<xvec::detail::DistanceQuery*>(reinterpret_cast<xvec::detail::CpuQuery*>(query_));

    if (targets_ == NULL || count == 0)
    {
        query->setTargets(type, nullptr, 0);
        return XVEC_SUCCESS;
    }

    if (type == XVEC_DISTANCE_TARGET_VECTOR_ARRAY)
    {
        std::shared_ptr<uint8_t[]> targets(new uint8_t[sizeof(xvecVectorArray) * count]);
        std::memcpy(targets.get(), targets_, sizeof(xvecVectorArray) * count);
        query->setTargets(type, targets, count);
    }
    else if (type == XVEC_DISTANCE_TARGET_INDEX_ARRAY)
    {
        std::shared_ptr<uint8_t[]> targets(new uint8_t[sizeof(xvecIndexArray) * count]);
        std::memcpy(targets.get(), targets_, sizeof(xvecIndexArray) * count);
        query->setTargets(type, targets, count);
    }

    return XVEC_SUCCESS;
}

xvecStatus xvecSetDistanceQueryFilters(xvecDistanceQuery query_, xvecBuffer* filters_, size_t count)
{
    auto query = dynamic_cast<xvec::detail::DistanceQuery*>(reinterpret_cast<xvec::detail::CpuQuery*>(query_));

    if (filters_ == NULL || count == 0)
    {
        query->setFilters(nullptr, 0);
        return XVEC_SUCCESS;
    }

    auto filters = reinterpret_cast<xvec::detail::HostBuffer**>(filters_);
    query->setFilters(filters, count);

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

xvecStatus xvecGetDistanceQueryResult(xvecDistanceQuery query_, xvecDistanceResult* result_)
{
    auto query = dynamic_cast<xvec::detail::DistanceQuery*>(reinterpret_cast<xvec::detail::CpuQuery*>(query_));
    auto result = query->result();
    result->retain();
    *result_ = reinterpret_cast<xvecDistanceResult>(result.get());
    return XVEC_SUCCESS;
}

}  // extern "C"
