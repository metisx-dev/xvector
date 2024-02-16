#pragma once

#include <cstddef>

#include "filter_base.hpp"
#include "knn_result_base.hpp"
#include "object.hpp"
#include "xvector/xvec_knn_query.h"

namespace xvec
{
namespace core
{

class KnnQueryBase : public Object
{
public:
    KnnQueryBase(ContextBase* context,
                 xvecKnnType type,
                 const std::shared_ptr<uint8_t[]>& vector,
                 xvecFloatType floatType,
                 std::size_t dimension,
                 std::size_t k);

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

    void setFilters(FilterBase** filters, size_t count) noexcept
    {
        filters_.clear();

        for (size_t i = 0; i < count; i++)
        {
            filters_.push_back(filters[i]);
        }
    }

    const std::vector<SharedPtr<FilterBase>>& filters() const noexcept
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

    SharedPtr<KnnResultBase> result()
    {
        return result_;
    }

    void setResult(SharedPtr<KnnResultBase> result)
    {
        result_ = result;
    }

private:
    KnnQueryBase(const KnnQueryBase& src) = delete;
    KnnQueryBase& operator=(const KnnQueryBase& src) = delete;

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
    std::vector<SharedPtr<FilterBase>> filters_;
    SharedPtr<KnnResultBase> result_;
};

}  // namespace sim
}  // namespace xvec
