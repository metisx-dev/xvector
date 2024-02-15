#include "knn_query_base.hpp"

namespace xvec
{
namespace detail
{

KnnQueryBase::KnnQueryBase(ContextBase* context,
                           xvecKnnType type,
                           const std::shared_ptr<uint8_t[]>& vector,
                           xvecFloatType floatType,
                           std::size_t dimension,
                           std::size_t k)
    : Object(ObjectType::KnnQuery, context),
      type_(type),
      floatType_(floatType),
      dimension_(dimension),
      k_(k),
      vector_(vector)
{
}

}  // namespace detail
}  // namespace xvec
