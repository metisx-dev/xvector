#include "mu_device_buffer.hpp"

#include <cstdlib>

#include "xflare/detail/host_buffer.hpp"

namespace xvec
{
namespace detail
{

MuDeviceBuffer::MuDeviceBuffer(size_t size)
    : size_(size)
{
}

MuDeviceBuffer::~MuDeviceBuffer() noexcept
{
}

}  // namespace detail
}  // namespace xvec
