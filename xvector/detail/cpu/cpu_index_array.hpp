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
class CpuIndexArray : public Factory<CpuIndexArray>, public Managed<CpuIndexArray>
{
    friend Factory<CpuIndexArray>;

public:
    SharedPtr<CpuVectorArray> target() const noexcept
    {
        return target_.get();
    }

    void setIndices(SharedPtr<CpuDeviceBuffer> indices, size_t size);

    SharedPtr<CpuDeviceBuffer> indices() const noexcept
    {
        return indices_;
    }

    std::size_t size() const noexcept
    {
        return size_;
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
    explicit CpuIndexArray(CpuVectorArray* target);

    CpuIndexArray(const CpuIndexArray& src) = delete;
    CpuIndexArray& operator=(const CpuIndexArray& src) = delete;

    SharedPtr<CpuVectorArray> target_;
    SharedPtr<CpuDeviceBuffer> indices_ = nullptr;
    std::size_t size_ = 0;
    std::uintptr_t customData_;
};

#ifndef XVEC_MU_SUPPORT
using IndexArray = CpuIndexArray;
#endif

}  // namespace detail
}  // namespace xvec
