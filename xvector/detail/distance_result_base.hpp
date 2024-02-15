#pragma once

#include <memory>

#include "object.hpp"

namespace xvec
{
namespace detail
{
class DistanceResultBase : public Object
{
public:
    DistanceResultBase(ContextBase* context, const std::shared_ptr<uint8_t[]>& values, std::size_t count) noexcept;

    DistanceResultBase(const DistanceResultBase& src) = delete;
    
    DistanceResultBase& operator=(const DistanceResultBase& src) = delete;

    const std::shared_ptr<uint8_t[]>& values() noexcept
    {
        return values_;
    }

    std::size_t count() const noexcept
    {
        return count_;
    }

private:
    std::shared_ptr<uint8_t[]> values_;
    std::size_t count_;
};

}  // namespace detail
}  // namespace xvec
