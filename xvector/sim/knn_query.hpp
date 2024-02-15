#pragma once

#include "detail/knn_query_base.hpp"

namespace xvec
{
namespace sim
{
using KnnQuery = detail::KnnQueryBase;

void searchKnn(KnnQuery* query);

}  // namespace sim
}  // namespace xvec
