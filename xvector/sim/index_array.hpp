#pragma once

#pragma once

#include "device_buffer.hpp"
#include "managed.hpp"
#include "vector_array.hpp"

namespace xvec
{
namespace sim
{
class IndexArray : public Managed<IndexArray>
{
public:
    explicit IndexArray(VectorArray* target);

    SharedPtr<VectorArray> target() const noexcept
    {
        return target_.get();
    }

    void setIndices(SharedPtr<DeviceBuffer> indices, size_t size);

    SharedPtr<DeviceBuffer> indices() const noexcept
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
    IndexArray(const IndexArray& src) = delete;
    IndexArray& operator=(const IndexArray& src) = delete;

    SharedPtr<VectorArray> target_;
    SharedPtr<DeviceBuffer> indices_ = nullptr;
    std::size_t size_ = 0;
    std::uintptr_t customData_;
};

}  // namespace sim
}  // namespace xvec
