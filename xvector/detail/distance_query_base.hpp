#pragma once

#include <cstddef>
#include <vector>

#include "distance_result_base.hpp"
#include "filter_base.hpp"
#include "object.hpp"
#include "xvector/xvec_distance_query.h"
#include "xvector/xvec_float_type.h"

namespace xvec
{
namespace detail
{
class DistanceQueryBase : public Object
{
public:
    DistanceQueryBase(ContextBase* context,
                      xvecDistanceType type,
                      const std::shared_ptr<uint8_t[]>& vector,
                      xvecFloatType floatType,
                      std::size_t dimension);

    xvecDistanceType type() const noexcept
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

    void setTargets(xvecDistanceTargetType type, std::shared_ptr<uint8_t[]> targets, std::size_t count) noexcept
    {
        targets_ = targets;
        targetType_ = type;
        targetCount_ = count;
    }

    const std::shared_ptr<uint8_t[]>& targets() const noexcept
    {
        return targets_;
    }

    xvecDistanceTargetType targetType() const noexcept
    {
        return targetType_;
    }

    std::size_t targetCount() const noexcept
    {
        return targetCount_;
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

    SharedPtr<DistanceResultBase> result()
    {
        return result_;
    }

    void setResult(SharedPtr<DistanceResultBase> result)
    {
        result_ = result;
    }

private:
    DistanceQueryBase(const DistanceQueryBase& src) = delete;
    DistanceQueryBase& operator=(const DistanceQueryBase& src) = delete;

    xvecDistanceType type_;
    xvecFloatType floatType_;
    std::size_t dimension_;
    xvecDistanceTargetType targetType_;
    std::size_t targetCount_ = 0;
    std::shared_ptr<uint8_t[]> vector_;
    std::shared_ptr<uint8_t[]> targets_;
    std::vector<SharedPtr<FilterBase>> filters_;
    SharedPtr<DistanceResultBase> result_;
};

}  // namespace detail
}  // namespace xvec
