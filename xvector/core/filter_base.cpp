#include "filter_base.hpp"

namespace xvec
{
namespace core
{
FilterBase::FilterBase(ContextBase* context)
    : Object(ObjectType::Filter, context)
{
}

void FilterBase::setBitmap(SharedPtr<DeviceBufferBase> bitmap, size_t validCount)
{
    bitmap_ = bitmap;
    validCount_ = validCount;
}

}  // namespace core
}  // namespace xvec
