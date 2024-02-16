#pragma once

#include "device_buffer_base.hpp"
#include "object.hpp"
#include "xvector/xvec_float_type.h"

namespace xvec
{
namespace core
{
class VectorArrayBase : public Object
{
public:
    VectorArrayBase(ContextBase* context, xvecFloatType floatType, std::size_t dimension);

    xvecFloatType floatType() const noexcept
    {
        return floatType_;
    }

    size_t dimension() const noexcept
    {
        return dimension_;
    }

    void setVectors(SharedPtr<DeviceBufferBase> vectors, std::size_t size);

    SharedPtr<DeviceBufferBase> vectors() const
    {
        return vectors_;
    }

    std::size_t size() const noexcept
    {
        return size_;
    }

    void* customData() const noexcept
    {
        return customData_;
    }

    void setCustomData(void* customData) noexcept
    {
        customData_ = customData;
    }

    //SharedPtr<DeviceBufferBase> vector(std::size_t position);

private:
    VectorArrayBase(const VectorArrayBase& src) = delete;
    VectorArrayBase& operator=(const VectorArrayBase& src) = delete;

    xvecFloatType floatType_;
    std::size_t dimension_;
    std::size_t size_ = 0;
    SharedPtr<DeviceBufferBase> vectors_ = nullptr;
    void* customData_;
};

}  // namespace core
}  // namespace xvec
