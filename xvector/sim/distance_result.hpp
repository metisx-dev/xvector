#pragma once

#include <memory>

#include "factory.hpp"
#include "managed.hpp"

namespace xvec
{
namespace sim
{
class DistanceResult : public Factory<DistanceResult>, public Managed<DistanceResult>
{
    friend Factory<DistanceResult>;

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
    explicit DistanceResult(Context* context, const std::shared_ptr<uint8_t[]>& values, std::size_t count) noexcept;

    DistanceResult(const DistanceResult& src) = delete;
    DistanceResult& operator=(const DistanceResult& src) = delete;

private:
    std::shared_ptr<uint8_t[]> values_;
    std::size_t count_;
};

}  // namespace sim
}  // namespace xvec
