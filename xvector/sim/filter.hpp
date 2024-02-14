#pragma once

#pragma once

#include "device_buffer.hpp"
#include "managed.hpp"
#include "vector_array.hpp"

namespace xvec
{
namespace sim
{
class Filter : public Managed<Filter>
{
public:
    explicit Filter(Context* context);

    void setBitmap(SharedPtr<DeviceBuffer> bitmap, size_t validCount);

    SharedPtr<DeviceBuffer> bitmap() const noexcept
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
    Filter(const Filter& src) = delete;
    Filter& operator=(const Filter& src) = delete;

    SharedPtr<DeviceBuffer> bitmap_ = nullptr;
    std::size_t validCount_;
    std::uintptr_t customData_;
};

}  // namespace sim
}  // namespace xvec
