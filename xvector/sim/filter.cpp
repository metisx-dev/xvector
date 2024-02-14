#include "filter.hpp"

#include "context.hpp"

namespace xvec
{
namespace sim
{
Filter::Filter(Context* context)
    : Managed<Filter>(context)
{
}

void Filter::setBitmap(SharedPtr<DeviceBuffer> bitmap, size_t validCount)
{
    bitmap_ = bitmap;
    validCount_ = validCount;
}

}  // namespace detail
}  // namespace xvec
