#pragma once

#include "device_buffer.hpp"
#include "managed.hpp"
#include "xvector/xvec_float_type.h"

namespace xvec
{
namespace sim
{
class Context;

class VectorArray : public Managed<VectorArray>
{
public:
    VectorArray(Context* context, xvecFloatType floatType, std::size_t dimension);

    xvecFloatType floatType() const noexcept
    {
        return floatType_;
    }

    size_t dimension() const noexcept
    {
        return dimension_;
    }

    void setVectors(SharedPtr<DeviceBuffer> vectors, std::size_t size);

    SharedPtr<DeviceBuffer> vectors() const
    {
        return vectors_;
    }

    void setValidityBitmap(SharedPtr<DeviceBuffer> validityBitmap, std::size_t validCount);

    SharedPtr<DeviceBuffer> validityBitmap() const
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

    SharedPtr<DeviceBuffer> vector(std::size_t position);

    bool valid(std::size_t position) const;

    void updateVectors(SharedPtr<DeviceBuffer> positions, SharedPtr<DeviceBuffer> vectors, std::size_t size);

    SharedPtr<DeviceBuffer> insertVectors(SharedPtr<DeviceBuffer> vectors, std::size_t size);

    void deleteVectors(SharedPtr<DeviceBuffer> positions, std::size_t size);

private:
    VectorArray(const VectorArray& src) = delete;
    VectorArray& operator=(const VectorArray& src) = delete;

    xvecFloatType floatType_;
    std::size_t dimension_;
    std::size_t size_ = 0;
    std::size_t validCount_ = 0;
    SharedPtr<DeviceBuffer> vectors_ = nullptr;
    SharedPtr<DeviceBuffer> validityBitmap_ = nullptr;
    void* customData_;
    std::size_t freePosition_;
};

}  // namespace sim
}  // namespace xvec
