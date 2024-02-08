#include <cstdlib>

#include "cpu_device_buffer.hpp"
#include "cpu_context.hpp"

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

CpuDeviceBuffer::CpuDeviceBuffer(Context* context)
    : Managed<CpuDeviceBuffer>(context),
      size_(0)
{
}

CpuDeviceBuffer::CpuDeviceBuffer(Context* context, std::size_t size, std::size_t offset)
    : Managed<CpuDeviceBuffer>(context),
      base_(make_shared_array(size)),
      size_(size),
      offset_(offset)
{
}

CpuDeviceBuffer::CpuDeviceBuffer(Context* context,
                             std::shared_ptr<uint8_t> base,
                             std::size_t size,
                             std::size_t offset) noexcept
    : Managed<CpuDeviceBuffer>(context),
      base_(base),
      size_(size),
      offset_(offset)
{
}

CpuDeviceBuffer::~CpuDeviceBuffer() noexcept
{
}

}  // namespace detail
}  // namespace xvec
