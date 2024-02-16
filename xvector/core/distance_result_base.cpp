#include "distance_result_base.hpp"

namespace xvec
{
namespace core
{
DistanceResultBase::DistanceResultBase(ContextBase* context,
                                       const std::shared_ptr<uint8_t[]>& values,
                                       std::size_t count) noexcept
    : Object(ObjectType::DistanceResult, context),
      values_(values),
      count_(count)
{
}
}  // namespace core
}  // namespace xvec
