#include "cpu_distance_result.hpp"

namespace xvec
{
namespace detail
{
CpuDistanceResult::CpuDistanceResult(Context* context,
                                     const std::shared_ptr<uint8_t[]>& values,
                                     std::size_t count) noexcept
    : Managed<CpuDistanceResult>(context),
      values_(values),
      count_(count)
{
}
}  // namespace detail
}  // namespace xvec
