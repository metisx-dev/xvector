#pragma once

#include <memory>

#include "managed.hpp"

namespace xvec
{
namespace sim
{
class DistanceResult : public Managed<DistanceResult>
{
public:
    DistanceResult(Context* context, const std::shared_ptr<uint8_t[]>& values, std::size_t count) noexcept;

    const std::shared_ptr<uint8_t[]>& values() noexcept
    {
        return values_;
    }

    std::size_t count() const noexcept
    {
        return count_;
    }

private:
    DistanceResult(const DistanceResult& src) = delete;
    DistanceResult& operator=(const DistanceResult& src) = delete;

private:
    std::shared_ptr<uint8_t[]> values_;
    std::size_t count_;
};

}  // namespace sim
}  // namespace xvec
