#pragma once

#include <memory>

#include "xvector/detail/factory.hpp"
#include "xvector/detail/managed.hpp"

namespace xvec
{
namespace detail
{

class CpuHostBuffer;
class CpuContext;

class CpuDeviceBuffer : public Factory<CpuDeviceBuffer>, public Managed<CpuDeviceBuffer>
{
    friend Factory<CpuDeviceBuffer>;

public:
    void syncToDevice(CpuHostBuffer* hostBuffer) noexcept;

    void syncFromDevice(CpuHostBuffer* hostBuffer) noexcept;

    std::shared_ptr<uint8_t> base() const noexcept
    {
        return base_;
    }

    uint8_t* data() const noexcept
    {
        return base_.get() + offset_;
    }

    std::size_t size() const noexcept
    {
        return size_;
    }

private:
    explicit CpuDeviceBuffer(CpuContext* context) noexcept;

    CpuDeviceBuffer(CpuContext* context, std::size_t size) noexcept;

    CpuDeviceBuffer(const CpuDeviceBuffer& src) = delete;
    CpuDeviceBuffer& operator=(const CpuDeviceBuffer& src) = delete;

    std::shared_ptr<uint8_t> base_;
    std::size_t size_;
    std::size_t offset_;
};

#ifndef XVEC_MU_SUPPORT
using DeviceBuffer = CpuDeviceBuffer;
#endif

}  // namespace detail
}  // namespace xvec
