#pragma once

#include "detail/distance_query_base.hpp"

namespace xvec
{
namespace sim
{

using DistanceQuery = detail::DistanceQueryBase;

void calculateDistance(DistanceQuery* query);

}  // namespace sim
}  // namespace xvec
