#pragma once

#include "xvector/detail/buffer.hpp"
#include "xvector/detail/factory.hpp"
#include "xvector/detail/managed.hpp"
#include "xvector/xvec_float_type.h"

namespace xvec
{
namespace detail
{
class CpuContext;

class CpuVectorArray : public Factory<CpuVectorArray>, public Managed<CpuVectorArray>
{
    friend Factory<CpuVectorArray>;

public:
    xvecFloatType floatType() const noexcept
    {
        return floatType_;
    }

    size_t dimension() const noexcept
    {
        return dimension_;
    }

    void setVectors(SharedPtr<CpuDeviceBuffer> vectors, std::size_t size);

    SharedPtr<CpuDeviceBuffer> vectors() const
    {
        return vectors_;
    }

    void setValidityBitmap(SharedPtr<CpuDeviceBuffer> validityBitmap, std::size_t validCount);

    SharedPtr<CpuDeviceBuffer> validityBitmap() const
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

    void* customData() const noexcept
    {
        return customData_;
    }

    void setCustomData(void* customData) noexcept
    {
        customData_ = customData;
    }

    SharedPtr<CpuDeviceBuffer> vector(std::size_t position);

    bool valid(std::size_t position) const;

    void updateVectors(SharedPtr<CpuDeviceBuffer> positions, SharedPtr<CpuDeviceBuffer> vectors, std::size_t size);

    SharedPtr<CpuDeviceBuffer> insertVectors(SharedPtr<CpuDeviceBuffer> vectors, std::size_t size);

    void deleteVectors(SharedPtr<CpuDeviceBuffer> positions, std::size_t size);

private:
    CpuVectorArray(CpuContext* context, xvecFloatType floatType, std::size_t dimension);

    CpuVectorArray(const CpuVectorArray& src) = delete;
    CpuVectorArray& operator=(const CpuVectorArray& src) = delete;

    xvecFloatType floatType_;
    std::size_t dimension_;
    std::size_t size_ = 0;
    std::size_t validCount_ = 0;
    SharedPtr<CpuDeviceBuffer> vectors_ = nullptr;
    SharedPtr<CpuDeviceBuffer> validityBitmap_ = nullptr;
    void* customData_;
    std::size_t freePosition_;
};

#ifndef XVEC_MU_SUPPORT
using VectorArray = CpuVectorArray;
#endif

}  // namespace detail
}  // namespace xvec
