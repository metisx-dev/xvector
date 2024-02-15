#include "query.hpp"

#include <cassert>

#include "distance_query.hpp"
#include "knn_query.hpp"

namespace xvec
{
namespace sim
{
void executeQuery(detail::Object** queries, std::size_t count)
{
    for (std::size_t i = 0; i < count; ++i)
    {
        switch (queries[i]->Object::type())
        {
        case detail::ObjectType::KnnQuery:
            searchKnn(dynamic_cast<KnnQuery*>(queries[i]));
            break;
        case detail::ObjectType::DistanceQuery:
            calculateDistance(dynamic_cast<DistanceQuery*>(queries[i]));
            break;
        default:
            assert(0);
            break;
        }
    }
}
}  // namespace sim
}  // namespace xvec
