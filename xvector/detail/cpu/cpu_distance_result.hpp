#pragma once

#include <memory>

#include "xvector/detail/factory.hpp"
#include "xvector/detail/managed.hpp"

namespace xvec
{
namespace detail
{
class CpuDistanceResult : public Factory<CpuDistanceResult>, public Managed<CpuDistanceResult>
{
    friend Factory<CpuDistanceResult>;

public:
    const std::shared_ptr<uint8_t[]>& values() noexcept
    {
        return values_;
    }

    std::size_t count() const noexcept
    {
        return count_;
    }

private:
    explicit CpuDistanceResult(Context* context, const std::shared_ptr<uint8_t[]>& values, std::size_t count) noexcept;

    CpuDistanceResult(const CpuDistanceResult& src) = delete;
    CpuDistanceResult& operator=(const CpuDistanceResult& src) = delete;

private:
    std::shared_ptr<uint8_t[]> values_;
    std::size_t count_;
};

#ifndef XVEC_MU_SUPPORT
using DistanceResult = CpuDistanceResult;
#endif

}  // namespace detail
}  // namespace xvec
