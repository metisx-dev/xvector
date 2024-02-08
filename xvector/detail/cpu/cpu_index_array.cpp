#include "cpu_index_array.hpp"

#include "cpu_context.hpp"

namespace xvec
{
namespace detail
{
CpuIndexArray::CpuIndexArray(CpuVectorArray* target)
    : Managed<CpuIndexArray>(target->context()),
      target_(target)
{
}

void CpuIndexArray::setIndices(SharedPtr<CpuDeviceBuffer> indices,
                                     std::size_t size)
{
    indices_ = indices;
    size_ = size;
}

}  // namespace detail
}  // namespace xvec
