#if 0
#include "knn_search.hpp"

#include <new>

#include "knn_query.hpp"
#include "knn_result.hpp"
#include "xvector/xvec_float_type.h"

namespace xvec
{
namespace detail
{
KnnSearch::KnnSearch(KnnQuery* query) noexcept
    : query_(query)
{
}

void KnnSearch::init() noexcept
{
    auto result_ = new KnnResult(query_->k());
    result_->release();

    auto k = query_->k();

    xvecFloatType floatType;

    if (query_->targetVectorArrayCount() != 0)
    {
        floatType = query_->targetVectorArray(0)->type();

        for (std::size_t i = 0; i < query_->targetVectorArrayCount(); ++i)
        {
            auto targetVectorArray = query_->targetVectorArray(i);

            if (vectorArrayToIndex_.find(targetVectorArray) == vectorArrayToIndex_.end())
            {
                vectorArrayToIndex_[targetVectorArray] = result_->targetVectorArrayCount();
            }

            result_->addTargetVectorArray(targetVectorArray);
        }
    }
    else
    {
        floatType = query_->targetIndexArray(0)->target()->type();

        for (std::size_t i = 0; i < query_->targetIndexArrayCount(); ++i)
        {
            auto targetIndexArray = query_->targetIndexArray(i);
            auto targetVectorArray = targetIndexArray->target();

            if (vectorArrayToIndex_.find(targetVectorArray) == vectorArrayToIndex_.end())
            {
                vectorArrayToIndex_[targetVectorArray] = result_->targetVectorArrayCount();
            }

            result_->addTargetVectorArray(targetVectorArray);
        }
    }

    std::size_t floatSize = (floatType == XVEC_FLOAT32) ? 4 : 2;

    auto scores = Buffer::create(floatSize * k);
    result_->setScores(scores);
    scores->release();

    auto indices = Buffer::create(sizeof(xvecIndex) * k);
    result_->setIndices(indices);
    indices->release();

    auto arrayIndices = Buffer::create(sizeof(xvecIndex) * k);
    result_->setArrayIndices(arrayIndices);
    arrayIndices->release();
}

void KnnSearch::beginSearch() noexcept
{
    if (query_->targetVectorArrayCount() != 0)
    {
        for (std::size_t i = 0; i < query_->targetVectorArrayCount(); ++i)
        {
            auto targetVectorArray = query_->targetVectorArray(i);

            if (vectorArrayToIndex_.find(targetVectorArray) == vectorArrayToIndex_.end())
            {
                vectorArrayToIndex_[targetVectorArray] = result_->targetVectorArrayCount();
                result_->addTargetVectorArray(targetVectorArray);
            }
        }
    }
    else
    {
        for (std::size_t i = 0; i < query_->targetIndexArrayCount(); ++i)
        {
            auto targetIndexArray = query_->targetIndexArray(i);
            auto targetVectorArray = targetIndexArray->target();

            if (vectorArrayToIndex_.find(targetVectorArray) == vectorArrayToIndex_.end())
            {
                vectorArrayToIndex_[targetVectorArray] = result_->targetVectorArrayCount();
                result_->addTargetVectorArray(targetVectorArray);
            }
        }
    }
}

}  // namespace detail
}  // namespace xvec
#endif
