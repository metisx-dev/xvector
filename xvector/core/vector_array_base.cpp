#include "vector_array_base.hpp"

#include <cstring>

namespace xvec
{
namespace core
{
VectorArrayBase::VectorArrayBase(ContextBase* context, xvecFloatType floatType, std::size_t dimension)
    : Object(ObjectType::VectorArray, context),
      floatType_(floatType),
      dimension_(dimension)
{
}

void VectorArrayBase::setVectors(SharedPtr<DeviceBufferBase> vectors, std::size_t size)
{
    vectors_ = vectors;
    size_ = size;
}

#if 0
SharedPtr<DeviceBufferBase> VectorArrayBase::vector(std::size_t index)
{
    std::size_t floatSize = floatType() == XVEC_FLOAT32 ? sizeof(float) : sizeof(half);
    auto vector = makeShared<DeviceBufferBase>(context(), dimension() * floatSize);

    uint8_t* dst = vector->address();
    uint8_t* src = vectors_->address() + index * dimension() * floatSize;

    std::memcpy(dst, src, this->dimension() * floatSize);

    return vector;
}
#endif

}  // namespace core
}  // namespace xvec
