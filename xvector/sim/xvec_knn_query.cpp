#include "xvector/xvec_knn_query.h"

#include <cstring>

#include "knn_query.hpp"
#include "xvector/xvec_index_array.h"
#include "xvector/xvec_vector_array.h"

extern "C"
{
xvecStatus xvecCreateKnnQuery(xvecKnnQuery* query_,
                              xvecContext context_,
                              xvecKnnType type,
                              const float* vector_,
                              size_t dimension,
                              size_t k)
{
    try
    {
        auto context = reinterpret_cast<xvec::sim::Context*>(context_);

        auto vector = std::shared_ptr<uint8_t[]>(new uint8_t[dimension * sizeof(float)]);
        std::memcpy(vector.get(), vector_, dimension * sizeof(float));

        auto query = new xvec::sim::KnnQuery(context, type, vector, XVEC_FLOAT32, dimension, k);
        *query_ = reinterpret_cast<xvecKnnQuery>(static_cast<xvec::sim::Query*>(query));
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

xvecStatus xvecReleaseKnnQuery(xvecKnnQuery query_)
{
    auto query = dynamic_cast<xvec::sim::KnnQuery*>(reinterpret_cast<xvec::sim::Query*>(query_));
    query->release();
    return XVEC_SUCCESS;
}

xvecStatus xvecGetKnnQueryContext(xvecKnnQuery query_, xvecContext* context_)
{
    auto query = dynamic_cast<xvec::sim::KnnQuery*>(reinterpret_cast<xvec::sim::Query*>(query_));
    auto context = query->context();
    *context_ = reinterpret_cast<xvecContext>(context);
    return XVEC_SUCCESS;
}

xvecStatus xvecGetKnnQueryVector(xvecKnnQuery query_, float* vector_)
{
    auto query = dynamic_cast<xvec::sim::KnnQuery*>(reinterpret_cast<xvec::sim::Query*>(query_));
    auto vector = query->vector();
    std::memcpy(vector_, vector.get(), query->dimension() * sizeof(float));
    return XVEC_SUCCESS;
}

xvecStatus xvecSetKnnQueryTargets(xvecKnnQuery query_, xvecKnnTargetType type, const void* targets_, size_t count)
{
    auto query = dynamic_cast<xvec::sim::KnnQuery*>(reinterpret_cast<xvec::sim::Query*>(query_));

    if (targets_ == NULL || count == 0)
    {
        query->setTargets(type, nullptr, 0);
        return XVEC_SUCCESS;
    }

    if (type == XVEC_KNN_TARGET_VECTOR_ARRAY)
    {
        std::shared_ptr<uint8_t[]> targets(new uint8_t[sizeof(xvecVectorArray) * count]);
        std::memcpy(targets.get(), targets_, sizeof(xvecVectorArray) * count);
        query->setTargets(type, targets, count);
    }
    else if (type == XVEC_KNN_TARGET_INDEX_ARRAY)
    {
        std::shared_ptr<uint8_t[]> targets(new uint8_t[sizeof(xvecIndexArray) * count]);
        std::memcpy(targets.get(), targets_, sizeof(xvecIndexArray) * count);
        query->setTargets(type, targets, count);
    }

    return XVEC_SUCCESS;
}

xvecStatus xvecSetKnnQueryFilters(xvecKnnQuery query_, xvecFilter* filters_, size_t count)
{
    auto query = dynamic_cast<xvec::sim::KnnQuery*>(reinterpret_cast<xvec::sim::Query*>(query_));

    if (filters_ == NULL || count == 0)
    {
        query->setFilters(nullptr, 0);
        return XVEC_SUCCESS;
    }

    auto filters = reinterpret_cast<xvec::sim::Filter**>(filters_);
    query->setFilters(filters, count);

    return XVEC_SUCCESS;
}

xvecStatus xvecGetKnnQueryResult(xvecKnnQuery query_, xvecKnnResult* result_)
{
    auto query = dynamic_cast<xvec::sim::KnnQuery*>(reinterpret_cast<xvec::sim::Query*>(query_));
    auto result = query->result();
    if (result)
        result->retain();
    *result_ = reinterpret_cast<xvecKnnResult>(result.get());
    return XVEC_SUCCESS;
}

}  // extern "C"
