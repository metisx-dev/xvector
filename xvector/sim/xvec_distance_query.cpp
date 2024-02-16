#include "xvector/xvec_distance_query.h"

#include <cstring>

#include "context.hpp"
#include "filter.hpp"
#include "distance_query.hpp"
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
    try
    {
        auto context = reinterpret_cast<xvec::sim::Context*>(context_);

        std::shared_ptr<uint8_t[]> vector(new uint8_t[dimension * sizeof(float)]);
        std::memcpy(vector.get(), vector_, dimension * sizeof(float));

        auto query = new xvec::sim::DistanceQuery(context, type, vector, XVEC_FLOAT32, dimension);
        *query_ = reinterpret_cast<xvecDistanceQuery>(static_cast<xvec::core::Object*>(query));
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

xvecStatus xvecReleaseDistanceQuery(xvecDistanceQuery query_)
{
    auto query = dynamic_cast<xvec::sim::DistanceQuery*>(reinterpret_cast<xvec::core::Object*>(query_));
    query->release();
    return XVEC_SUCCESS;
}

xvecStatus xvecGetDistanceQueryVector(xvecDistanceQuery query_, float* vector_)
{
    auto query = dynamic_cast<xvec::sim::DistanceQuery*>(reinterpret_cast<xvec::core::Object*>(query_));
    auto vector = query->vector();
    std::memcpy(vector_, vector.get(), query->dimension() * sizeof(float));
    return XVEC_SUCCESS;
}

xvecStatus xvecSetDistanceQueryTargets(xvecDistanceQuery query_,
                                       xvecDistanceTargetType type,
                                       const void* targets_,
                                       size_t count)
{
    auto query = dynamic_cast<xvec::sim::DistanceQuery*>(reinterpret_cast<xvec::core::Object*>(query_));

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

xvecStatus xvecSetDistanceQueryFilters(xvecDistanceQuery query_, xvecFilter* filters_, size_t count)
{
    auto query = dynamic_cast<xvec::sim::DistanceQuery*>(reinterpret_cast<xvec::core::Object*>(query_));

    if (filters_ == NULL || count == 0)
    {
        query->setFilters(nullptr, 0);
        return XVEC_SUCCESS;
    }

    auto filters = reinterpret_cast<xvec::sim::Filter**>(filters_);
    query->setFilters(filters, count);

    return XVEC_SUCCESS;
}

xvecStatus xvecGetDistanceQueryResult(xvecDistanceQuery query_, xvecDistanceResult* result_)
{
    auto query = dynamic_cast<xvec::sim::DistanceQuery*>(reinterpret_cast<xvec::core::Object*>(query_));
    auto result = query->result();
    result->retain();
    *result_ = reinterpret_cast<xvecDistanceResult>(result.get());
    return XVEC_SUCCESS;
}

}  // extern "C"
