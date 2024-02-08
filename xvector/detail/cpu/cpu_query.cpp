#include "cpu_query.hpp"

#include "cpu_distance_query.hpp"
#include "cpu_knn_query.hpp"

namespace xvec
{
namespace detail
{
void executeQuery(xvec::detail::CpuQuery** queries, std::size_t count)
{
    for (std::size_t i = 0; i < count; ++i)
    {
        switch (queries[i]->queryType())
        {
        case CpuQuery::Knn:
            searchKnn(dynamic_cast<CpuKnnQuery*>(queries[i]));
            break;
        case CpuQuery::Distance:
            calculateDistance(dynamic_cast<CpuDistanceQuery*>(queries[i]));
            break;
        }
    }
}
}  // namespace detail
}  // namespace xvec
