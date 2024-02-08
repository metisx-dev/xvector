#pragma once

#pragma once

#include "xvector/detail/cpu/cpu_vector_array.hpp"
#include "xvector/detail/factory.hpp"
#include "xvector/detail/host_buffer.hpp"
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

    void setTargetIndices(SharedPtr<CpuHostBuffer> targetIndices,
                          size_t size,
                          SharedPtr<CpuHostBuffer> validityBitmap,
                          size_t validCount);

    SharedPtr<CpuHostBuffer> targetIndices() const noexcept
    {
        return targetIndices_;
    }

    SharedPtr<CpuHostBuffer> validityBitmap() const noexcept
    {
        return validityBitmap_;
    }

    std::size_t size() const noexcept
    {
        return size_;
    }

    std::size_t validCount() const noexcept
    {
        return validCount_;
    }

    bool valid(std::size_t position) const;

    std::uintptr_t customData() const noexcept
    {
        return customData_;
    }

    void setCustomData(std::uintptr_t customData) noexcept
    {
        customData_ = customData;
    }

private:
    CpuIndexArray(CpuVectorArray* target);

    CpuIndexArray(const CpuIndexArray& src) = delete;
    CpuIndexArray& operator=(const CpuIndexArray& src) = delete;

    SharedPtr<CpuVectorArray> target_;
    SharedPtr<CpuHostBuffer> targetIndices_ = nullptr;
    SharedPtr<CpuHostBuffer> validityBitmap_ = nullptr;
    std::size_t size_ = 0;
    std::size_t validCount_;
    std::uintptr_t customData_;
};

#ifndef XVEC_MU_SUPPORT
using IndexArray = CpuIndexArray;
#endif

}  // namespace detail
}  // namespace xvec
