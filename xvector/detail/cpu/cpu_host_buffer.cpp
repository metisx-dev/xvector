#include <cstdlib>

#include "cpu_host_buffer.hpp"
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

CpuHostBuffer::CpuHostBuffer(Context* context)
    : Managed<CpuHostBuffer>(context),
      size_(0)
{
}

CpuHostBuffer::CpuHostBuffer(Context* context, std::size_t size, std::size_t offset)
    : Managed<CpuHostBuffer>(context),
      base_(make_shared_array(size)),
      size_(size),
      offset_(offset)
{
}

CpuHostBuffer::CpuHostBuffer(Context* context,
                             std::shared_ptr<uint8_t> base,
                             std::size_t size,
                             std::size_t offset) noexcept
    : Managed<CpuHostBuffer>(context),
      base_(base),
      size_(size),
      offset_(offset)
{
}

CpuHostBuffer::~CpuHostBuffer() noexcept
{
}

}  // namespace detail
}  // namespace xvec
