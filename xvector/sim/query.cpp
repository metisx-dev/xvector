#include "distance_query.hpp"
#include "knn_query.hpp"
#include "query.hpp"

namespace xvec
{
namespace sim
{
void executeQuery(Query** queries, std::size_t count)
{
    for (std::size_t i = 0; i < count; ++i)
    {
        switch (queries[i]->queryType())
        {
        case Query::Knn:
            searchKnn(dynamic_cast<KnnQuery*>(queries[i]));
            break;
        case Query::Distance:
            calculateDistance(dynamic_cast<DistanceQuery*>(queries[i]));
            break;
        }
    }
}
}  // namespace sim
}  // namespace xvec
