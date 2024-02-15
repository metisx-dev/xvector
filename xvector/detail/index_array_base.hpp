#pragma once

#pragma once

#include "device_buffer_base.hpp"
#include "object.hpp"
#include "vector_array_base.hpp"

namespace xvec
{
namespace detail
{
class IndexArrayBase : public Object
{
public:
    explicit IndexArrayBase(VectorArrayBase* target);

    SharedPtr<VectorArrayBase> target() const noexcept
    {
        return target_.get();
    }

    void setIndices(SharedPtr<DeviceBufferBase> indices, size_t size);

    SharedPtr<DeviceBufferBase> indices() const noexcept
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
    IndexArrayBase(const IndexArrayBase& src) = delete;
    IndexArrayBase& operator=(const IndexArrayBase& src) = delete;

    SharedPtr<VectorArrayBase> target_;
    SharedPtr<DeviceBufferBase> indices_ = nullptr;
    std::size_t size_ = 0;
    std::uintptr_t customData_;
};

}  // namespace detail
}  // namespace xvec
