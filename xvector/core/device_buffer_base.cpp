#include "device_buffer_base.hpp"

#include <cstdlib>

#include "context_base.hpp"

namespace xvec
{
namespace core
{
DeviceBufferBase::DeviceBufferBase(ContextBase* context)
    : Object(ObjectType::DeviceBuffer, context),
      size_(0)
{
}

DeviceBufferBase::DeviceBufferBase(ContextBase* context, std::size_t size, std::size_t offset)
    : Object(ObjectType::DeviceBuffer, context),
      size_(size),
      offset_(offset)
{
}

}  // namespace sim
}  // namespace xvec
