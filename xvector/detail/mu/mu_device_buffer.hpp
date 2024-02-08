#pragma once

#include "xvector/detail/factory.hpp"
#include "xvector/detail/managed.hpp"
#include "xvector/detail/shared_ptr.hpp"

namespace xvec
{
namespace detail
{

class MuHostBuffer;

class MuDeviceBuffer : public Factory<MuDeviceBuffer>, public Managed<MuDeviceBuffer>
{
    friend class MuHostBuffer;

    template <typename T, typename... Args>
    inline SharedPtr<T> makeShared(Args&&... args);

public:
    MuDeviceBuffer(std::size_t size) noexcept;

    ~MuDeviceBuffer() noexcept;

    MuDeviceBuffer(const MuDeviceBuffer& src) = delete;
    MuDeviceBuffer& operator=(const MuDeviceBuffer& src) = delete;

    void syncToHost() noexcept;

    std::size_t size() const noexcept
    {
        return size_;
    }

private:
    // metisx::Heap<> data_;
    std::size_t size_;
};

using DeviceBuffer = MuDeviceBuffer;
using DeviceBuffer = MuDeviceBuffer;

}  // namespace detail
}  // namespace xvec
