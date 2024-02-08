#include "cpu_distance_query.hpp"

#include <cassert>
#include <iostream>

#include "xvector/detail/cpu/half_float/half_float.hpp"
#include "xvector/detail/index_array.hpp"
#include "xvector/detail/vector_array.hpp"
#include "xvector/xvec_distance_query.h"
#include "xvector/xvec_index.h"
#include "xvector/xvec_index_array.h"

namespace xvec
{
namespace detail
{

CpuDistanceQuery::CpuDistanceQuery(CpuContext* context,
                                   xvecDistanceType type,
                                   const std::shared_ptr<uint8_t[]>& vector,
                                   xvecFloatType floatType,
                                   std::size_t dimension)
    : Managed<CpuDistanceQuery>(context),
      CpuQuery(CpuQuery::Distance),
      type_(type),
      floatType_(floatType),
      dimension_(dimension),
      vector_(vector),
      result_()
{
}

namespace
{

template <typename Float>
struct DotProduct
{
    Float operator()(const Float* a, const Float* b, std::size_t dimension) const
    {
        Float dotProduct = 0.0f;
        for (std::size_t i = 0; i < dimension; i++)
        {
            dotProduct += a[i] * b[i];
            // std::cout << "a[" << i << "]=" << a[i] << ", b[" << i << "]=" << b[i] << ", dimension=" << dimension <<
            // ", dp=" << dotProduct << std::endl;
        }
        return dotProduct;
    }
};

template <typename Float>
struct L2Distance
{
    Float operator()(const Float* a, const Float* b, std::size_t dimension) const
    {
        Float distance = 0.0f;
        for (std::size_t i = 0; i < dimension; i++)
        {
            const Float diff = a[i] - b[i];
            distance += diff * diff;
        }
        return distance;
    }
};

template <typename Float>
void createIndexArrayResult(CpuDistanceQuery* query)
{
    const xvecIndexArray* indexArrays = reinterpret_cast<xvecIndexArray*>(query->targets().get());
    const auto context = query->context();
    auto& filters = query->filters();

    std::size_t resultCount = 0;

    for (std::size_t i = 0; i < query->targetCount(); i++)
    {
        const auto indexArray = reinterpret_cast<const IndexArray*>(indexArrays[i]);
        const auto indexArraySize = indexArray->size();

        if (filters.size() <= i || filters[i] == nullptr)
        {
            resultCount += indexArraySize;
        }
        else
        {
            resultCount += filters[i]->validCount();
        }
    }

    std::shared_ptr<uint8_t[]> values(new uint8_t[sizeof(Float) * resultCount]);
    const auto result = CpuDistanceResult::create(context, values, resultCount);
    query->setResult(result);
}

template <typename Float>
void createVectorArrayResult(CpuDistanceQuery* query)
{
    const xvecVectorArray* vectorArrays = reinterpret_cast<xvecVectorArray*>(query->targets().get());
    const auto context = query->context();
    auto& filters = query->filters();

    std::size_t resultCount = 0;

    for (std::size_t i = 0; i < query->targetCount(); i++)
    {
        const auto vectorArray = reinterpret_cast<const VectorArray*>(vectorArrays[i]);
        const auto vectorArraySize = vectorArray->size();

        if (filters.size() <= i || filters[i] == nullptr)
        {
            resultCount += vectorArraySize;
        }
        else
        {
            resultCount += filters[i]->validCount();
        }
    }

    std::shared_ptr<uint8_t[]> values(new uint8_t[sizeof(Float) * resultCount]);
    const auto result = CpuDistanceResult::create(context, values, resultCount);
    query->setResult(result);
}

template <typename Float, xvecDistanceType DistanceType>
void calculateByIndexArray(CpuDistanceQuery* query)
{
    createIndexArrayResult<Float>(query);

    using Distance =
        std::conditional_t<DistanceType == XVEC_DISTANCE_L2_DISTANCE, L2Distance<Float>, DotProduct<Float>>;
    Distance distance;

    const auto dim = query->dimension();
    const auto floatType = query->floatType();

    const Float* const queryVector = reinterpret_cast<const Float*>(query->vector().get());
    Float* result = reinterpret_cast<Float*>(query->result()->values().get());

    const xvecIndexArray* indexArrays = reinterpret_cast<const xvecIndexArray*>(query->targets().get());

    auto& filters = query->filters();

    for (std::size_t i = 0; i < query->targetCount(); ++i)
    {
        const IndexArray* indexArray = reinterpret_cast<IndexArray*>(indexArrays[i]);
        const auto vectorArray = indexArray->target();

        // TODO: yongil - Add error handling instead of assert.
        assert(vectorArray->dimension() == dim);
        assert(vectorArray->floatType() == floatType);

        const auto indexArraySize = indexArray->size();
        const xvecIndex* indexArrayData = reinterpret_cast<const xvecIndex*>(indexArray->indices()->data());
        const Float* vectorArrayData = reinterpret_cast<const Float*>(vectorArray->vectors()->data());

        const uint8_t* filterData = nullptr;
        if (filters.size() > i)
            filterData = filters[i]->bitmap()->data();

        for (auto j = 0u; j < indexArraySize; ++j)
        {
            if (!filterData || (filterData[j / 8] & (1 << (j % 8))))
            {
                const xvecIndex index = indexArrayData[j];
                const Float* const targetVector = &vectorArrayData[index * dim];
                *result++ = distance(queryVector, targetVector, dim);
            }
        }
    }
}

template <typename Float, xvecDistanceType DistanceType>
void calculateByVectorArray(CpuDistanceQuery* query)
{
    createVectorArrayResult<Float>(query);

    using Distance =
        std::conditional_t<DistanceType == XVEC_DISTANCE_L2_DISTANCE, L2Distance<Float>, DotProduct<Float>>;
    Distance distance;

    const auto dim = query->dimension();
    const auto floatType = query->floatType();

    const Float* const queryVector = reinterpret_cast<const Float*>(query->vector().get());
    Float* result = reinterpret_cast<Float*>(query->result()->values().get());
    xvecVectorArray* vectorArrays = reinterpret_cast<xvecVectorArray*>(query->targets().get());
    auto& filters = query->filters();

    for (std::size_t i = 0; i < query->targetCount(); ++i)
    {
        const auto vectorArray = reinterpret_cast<VectorArray*>(vectorArrays[i]);

        // TODO: yongil - Add error handling instead of assert.
        assert(vectorArray->dimension() == dim);
        assert(vectorArray->floatType() == floatType);

        const auto vectorArraySize = vectorArray->size();
        const auto vectorArrayData = reinterpret_cast<const Float*>(vectorArray->vectors()->data());

        const uint8_t* filterData = nullptr;
        if (filters.size() > i)
            filterData = filters[i]->bitmap()->data();

        for (xvecIndex index = 0u; index < vectorArraySize; ++index)
        {
            if (!filterData || (filterData[index / 8] & (1 << (index % 8))))
            {
                const Float* const targetVector = &vectorArrayData[index * dim];
                *result++ = distance(queryVector, targetVector, dim);
            }
        }
    }
}

template <typename Float, xvecDistanceType DistanceType>
void calculateByTargetType(CpuDistanceQuery* query)
{
    if (query->targetType() == XVEC_DISTANCE_TARGET_INDEX_ARRAY)
    {
        calculateByIndexArray<Float, DistanceType>(query);
    }
    else if (query->targetType() == XVEC_DISTANCE_TARGET_VECTOR_ARRAY)
    {
        calculateByVectorArray<Float, DistanceType>(query);
    }
    else
    {
        assert(0);
    }
}

template <typename Float>
void calculateByType(CpuDistanceQuery* query)
{
    if (query->type() == XVEC_DISTANCE_L2_DISTANCE)
    {
        calculateByTargetType<Float, XVEC_DISTANCE_L2_DISTANCE>(query);
    }
    else if (query->type() == XVEC_DISTANCE_DOT_PRODUCT)
    {
        calculateByTargetType<Float, XVEC_DISTANCE_DOT_PRODUCT>(query);
    }
    else if (query->type() == XVEC_DISTANCE_COSINE_SIMILARITY)
    {
        calculateByTargetType<Float, XVEC_DISTANCE_COSINE_SIMILARITY>(query);
    }
    else
    {
        assert(0);
    }
}

}  // namespace

void calculateDistance(xvec::detail::DistanceQuery* query)
{
    if (query->floatType() == XVEC_FLOAT32)
    {
        calculateByType<float>(query);
    }
    else if (query->floatType() == XVEC_FLOAT16)
    {
        assert(0);
        // calculateByType<half>(query);
    }
    else
    {
        assert(0);
    }
}

}  // namespace detail
}  // namespace xvec
