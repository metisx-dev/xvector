#pragma once

#include <cstddef>
#include <vector>

#include "distance_result.hpp"
#include "filter.hpp"
#include "managed.hpp"
#include "query.hpp"
#include "xvector/xvec_distance_query.h"

namespace xvec
{
namespace sim
{
class Context;

class DistanceQuery : public Managed<DistanceQuery>, public Query
{
public:
    DistanceQuery(Context* context,
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

    SharedPtr<DistanceResult> result()
    {
        return result_;
    }

    void setResult(SharedPtr<DistanceResult> result)
    {
        result_ = result;
    }

private:
    DistanceQuery(const DistanceQuery& src) = delete;
    DistanceQuery& operator=(const DistanceQuery& src) = delete;

    xvecDistanceType type_;
    xvecFloatType floatType_;
    std::size_t dimension_;
    xvecDistanceTargetType targetType_;
    std::size_t targetCount_ = 0;
    std::shared_ptr<uint8_t[]> vector_;
    std::shared_ptr<uint8_t[]> targets_;
    std::vector<SharedPtr<Filter>> filters_;
    SharedPtr<DistanceResult> result_;
};

void calculateDistance(DistanceQuery* query);

}  // namespace sim
}  // namespace xvec
