#pragma once

#pragma once

#include "xvector/detail/cpu/cpu_vector_array.hpp"
#include "xvector/detail/device_buffer.hpp"
#include "xvector/detail/factory.hpp"
#include "xvector/detail/managed.hpp"

namespace xvec
{
namespace detail
{
class CpuFilter : public Factory<CpuFilter>, public Managed<CpuFilter>
{
    friend Factory<CpuFilter>;

public:
    void setBitmap(SharedPtr<CpuDeviceBuffer> bitmap, size_t validCount);

    SharedPtr<CpuDeviceBuffer> bitmap() const noexcept
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
    CpuFilter(CpuContext* context);

    CpuFilter(const CpuFilter& src) = delete;
    CpuFilter& operator=(const CpuFilter& src) = delete;

    SharedPtr<CpuDeviceBuffer> bitmap_ = nullptr;
    std::size_t validCount_;
    std::uintptr_t customData_;
};

#ifndef XVEC_MU_SUPPORT
using Filter = CpuFilter;
#endif

}  // namespace detail
}  // namespace xvec
