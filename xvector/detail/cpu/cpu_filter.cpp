#include "cpu_filter.hpp"

#include "cpu_context.hpp"

namespace xvec
{
namespace detail
{
CpuFilter::CpuFilter(CpuContext* context)
    : Managed<CpuFilter>(context)
{
}

void CpuFilter::setBitmap(SharedPtr<CpuDeviceBuffer> bitmap, size_t validCount)
{
    bitmap_ = bitmap;
    validCount_ = validCount;
}

}  // namespace detail
}  // namespace xvec
