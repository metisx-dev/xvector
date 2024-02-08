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

void CpuIndexArray::setTargetIndices(SharedPtr<CpuDeviceBuffer> targetIndices,
                                     std::size_t size,
                                     SharedPtr<CpuDeviceBuffer> validityBitmap,
                                     std::size_t validCount)
{
    targetIndices_ = targetIndices;
    size_ = size;
    validityBitmap_ = validityBitmap;
    validCount_ = validCount;

    if (validCount_ == 0)
    {
        if (validityBitmap_ != nullptr)
        {
            for (std::size_t i = 0; i < size_; ++i)
            {
                if (valid(i))
                {
                    validCount_++;
                }
            }
        }
        else
        {
            validCount_ = size_;
        }
    }
}

bool CpuIndexArray::valid(std::size_t position) const
{
    if (position >= this->size())
    {
        throw std::out_of_range("Index out of range");
    }

    if (validityBitmap_ == nullptr)
    {
        return true;
    }

    const uint8_t* bitmap = validityBitmap_->data();
    return bitmap[position / 8] & (1 << (position % 8));
}

}  // namespace detail
}  // namespace xvec
