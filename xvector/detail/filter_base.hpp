#pragma once

#pragma once

#include "device_buffer_base.hpp"
#include "object.hpp"

namespace xvec
{
namespace detail
{
class FilterBase : public Object
{
public:
    explicit FilterBase(ContextBase* context);

    void setBitmap(SharedPtr<DeviceBufferBase> bitmap, size_t validCount);

    SharedPtr<DeviceBufferBase> bitmap() const noexcept
    {
        return bitmap_;
    }

    std::size_t validCount() const noexcept
    {
        return validCount_;
    }

    std::uintptr_t customData() const noexcept
    {
        return customData_;
    }

    void setCustomData(std::uintptr_t customData) noexcept
    {
        customData_ = customData;
    }

private:
    FilterBase(const FilterBase& src) = delete;
    FilterBase& operator=(const FilterBase& src) = delete;

    SharedPtr<DeviceBufferBase> bitmap_ = nullptr;
    std::size_t validCount_;
    std::uintptr_t customData_;
};

}  // namespace detail
}  // namespace xvec
