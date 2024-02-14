#include "distance_result.hpp"

namespace xvec
{
namespace sim
{
DistanceResult::DistanceResult(Context* context, const std::shared_ptr<uint8_t[]>& values, std::size_t count) noexcept
    : Managed<DistanceResult>(context),
      values_(values),
      count_(count)
{
}
}  // namespace sim
}  // namespace xvec
