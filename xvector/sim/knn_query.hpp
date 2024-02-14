#pragma once

#include <cstddef>

#include "factory.hpp"
#include "filter.hpp"
#include "knn_result.hpp"
#include "managed.hpp"
#include "query.hpp"
#include "xvector/xvec_knn_query.h"

namespace xvec
{
namespace sim
{

class KnnQuery : public Factory<KnnQuery>, public Managed<KnnQuery>, public Query
{
    friend Factory<KnnQuery>;

public:
    xvecKnnType type() const noexcept
    {
        return type_;
    }

    xvecFloatType floatType() const noexcept
    {
        return floatType_;
    }

    const std::shared_ptr<uint8_t[]>& vector() const noexcept
    {
        return vector_;
    }

    std::size_t dimension() const noexcept
    {
        return dimension_;
    }

    std::size_t k() const noexcept
    {
        return k_;
    }

    void setTargets(xvecKnnTargetType type, const std::shared_ptr<uint8_t[]>& targets, std::size_t count) noexcept
    {
        targets_ = targets;
        targetType_ = type;
        targetCount_ = count;
    }

    std::shared_ptr<uint8_t[]> targets() const noexcept
    {
        return targets_;
    }

    void setFilters(Filter** filters, size_t count) noexcept
    {
        filters_.clear();

        for (size_t i = 0; i < count; i++)
        {
            filters_.push_back(filters[i]);
        }
    }

    const std::vector<SharedPtr<Filter>>& filters() const noexcept
    {
        return filters_;
    }

    xvecKnnTargetType targetType() const noexcept
    {
        return targetType_;
    }

    std::size_t targetCount() const noexcept
    {
        return targetCount_;
    }

    SharedPtr<KnnResult> result()
    {
        return result_;
    }

    void setResult(SharedPtr<KnnResult> result)
    {
        result_ = result;
    }

private:
    KnnQuery(Context* context,
             xvecKnnType type,
             const std::shared_ptr<uint8_t[]>& vector,
             xvecFloatType floatType,
             std::size_t dimension,
             std::size_t k);

    KnnQuery(const KnnQuery& src) = delete;
    KnnQuery& operator=(const KnnQuery& src) = delete;

    void createResult();

    void insertResult(float score, std::size_t index, std::size_t vectorArrayId);

    void searchIndexArray();

    void searchIndexArray32();

    void searchIndexArray16();

    void searchVectorArray();

    void searchVectorArray32();

    void searchVectorArray16();

    xvecKnnType type_;
    xvecFloatType floatType_;
    std::size_t dimension_;
    std::size_t k_;
    xvecKnnTargetType targetType_;
    std::size_t targetCount_ = 0;
    std::shared_ptr<uint8_t[]> vector_;
    std::shared_ptr<uint8_t[]> targets_;
    std::vector<SharedPtr<Filter>> filters_;
    SharedPtr<KnnResult> result_;
};

void searchKnn(KnnQuery* query);

}  // namespace sim
}  // namespace xvec
