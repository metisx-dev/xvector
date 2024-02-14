#include "knn_query.hpp"

#include <cassert>
//#include <iostream>

//#include "half_float/half_float.hpp"
#include "index_array.hpp"
#include "vector_array.hpp"
#include "xvector/xvec_index_array.h"
#include "xvector/xvec_vector_array.h"

namespace xvec
{
namespace sim
{

KnnQuery::KnnQuery(Context* context,
                   xvecKnnType type,
                   const std::shared_ptr<uint8_t[]>& vector,
                   xvecFloatType floatType,
                   std::size_t dimension,
                   std::size_t k)
    : Managed<KnnQuery>(context),
      Query(Query::Knn),
      type_(type),
      floatType_(floatType),
      dimension_(dimension),
      k_(k),
      vector_(vector)
{
}

namespace
{

template <typename Float>
struct DotProduct
{
    Float operator()(const Float* a, const Float* b, std::size_t dimension) const
    {
        // std::cout << "a=" << *a << ", b=" << *b << ", dimension=" << dimension << std::endl;

        Float dotProduct = 0.0f;
        for (std::size_t i = 0; i < dimension; i++)
        {
            dotProduct += a[i] * b[i];
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
void createResult(KnnQuery* query)
{
    if (query->result() == nullptr)
    {
        const auto context = query->context();
        const auto k = query->k();

        // (k + 1) for simplicity of the insertion.
        auto scores = std::shared_ptr<uint8_t[]>(new uint8_t[sizeof(Float) * (k + 1)]);
        auto indices = std::shared_ptr<xvecIndex[]>(new xvecIndex[k + 1]);
        auto vectorArrays = std::shared_ptr<xvecVectorArray[]>(new xvecVectorArray[k + 1]);
        auto result = makeShared<KnnResult>(context, query->floatType(), scores, indices, vectorArrays);
        query->setResult(result);
    }
}

template <typename Float, typename Compare>
void insertResult(KnnQuery* query, Float score, std::size_t index, VectorArray* vectorArray)
{
    Compare compare;

    auto result = query->result();

    Float* scores = reinterpret_cast<Float*>(result->scores().get());
    xvecIndex* indices = reinterpret_cast<xvecIndex*>(result->indices().get());
    xvecVectorArray* vectorArrays = reinterpret_cast<xvecVectorArray*>(result->vectorArrays().get());

    if (result->k() == 0)
    {
        scores[0] = score;
        indices[0] = index;
        vectorArrays[0] = reinterpret_cast<xvecVectorArray>(vectorArray);
        result->setK(1);
        return;
    }
    else if (result->k() < query->k())
    {
        result->setK(result->k() + 1);
    }
    else if (!compare(score, scores[result->k() - 1]))
    {
        return;
    }

    std::size_t i;
    for (i = result->k() - 1; i >= 1; --i)
    {
        if (compare(scores[i - 1], score))
        {
            break;
        }
        else
        {
            scores[i] = scores[i - 1];
            indices[i] = indices[i - 1];
            vectorArrays[i] = vectorArrays[i - 1];
        }
    }

    scores[i] = score;
    indices[i] = index;
    vectorArrays[i] = reinterpret_cast<xvecVectorArray>(vectorArray);
}

template <typename Float, xvecKnnType KnnType>
void searchByIndexArray(KnnQuery* query)
{
    createResult<Float>(query);

    using Compare = std::conditional_t<KnnType == XVEC_KNN_L2_DISTANCE, std::less<Float>, std::greater<Float>>;
    using Distance = std::conditional_t<KnnType == XVEC_KNN_L2_DISTANCE, L2Distance<Float>, DotProduct<Float>>;
    Distance distance;

    const auto dim = query->dimension();
    const auto floatType = query->floatType();

    const Float* const queryVector = reinterpret_cast<const Float*>(query->vector().get());

    const xvecIndexArray* indexArrays = reinterpret_cast<const xvecIndexArray*>(query->targets().get());
    auto& filters = query->filters();

    for (std::size_t i = 0; i < query->targetCount(); i++)
    {
        const IndexArray* indexArray = reinterpret_cast<IndexArray*>(indexArrays[i]);
        auto vectorArray = indexArray->target();

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
            // if (filterData)
            //{
            //     const xvecIndex index = indexArrayData[j];
            //     std::cout << "[" << index << "] " << (uint32_t)(filterData[j / 8] & (1 << (j % 8))) << std::endl;
            // }

            if (!filterData || (filterData[j / 8] & (1 << (j % 8))))
            {
                const xvecIndex index = indexArrayData[j];
                const Float* const targetVector = &vectorArrayData[index * dim];
                Float score;

                score = distance(queryVector, targetVector, dim);
                insertResult<Float, Compare>(query, score, index, vectorArray.get());
            }
        }
    }
}

template <typename Float, xvecKnnType KnnType>
void searchByVectorArray(KnnQuery* query)
{
    createResult<Float>(query);

    using Compare = std::conditional_t<KnnType == XVEC_KNN_L2_DISTANCE, std::less<Float>, std::greater<Float>>;
    using Distance = std::conditional_t<KnnType == XVEC_KNN_L2_DISTANCE, L2Distance<Float>, DotProduct<Float>>;
    Distance distance;

    const auto dim = query->dimension();
    const auto floatType = query->floatType();

    const Float* const queryVector = reinterpret_cast<const Float*>(query->vector().get());
    xvecVectorArray* vectorArrays = reinterpret_cast<xvecVectorArray*>(query->targets().get());
    auto& filters = query->filters();

    for (std::size_t i = 0; i < query->targetCount(); i++)
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
                Float score = distance(queryVector, targetVector, dim);
                insertResult<Float, Compare>(query, score, index, vectorArray);
            }
        }
    }
}

template <typename Float, xvecKnnType KnnType>
void searchByTargetType(KnnQuery* query)
{
    if (query->targetType() == XVEC_KNN_TARGET_INDEX_ARRAY)
    {
        searchByIndexArray<Float, KnnType>(query);
    }
    else if (query->targetType() == XVEC_KNN_TARGET_VECTOR_ARRAY)
    {
        searchByVectorArray<Float, KnnType>(query);
    }
    else
    {
        assert(0);
    }
}

template <typename Float>
void searchByType(KnnQuery* query)
{
    if (query->type() == XVEC_KNN_L2_DISTANCE)
    {
        searchByTargetType<Float, XVEC_KNN_L2_DISTANCE>(query);
    }
    else if (query->type() == XVEC_KNN_DOT_PRODUCT)
    {
        searchByTargetType<Float, XVEC_KNN_DOT_PRODUCT>(query);
    }
    else if (query->type() == XVEC_KNN_COSINE_SIMILARITY)
    {
        searchByTargetType<Float, XVEC_KNN_COSINE_SIMILARITY>(query);
    }
    else
    {
        assert(0);
    }
}

}  // namespace

void searchKnn(KnnQuery* query)
{
    if (query->floatType() == XVEC_FLOAT32)
    {
        searchByType<float>(query);
    }
    else if (query->floatType() == XVEC_FLOAT16)
    {
        assert(0);
        // searchByType<half>(query);
    }
    else
    {
        assert(0);
    }
}

}  // namespace sim
}  // namespace xvec
