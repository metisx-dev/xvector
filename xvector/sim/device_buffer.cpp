#include "device_buffer.hpp"

#include <cstdlib>

#include "context.hpp"

namespace xvec
{
namespace sim
{
namespace
{
std::shared_ptr<uint8_t> make_shared_array(std::size_t size)
{
    return std::shared_ptr<uint8_t>(new uint8_t[size], std::default_delete<uint8_t[]>());
}
}  // namespace

DeviceBuffer::DeviceBuffer(Context* context)
    : Managed<DeviceBuffer>(context),
      size_(0)
{
}

DeviceBuffer::DeviceBuffer(Context* context, std::size_t size, std::size_t offset)
    : Managed<DeviceBuffer>(context),
      base_(make_shared_array(size)),
      size_(size),
      offset_(offset)
{
}

DeviceBuffer::DeviceBuffer(Context* context,
                           std::shared_ptr<uint8_t> base,
                           std::size_t size,
                           std::size_t offset) noexcept
    : Managed<DeviceBuffer>(context),
      base_(base),
      size_(size),
      offset_(offset)
{
}

DeviceBuffer::~DeviceBuffer() noexcept
{
}

}  // namespace sim
}  // namespace xvec
