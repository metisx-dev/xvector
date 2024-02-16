#pragma once

#include "core/distance_query_base.hpp"

namespace xvec
{
namespace sim
{

using DistanceQuery = core::DistanceQueryBase;

void calculateDistance(DistanceQuery* query);

}  // namespace sim
}  // namespace xvec
