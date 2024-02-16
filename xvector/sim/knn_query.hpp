#pragma once

#include "core/knn_query_base.hpp"

namespace xvec
{
namespace sim
{
using KnnQuery = core::KnnQueryBase;

void searchKnn(KnnQuery* query);

}  // namespace sim
}  // namespace xvec
