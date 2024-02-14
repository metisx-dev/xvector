#include "index_array.hpp"

#include "context.hpp"

namespace xvec
{
namespace sim
{
IndexArray::IndexArray(VectorArray* target)
    : Managed<IndexArray>(target->context()),
      target_(target)
{
}

void IndexArray::setIndices(SharedPtr<DeviceBuffer> indices, std::size_t size)
{
    indices_ = indices;
    size_ = size;
}

}  // namespace sim
}  // namespace xvec
