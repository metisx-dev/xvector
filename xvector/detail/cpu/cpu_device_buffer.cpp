#include "cpu_device_buffer.hpp"

#include <cstdlib>

#include "xvector/detail/host_buffer.hpp"

namespace xvec
{
namespace detail
{

namespace
{
std::shared_ptr<uint8_t> make_shared_array(std::size_t size)
{
    return std::shared_ptr<uint8_t>(new uint8_t[size], std::default_delete<uint8_t[]>());
}
}  // namespace

CpuDeviceBuffer::CpuDeviceBuffer(Context* context) noexcept
    : Managed<CpuDeviceBuffer>(context),
      size_(0)
{
}

CpuDeviceBuffer::CpuDeviceBuffer(Context* context, size_t size) noexcept
    : Managed<CpuDeviceBuffer>(context),
      base_(make_shared_array(size)),
      size_(size),
      offset_(0)
{
}

void CpuDeviceBuffer::syncToDevice(CpuHostBuffer* hostBuffer) noexcept
{
    base_ = hostBuffer->base();
    offset_ = hostBuffer->offset();
}

void CpuDeviceBuffer::syncFromDevice(CpuHostBuffer* hostBuffer) noexcept
{
    hostBuffer->setData(base_, offset_);
}

}  // namespace detail
}  // namespace xvec
