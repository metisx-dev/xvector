#include "index_array_base.hpp"

namespace xvec
{
namespace core
{
IndexArrayBase::IndexArrayBase(VectorArrayBase* target)
    : Object(ObjectType::IndexArray, target->context()),
      target_(target)
{
}

void IndexArrayBase::setIndices(SharedPtr<DeviceBufferBase> indices, std::size_t size)
{
    indices_ = indices;
    size_ = size;
}

}  // namespace core
}  // namespace xvec
