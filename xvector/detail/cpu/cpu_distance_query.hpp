#pragma once

#include <cstddef>
#include <vector>

#include "xvector/detail/buffer.hpp"
#include "xvector/detail/cpu/cpu_distance_result.hpp"
#include "xvector/detail/cpu/cpu_filter.hpp"
#include "xvector/detail/cpu/cpu_query.hpp"
#include "xvector/detail/factory.hpp"
#include "xvector/detail/managed.hpp"
#include "xvector/xvec_distance_query.h"

namespace xvec
{
namespace detail
{
class CpuContext;

class CpuDistanceQuery : public Factory<CpuDistanceQuery>, public Managed<CpuDistanceQuery>, public CpuQuery
{
    friend Factory<CpuDistanceQuery>;

public:
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

    void setFilters(CpuFilter** filters, size_t count) noexcept
    {
        filters_.clear();

        for (size_t i = 0; i < count; i++)
        {
            filters_.push_back(filters[i]);
        }
    }

    const std::vector<SharedPtr<CpuFilter>>& filters() const noexcept
    {
        return filters_;
    }

    SharedPtr<CpuDistanceResult> result()
    {
        return result_;
    }

    void setResult(SharedPtr<CpuDistanceResult> result)
    {
        result_ = result;
    }

private:
    CpuDistanceQuery(CpuContext* context,
                     xvecDistanceType type,
                     const std::shared_ptr<uint8_t[]>& vector,
                     xvecFloatType floatType,
                     std::size_t dimension);

    CpuDistanceQuery(const CpuDistanceQuery& src) = delete;
    CpuDistanceQuery& operator=(const CpuDistanceQuery& src) = delete;

    xvecDistanceType type_;
    xvecFloatType floatType_;
    std::size_t dimension_;
    xvecDistanceTargetType targetType_;
    std::size_t targetCount_ = 0;
    std::shared_ptr<uint8_t[]> vector_;
    std::shared_ptr<uint8_t[]> targets_;
    std::vector<SharedPtr<CpuFilter>> filters_;
    SharedPtr<CpuDistanceResult> result_;
};

#ifndef XVEC_MU_SUPPORT
using DistanceQuery = CpuDistanceQuery;
#endif

void calculateDistance(xvec::detail::DistanceQuery* query);

}  // namespace detail
}  // namespace xvec
